# TRS-80 Floppy remapper

![front of board](/images/front-v3.jpg) ![back of board](/images/back-v3.jpg)

## Introduction

The TRS-80 floppy remapper is a simple board which dynamically remaps the floppy disk drives in vintage
TRS-80 Model 3, 4, and 4P computers.

The main reason for remapping the floppy drives on these computers
is to enable booting from drives other than the fixed internal drive 0.  This is particualy
useful when paired with a modern external floppy disk emulator such as
the [USB HxC emulator](http://hxc2001.free.fr/floppy_drive_emulator/).  This avoids the need
to take apart the computer, swap cables or replace your internal vintage floppy drives.

When booting from a [M3SE](http://bartlettlabs.com/M3SE/) or [FreHD](http://www.vecoven.com/trs80/trs80.html), the remapper can be used to conveniently
remap the two internal drives (as the remaining drives are Hard Disks).

Eight different floppy drive mappings are supported, allowing booting from
any drive (0-3) with a choice of two maps for each boot drive.
This map can be as simple as swapping drives 0 and 1 (useful perhaps if they are different types).

As a bonus, this board adds support for two external floppy drives on Model 4P
computers (which previously only supported two internal drives).  Inspiration for
this feature came from a [January 1986 80 Micro article](https://colorcomputerarchive.com/repo/Documents/Magazines/80%20Micro/1986/80%20Micro%20-%208601%20-%20January%201986.pdf), while significantly reducing the modifications needed.

Remapping of the drives is controlled via software using the "out" command in Basic.
You can set the current map (which will survive a reset), or set the default
map to be used upon power on.

An optional disable switch can be installed if desired.

In order to install this board, one chip on the floppy disk controller
board (or the main motherboard) needs to be replaced by a socket.  Certain
models require an additional minor modification (see installation details).

My goal for this project was to enable the features above while
requiring the fewest (and least invasive) modifications possible to these
vintage computers.

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
  * [Installing an (optional) disable switch](/Disable.md)
* [TRS-80 Model 3, 4, and 4P installation](/Installation.md)
* [Usage](/Usage.md)

## Discussion

* [VCF Thread on V3](http://www.vcfed.org/forum/showthread.php?75460-My-floppy-remapper-project-version-2)
* [VCF Thread on V1](http://www.vcfed.org/forum/showthread.php?70726-Booting-from-an-external-floppy-on-a-model-III&p=606759#post606759)

## TODO

1. LED brightness is not exactly right (green is bit too bright,
blue is too dim, reds are about right).
1. Modify TRS-80 boot roms to control drive mapping via the keyboard (eliminating the need
for a disable switch).
1. Write theory of operation
