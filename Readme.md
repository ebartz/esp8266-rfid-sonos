# Description
This box is made to control Sonos Speakers. My children are not yet able to control the Sonos speakers using a Phone or a tablet and in most cases I don't want them to. So I came to the idea, that RFID cards with album covers printed on them could be a good way for them to choose what they want to listen to.

The Tiny box is connected via WIFI. It then connects to an MQTT Server and sends the Card IDs and an event if a button has been pressed to the server. Afterwards I pick up those events using node-red which then plays the selected audio on the sonos speaker.

Here you can find a demo video:

[![VIDEO](https://img.youtube.com/vi/QziWnsG4_Hs/0.jpg)](https://www.youtube.com/watch?v=QziWnsG4_Hs)

# DIY?
Wanna build it yourself? Just go ahead, if I can do it, you probably can do it much better :)

## Part List

Part | QTY | Info | Link | Price |
| -- | :-: | ---- | :--: | ----: |
| Case | 1 | 72 x 50 x 26  |[Conrad](https://www.conrad.de/de/strapubox-2024bl-universal-gehaeuse-72-x-50-x-26-abs-blau-transparent-1-st-525967.html) | 3,65 € |
| Switch Red | 1 | TC-R13-24A1-05 RD | [Conrad](https://www.conrad.de/de/tru-components-tc-r13-24a1-05-rd-drucktaster-250-vac-15-a-1-x-ausein-tastend-1-st-1587869.html) | 1,32€ |
| Switch Yellow | 1 | TC-R13-24A1-05 YE | [Conrad](https://www.conrad.de/de/tru-components-tc-r13-24a1-05-ye-drucktaster-250-vac-15-a-1-x-ausein-tastend-1-st-1587870.html) | 1,32€ |
| Switch Green | 1 | TC-R13-24A1-05 GN | [Conrad](https://www.conrad.de/de/tru-components-tc-r13-24a1-05-gn-drucktaster-250-vac-15-a-1-x-ausein-tastend-1-st-1587871.html) | 1,32€ |
| Power Supply | 1 | Micro USB, 5V 1A | [Conrad](https://www.conrad.de/de/usb-ladegeraet-basetech-ppc-5mu-ppc-5mu-steckdose-ausgangsstrom-max-1000-ma-1-x-micro-usb-469382.html) | 4,99€ |
| RFID Reader | 1 | RC522 | [Amazon](https://www.amazon.de/gp/product/B076HTH56Q/) | 6,99€ |
| ESP Board   | 1 | Wemos D1 Mini | [Amazon](https://www.amazon.de/AZDelivery-D1-Mini-ESP8266-12E-kompatibel/dp/B01N9RXGHY/) | 5,99€ |

You may find those parts cheaper on Aliexpress or ebay.

## Wiring
To make it easier to read, I decided to split up the wiring in 2 parts.

### RC522 Board
![RC522 Wiring](/img/fritzing-1.png?raw=true "RC522 Wiring")

### Buttons
![Buttons](/img/fritzing-2.png?raw=true "Buttons")

## Build Steps

### Flashing the Code
To make your ESP ready, you will have to flash the Code to your ESP Board. This can be done using the Arduino IDE.

For the first time, you will have to flash the code using USB. When everything is flashed and the ESP is connected to your WiFi, you can update the code over the network so that no USB connection should be needed after the first setup.

Before you can compile the code, you will have to update wifi and MQTT settings.

Also you will have to install some Dependencies: (TBD)


### Prepare the Case
To prepare the case you have to add 3 holes which will later be used to mount the buttons.

![Buttons](/img/002.jpg?raw=true "Buttons")
![Buttons](/img/003.jpg?raw=true "Buttons")
![Buttons](/img/004.jpg?raw=true "Buttons")
![Buttons](/img/005.jpg?raw=true "Buttons")

### Soldering
I prepared 9 wires which are about 7cm long. I have soldered them to the RC522 board at first.

![Soldering](/img/006.jpg?raw=true "Soldering")

Afterwards I soldered the wires to the buttons and glued the RC522 board to the bottom of the case using hot glue.

![Soldering](/img/006.jpg?raw=true "Soldering")
![Soldering](/img/007.jpg?raw=true "Soldering")
![Soldering](/img/008.jpg?raw=true "Soldering")

And then soldered it to the Wemos board.

Finnaly slice a hole to the botton where the power cable fits in and glue everything together.

![Soldering](/img/009.jpg?raw=true "Soldering")
![Soldering](/img/010.jpg?raw=true "Soldering")


## Node Red
You Will need MQTT, node-red-contrib-better-sonos and node-red-contrib-sonos.

The flow looks like this:
![NodeRED](/img/node-red-1.png?raw=true "NodeRED")

Flow Example:
```
[{"id":"a10034ab.7f15e8","type":"mqtt in","z":"93696aff.c14fc8","name":"1 - Speaker 1","topic":"rfid/1/","qos":"0","broker":"","x":290,"y":180,"wires":[["1f8a78ee.ee7877"]]},{"id":"8916af00.62475","type":"mqtt in","z":"93696aff.c14fc8","name":"Vol Up","topic":"rfid/1/button/1","qos":"0","broker":"","x":290,"y":280,"wires":[["42ee40a5.e087a"]]},{"id":"ae2cc053.db46a","type":"mqtt in","z":"93696aff.c14fc8","name":"Pause","topic":"rfid/1/button/2","qos":"0","broker":"","x":290,"y":340,"wires":[["58d3d246.07811c"]]},{"id":"ad10faf1.f738f8","type":"mqtt in","z":"93696aff.c14fc8","name":"Vol Down","topic":"rfid/1/button/3","qos":"0","broker":"","x":300,"y":400,"wires":[["2d3b8c60.65ad44"]]},{"id":"66af88b8.04b1d8","type":"better-sonos-control","z":"93696aff.c14fc8","confignode":"","name":"","mode":"play","track":"","volume":"","volume_value":"","x":940,"y":300,"wires":[]},{"id":"58d3d246.07811c","type":"better-sonos-status","z":"93696aff.c14fc8","confignode":"","name":"","x":500,"y":340,"wires":[["e00db7d6.284438"]]},{"id":"e00db7d6.284438","type":"switch","z":"93696aff.c14fc8","name":"","property":"state","propertyType":"msg","rules":[{"t":"eq","v":"paused","vt":"str"},{"t":"eq","v":"playing","vt":"str"}],"checkall":"true","repair":false,"outputs":2,"x":710,"y":340,"wires":[["66af88b8.04b1d8"],["40218887.a2a648"]]},{"id":"40218887.a2a648","type":"better-sonos-control","z":"93696aff.c14fc8","confignode":"","name":"","mode":"pause","track":"","volume":"","volume_value":"","x":940,"y":360,"wires":[]},{"id":"ed6fd1f2.9a9e7","type":"sonos-queue","z":"93696aff.c14fc8","playnode":"","songuri":"","position":"directplay","positioninqueue":"","name":"Play File","x":980,"y":160,"wires":[[]]},{"id":"1f8a78ee.ee7877","type":"switch","z":"93696aff.c14fc8","name":"","property":"payload","propertyType":"msg","rules":[{"t":"eq","v":"911d992f","vt":"str"},{"t":"eq","v":"0433a2a2ed4c80","vt":"str"},{"t":"eq","v":"9111192f","vt":"str"}],"checkall":"true","repair":false,"outputs":3,"x":510,"y":180,"wires":[["44d12305.c202ac"],["2b57a5ef.e09f9a"],["4a9e52e.d4df3ac"]]},{"id":"44d12305.c202ac","type":"change","z":"93696aff.c14fc8","name":"Audiobook 1","rules":[{"t":"set","p":"payload","pt":"msg","to":"{\"songuri\":\"http://hostname/audiobook1.mp3\"}","tot":"json"}],"action":"","property":"","from":"","to":"","reg":false,"x":690,"y":140,"wires":[["ed6fd1f2.9a9e7"]]},{"id":"2b57a5ef.e09f9a","type":"change","z":"93696aff.c14fc8","name":"Audiobook 2","rules":[{"t":"set","p":"payload","pt":"msg","to":"{\"songuri\":\"http://hostname/audiobook2.mp3\"}","tot":"json"}],"action":"","property":"","from":"","to":"","reg":false,"x":690,"y":180,"wires":[["ed6fd1f2.9a9e7"]]},{"id":"4a9e52e.d4df3ac","type":"change","z":"93696aff.c14fc8","name":"Audiobook 3","rules":[{"t":"set","p":"payload","pt":"msg","to":"{\"songuri\":\"http://hostname/audiobook3.mp3\"}","tot":"json"}],"action":"","property":"","from":"","to":"","reg":false,"x":690,"y":220,"wires":[["ed6fd1f2.9a9e7"]]},{"id":"2d3b8c60.65ad44","type":"better-sonos-control","z":"93696aff.c14fc8","confignode":"","name":"","mode":"","track":"","volume":"vol_down","volume_value":"","x":500,"y":400,"wires":[]},{"id":"42ee40a5.e087a","type":"better-sonos-control","z":"93696aff.c14fc8","confignode":"","name":"","mode":"","track":"","volume":"vol_up","volume_value":"","x":500,"y":280,"wires":[]}]
```
