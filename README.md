# TRS-80 Floppy remapper

![front of board](/images/front-v4.jpg) ![back of board](/images/back-v4.jpg)

## Introduction

The TRS-80 floppy remapper is a simple board (and microcontroller) which dynamically remaps the floppy disk drives in vintage
[TRS-80](https://en.wikipedia.org/wiki/TRS-80) computers.

The main reason for remapping the floppy drives on these computers
is to enable booting from drives other than the fixed internal drive 0.  This is particualy
useful when paired with a modern external floppy disk emulator such as
the [USB HxC emulator](http://hxc2001.free.fr/floppy_drive_emulator/).  This avoids the need
to take apart the computer, swap cables or replace your internal vintage floppy drives.

## Features

1. Should work in the TRS-80 model 3, model 4, model 4 gate-array, model 4P, and model 4P gate-array computers
1. Eight different floppy drive mappings are supported, allowing booting from
any drive (0-3) with a choice of two different maps for each boot drive.
This map can be as simple as swapping drives 0 and 1 (useful perhaps if they are different types).
1. Mappings are controlled via software using a simple "out" command (conveniently in Basic).
You can set the current map (which will survive a computer reset), or set the default
map (to be used upon computer power on).
1. An optional disable switch can be installed (if desired).
1. As a bonus for Model 4P users, this board adds support for two external floppy drives (which previously only supported two internal drives).  Inspiration for
this feature came from a magazine article in [80 Micro (January 1986)](https://colorcomputerarchive.com/repo/Documents/Magazines/80%20Micro/1986/80%20Micro%20-%208601%20-%20January%201986.pdf), while significantly reducing the modifications needed.
1. Optional (limited) motor control is supported, turning on drive motors only when they are accessed.  This is useful to avoid wear and tear on your internal floppy drives when primarily using external (likely virtual) drives.
1. LEDs on the board display the current map, default map, enable status, and mode.  Sadly the LEDs are not visible when the computer is assembled (but they are useful for debugging, are pretty colors, and they blink).
1. When booting from a [M3SE](http://bartlettlabs.com/M3SE/) or [FreHD](http://www.vecoven.com/trs80/trs80.html), the remapper can be used to conveniently
remap the two internal drives (as the remaining drives are allocated to Hard Disks).
1. I've made every attempt to make the board "easy" to install (or remove) with the mimimum number of board changes.  On most models, you only need to install one socket (while two models require a single jumper wire).  Other features are optional.

## Examples
#### TRS-80 Model 4P booting directly from an external floppy emulator
![Model 4P GA booting](/images/m4pga-boot.jpg)
#### TRS-80 Model 4 (gate array) install
![Model 4P GA booting](/images/install-m4ga-1.jpg)

## More info

* [Board design, manufacturing, and programming](/Design.md)
* [Board overview](/Board.md)
* Prep for installation
  * [Making the Model 4P Floppy Cable](/M4P-FloppyCable.md)
  * [Installing the socket](/Socket.md)
  * [(Optional) Installing a disable switch](/Disable.md)
  * [(Optional) Enabling limited motor control](/MotorOn.md)
* [TRS-80 Model 3, 4, and 4P installation](/Installation.md)
* [Usage](/Usage.md)

## Discussion

* [VCF Thread on V3](http://www.vcfed.org/forum/showthread.php?75460-My-floppy-remapper-project-version-2)
* [VCF Thread on V1](http://www.vcfed.org/forum/showthread.php?70726-Booting-from-an-external-floppy-on-a-model-III&p=606759#post606759)

## Changes in V4

1. Added support for controlling MotorOn signals. Thanks to Pete (pski) for this suggestion!
1. As I had to reduce the number of LEDS (for MotorOn), I simplified how the current MAP is displayed
1. Increased passive component size to 0603 for easier assembly (and verification)
1. Tweaked the silkscreen to make the text more readable
1. Fixed LED brightness (because these things matter)

## Still todo

1. Modify TRS-80 boot roms to control drive mapping via the keyboard (eliminating the need
for a disable switch).
1. Write theory of operation
1. Possibly reduce header (U2) height so it fits better underneath the graphics board on a M4P non-gate array.  I need to be careful so that this doesn't create opportunities for shorting underneath the remapper board.
