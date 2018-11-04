/*
    ESP8266 RFID Reader - MQTT Sender
    Copyright 2018 Enrico Bartz <eb@mrel.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
    der GNU General Public License, wie von der Free Software Foundation,
    Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
    veröffentlichten Version, weiterverbreiten und/oder modifizieren.

    Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
    OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
    Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
    Siehe die GNU General Public License für weitere Details.

    Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
    Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D8 //Pin on WeMos D1 Mini
#define RST_PIN D3 //Pin on WeMos D1 Mini


const char* ssid = "SSID goes HERE!!";
const char* password = "WIFI Password goes here!!";
const char* server = "MQTT Server Name/IP here!!";
char deviceId[10] = "1"; // device id, if you use more than one box. Must be different for each one!


char host[100] = "rfid_reader_";
ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;
WiFiClient wifi;
PubSubClient mqttClient(wifi);

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

unsigned int batt;
double battV;
unsigned long oldMillis;

void connect();

void reconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect(host)){
      Serial.println("connected");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
//      Wait 5 seconds before retrying
      delay(1000);
    }
  }
}

void setup(void){
  SPI.begin();
  rfid.PCD_Init();

  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);

  mqttClient.setServer(server, 1883);

  connect();

  MDNS.begin(host);

  // build hostname
  strcat(host, deviceId);

  //Attach handles for different pages.
  httpUpdater.setup(&httpServer);

  httpServer.on("/", handleRoot);

  httpServer.begin();

  MDNS.addService("http", "tcp", 80);

  // init switch
  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  Serial.println("Up and running!");


}

int prevState1 = 0;
int currState1 = 0;
long lastChangeTime1 = 0;
char buttonMessage[10] = "true";

void checkButton1(){
  // Invert state, since button is "Active LOW"
  int state1 = !digitalRead(5);

  // Debounce mechanism
  long t = millis();
  if (state1 != prevState1) {
    lastChangeTime1 = t;
    Serial.println("Button 1");
    if (state1 != 0){
      char topic1[200] = "rfid/";
      strcat(topic1, deviceId);
      strcat(topic1, "/button/1");
      mqttClient.publish(topic1, buttonMessage);
    }
  }
  if (t - lastChangeTime1 > 50) {
    if (state1 != currState1) {
      currState1 = state1;
    }
  }
  prevState1 = state1;
}


int prevState2 = 0;
int currState2 = 0;
long lastChangeTime2 = 0;
void checkButton2(){
  // Invert state, since button is "Active LOW"
  int state2 = !digitalRead(4);

  // Debounce mechanism
  long t = millis();
  if (state2 != prevState2) {
    lastChangeTime2 = t;
    Serial.println("Button 2");
    if (state2 != 0){
      char topic2[200] = "rfid/";
      strcat(topic2, deviceId);
      strcat(topic2, "/button/2");
      mqttClient.publish(topic2, buttonMessage);
    }
  }
  if (t - lastChangeTime2 > 50) {
    if (state2 != currState2) {
      currState2 = state2;
    }
  }
  prevState2 = state2;
}


int prevState3 = 0;
int currState3 = 0;
long lastChangeTime3 = 0;
void checkButton3(){
  // Invert state, since button is "Active LOW"
  int state3 = !digitalRead(2);

  // Debounce mechanism
  long t = millis();
  if (state3 != prevState3) {
    lastChangeTime3 = t;
    Serial.println("Button 3");
    if (state3 != 0){
      char topic3[200] = "rfid/";
      strcat(topic3, deviceId);
      strcat(topic3, "/button/3");
      mqttClient.publish(topic3, buttonMessage);
    }
  }
  if (t - lastChangeTime3 > 50) {
    if (state3 != currState3) {
      currState3 = state3;
    }
  }
  prevState3 = state3;
}


void loop(void){
  //if(!mqtt.connected()) {
  //  connect();
 // }

  httpServer.handleClient();
  //mqtt.loop();
  delay(10);
  if (!mqttClient.connected()) {
    reconnect();
  }

  mqttClient.loop();
  handleRFID();
  checkButton1();
  checkButton2();
  checkButton3();

  //things that should only be transmitted all 60 sec
  if (millis()-oldMillis > 60000) {
    batt = analogRead(A0);
    battV = mapDouble(batt, 0, 1023, 0.0, 6.6);
    oldMillis = millis();
  }
}

void connect() {
  while(WiFi.waitForConnectResult() != WL_CONNECTED){
    WiFi.begin(ssid, password);
    Serial.println("WiFi failed, retrying.");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("\nconnected!");
}

void handleRoot() {
  httpServer.send(200, "text/plain", host);
}

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();
}

void handleRFID() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;
  String data = printHex(rfid.uid.uidByte, rfid.uid.size);
  char copy[50];
  data.toCharArray(copy, 50);
  char topic0[200] = "rfid/";
  strcat(topic0, deviceId);
  strcat(topic0, "/");
  mqttClient.publish(topic0, copy);
  Serial.print(data);
  Serial.print('\n');
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

double mapDouble(double x, double in_min, double in_max, double out_min, double out_max)
{
  double temp = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  temp = (int) (4*temp + .5);
  return (double) temp/4;
}

String printHex(byte *buffer, byte bufferSize) {
  String id = "";
  for (byte i = 0; i < bufferSize; i++) {
    id += buffer[i] < 0x10 ? "0" : "";
    id += String(buffer[i], HEX);
  }
  return id;
}
