redos
=====

Implemented Features:
* Keyboard Driver and Stdio Support for it
* VGA Driver and a Full printf()
* Real Time Clock with Unix Timestamp ability
* Interrupt Handling with Programmable Interrupt Controller Support
* Grand Descriptor Table implemented

Lots More to come

stdint
======
So <stdint.h> exists. I'm gonna use it.
All mission critical primitive types will be changed to stdint types.
This will allow porting to other platforms of different word size easier.
