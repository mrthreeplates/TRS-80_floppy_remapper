# TRS-80_floppy_remapper

![front of board](/images/front-v3.jpg) ![back of board](/images/back-v3.jpg)

## Introduction

The TRS-80 floppy remapper dynamically remaps the floppy disk drives (e.g. 0 through 3) in vintage
TRS-80 Model 3, 4, and 4P computers.

The main reason for remapping the floppy drives on these computers
is to enable booting from drives other than the fixed internal drive 0.  This is particualy
useful when paired with a modern external floppy disk emulator such as
the [USB HxC emulator](http://hxc2001.free.fr/floppy_drive_emulator/).  This avoids the need
to take apart the computer, swap cables or replace your internal vintage floppy drives.

Additionally, this board adds support for two external floppy drives on Model 4P
computers (which previously only supported two internal drives).  Inspiration for
this feature came from a [January 1986 80 Micro article](https://colorcomputerarchive.com/repo/Documents/Magazines/80%20Micro/1986/80%20Micro%20-%208601%20-%20January%201986.pdf), while significantly reducing the modifications needed.

Remapping of the drives is selectable via software using a simple "out" command in basic,
enabling one of eight pre-programmed floppy disk maps.  You can also save the default power
up mapping.

An optional disable switch can be installed.

In order to install this board, one chip on the floppy disk controller
board (or the main motherboard) needs to be replaced by a socket.  Certain
models require an additional minor motherboard modification (see below).

My goal for this project was to enable the features above while
requiring the fewest (and least invasive) modifications possible to these
vintage computers.

## TRS-80 Model 4P booting directly from an external floppy emulator

![Model 4P GA booting](/images/m4pga-boot.jpg)

## Contents

* [Board design, manufacturing, and programming](/Design.md)
* [Board overview](/Board.md)
* Prep for installation
  * [Making the M4P Floppy Cable](/M4P-FloppyCable.md)
  * [Installing the socket](/Socket.md)
  * [Installing an (optional) disable switch](/Disable.md)
* [Installation](/Installation.md)
* [Usage](/Usage.md)

## Background

* [VCF Thread on V3](http://www.vcfed.org/forum/showthread.php?75460-My-floppy-remapper-project-version-2)
* [VCF Thread on V1](http://www.vcfed.org/forum/showthread.php?70726-Booting-from-an-external-floppy-on-a-model-III&p=606759#post606759)

## TODO for V3

1. LED brightness is still not exactly right (green is still a touch bright,
blue is a touch too dim, reds are about right).
1. Add code to TRS-80 boot roms to set drive mapping (eliminating the need
for a disable switch).
1. Write theory of operation section
