# Description
This box is made to control Sonos Speakers. My children are not yet able to control the Sonos speakers using a Phone or a tablet and in most cases I don't want them to. So I came to the idea, that RFID cards with album covers printed on them could be a good way for them to choose what they want to listen to.

The Tiny box is connected via WIFI. It then connects to an MQTT Server and sends the Card IDs and an event if a button has been pressed to the server. Afterwards I pick up those events using node-red which then plays the selected audio on the sonos speaker.

[![VIDEO](https://img.youtube.com/vi/QziWnsG4_Hs/0.jpg)](https://www.youtube.com/watch?v=QziWnsG4_Hs)

# DIY?
Wanna build it yourself? Just go ahead, if I can do it, you probably can do it much better :)

## Part List

Part | QTY | Info | Link | Price |
| -- | :-: | ---- | :--: | ----: |
| Case | 1 | 72 x 50 x 26  |[Conrad](https://www.conrad.de/de/strapubox-2024bl-universal-gehaeuse-72-x-50-x-26-abs-blau-transparent-1-st-525967.html) | 3,65 € |
| Switch Red | 1 | TC-R13-24A1-05 RD | [Conrad](https://www.conrad.de/de/tru-components-tc-r13-24a1-05-rd-drucktaster-250-vac-15-a-1-x-ausein-tastend-1-st-1587869.html) | 1,32€ |
| Switch Yellow | 1 | TC-R13-24A1-05 YE | [Conrad](https://www.conrad.de/de/tru-components-tc-r13-24a1-05-ye-drucktaster-250-vac-15-a-1-x-ausein-tastend-1-st-1587870.html) | 1,32€ |
| Switch Yellow | 1 | TC-R13-24A1-05 GN | [Conrad](https://www.conrad.de/de/tru-components-tc-r13-24a1-05-gn-drucktaster-250-vac-15-a-1-x-ausein-tastend-1-st-1587871.html) | 1,32€ |
| Power Supply | 1 | Micro USB, 5V 1A | [Conrad](https://www.conrad.de/de/usb-ladegeraet-basetech-ppc-5mu-ppc-5mu-steckdose-ausgangsstrom-max-1000-ma-1-x-micro-usb-469382.html) | 4,99€ |
| RFID Reader | 1 | RC522 | [Amazon](https://www.amazon.de/gp/product/B076HTH56Q/) | 6,99€ |
| ESP Board   | 1 | Wemos D1 Mini | [Amazon](https://www.amazon.de/AZDelivery-D1-Mini-ESP8266-12E-kompatibel/dp/B01N9RXGHY/) | 5,99€ |

You may find those parts cheaper on Aliexpress or ebay.

## Wiring

## Build Steps

## Node Red
