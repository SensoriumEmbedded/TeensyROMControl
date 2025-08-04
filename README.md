# TeensyROMControl
Library for microcontroller based control of the [TeensyROM](https://github.com/SensoriumEmbedded/TeensyROM) via USB Serial.
Connect USB device port of microcontroller module (Arduino, ESP32, etc) to the Host USB port of the TeensyROM.  

Example project Connects 10 push buttons, each programmable to perform any of the following functions:
* Launch any File (PRG, CRT, SID, KLA etc)
  * Can be located on SD Card, USB memory, or TeensyROM included programs.
* Pause/Unpause SID
* Individual SID Voice Mutes (1-3)
* Pause/Freeze entire C64 system
* Reset TeensyROM to Main Menu
