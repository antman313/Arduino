##ENC28J60 Ethernet module

After playing with Arduino for a while, I wanted to connect one to the Internet for a little project. Now you can buy shields for that, but they are quite expensive (like 40$). So I decide to look for alternatives and after a while I found 10$ ENC28J60 Ethernet module.

You can buy one here for a price like a Cup of Coffee.

http://www.amazon.de/gp/product/B00H8Q0DVA/ref=oh_details_o00_s00_i00?ie=UTF8&psc=1

#####Specs

Ethernet LAN Module for Arduino/AVR/LPC/STM3/Teensy
ENC28J60 Ethernet chips
Network Interface: HR911105A
Supply Voltage: 3.3 V
25Mhz crystal oscillator


#####Wireing

As it turns out, it is quite easy to connect any (3.3 or 5V) Arduino to one of those modules with just six wires:

ENC SO -> Arduino pin 12
ENC SI -> Arduino pin 11
ENC SCK -> Arduino pin 13
ENC CS -> Arduino pin 8
ENC VCC -> Arduino 3V3 pin
ENC GND -> Arduino Gnd pin

#####Use it

see the example files:

xxx.ino
xxx.ino
