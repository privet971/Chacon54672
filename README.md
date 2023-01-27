# Chacon54672
Taking control on CHACON 54672 plugs



My aim was to remote controlling outlet plugs Chacon 54672   through Alexa.

I first tried to use the RCSWITCH library by modifying it without success,
then several other arduino programs with different MCU, RPI too, but none worked.
Some other tools too, rtl_433,RFSniffer, and my memory oscilloscope 

Finally, I used an arduino sketch to record the original 54672 remote control with the correct timings then I used an RPI to recreate them

Here is my working succeed journey:

Let's start with the hardware: 
- I used an ESP12E module (ESP8266) with a basic 433 receiver.
By the way, you have to know that these economic receivers have a big issue, they receive a lot of parasites when they are powered in 5V while in 3,3V, these parasites disappear. Maybe a problem with the integrated power supply regulator ? 
- A raspberry pi 4 with a low cost 433 transmitter.

With help of https://github.com/sillyfrog/RFreplayESP, I recorded the original 54672 remote control with the correct timings in files then I used an RPI to recreate them.


Using Nodered help , Alexa launch my RPI program with correct file parameter. 




EPILOGUE: Today (01/27/2023), I just found this repository https://github.com/fcrespel/chacon54662 which seem to be functional but I'm too lazy to try it.
