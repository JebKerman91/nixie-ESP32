# nixie-ESP32
Arduino Nano ESP32 conversion of Great Scott's Nixie Tube clock

Arduino Nano ESP32 sketches and interposer board design files to enable network connectivity on the Nixie Tube clock [as originally designed by Great Scott](https://www.youtube.com/watch?v=ObgmVNV1Kfg).

The interposer board is a very rough design, being an amateur at best when PCB design is concerned.

Two solder jumpers enable the selection of input voltage: either 5V through what would be the original Arduino Pro Mini's 5V power supply pin, or through a pad to be connected to the clock's existing 9V voltage.

The power supply specifications of the Arduino Nano ESP32 recommend a voltage range *starting* from 6V for the external power supply, but 5V seems to work good enough in practice.
