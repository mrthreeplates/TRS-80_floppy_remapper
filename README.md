# TRS-80_floppy_remapper

![front of board](/images/front-v3.jpg)![back of board](/images/back-v3.jpg)

## Introduction

This board dynamically remaps the floppy disk drives (e.g. 0 through 3) in vintage
TRS-80 Model 3, 4, and 4P computers.

The main reason for remapping the floppy drives on these computers
is to enable booting from drives other than the fixed internal drive 0.  This is particualy
useful when paired with a mondern external floppy disk emulator.

Additionally, this board adds support for two external floppy drives on Model 4P
computers (which previously only supported two internal drives).  Inspiration for
this feature came from a [January 1986 80 Micro article](https://colorcomputerarchive.com/repo/Documents/Magazines/80%20Micro/1986/80%20Micro%20-%208601%20-%20January%201986.pdf), while significantly reducing the number of board modifications needed.

Remapping of the drives is selectable via software using a simple "out" command in basic,
enabling one of eight pre-programmed floppy disk maps.  You can also set the default power
up mapping (if desired).

An optional disable switch can be installed, if desired.

In order to install this board, one chip on the floppy disk controller
board (or the main motherboard) needs to be replaced by a socket.  Certain
models require an additional minor motherboard modification (see below).

**WARNING**: This is a hobby project, that I've done for fun, and am sharing my effort for others
to enjoy.  This project requires some soldering and assumes you are very comfortable working around
electronics.  Deadly high voltage is present on these computers!  Do not proceed if you don't know
what you are doing!  I make no claim that these instructions are complete, correct, easy to
follow, or you won't damage your computer.  If this worries you at all, this project isn't for you.

### More information and background about this project:

http://www.vcfed.org/forum/showthread.php?75460-My-floppy-remapper-project-version-2

## Project files

1. [design files](/design): (schematic and pin map)
1. [PCB files](/design/pcb_info): (gerbers, bill of material, centroid)
1. [Programming files](/program): (MPLAB project source code and compiled HEX file)

## Project build instructions

You can build a programmable image from source, or use the pre-built image I've supplied.

How to build from source:

1. Create a new project using [MPLAB X IDE](https://www.microchip.com/mplab/mplab-x-ide) based on a PIC18F26Q10
1. Under your projects tab, "Important Files", right click to "Add item to important Files"
   Select "MyConfig.mc3" from this repo and add it.
   For help see [Adding an Existing Configuration File to a Project](https://microchipdeveloper.com/mcc:mcc-config).
1. Open MCC
1. Click "Generate".  You should now have a list of "mcc_generated" files now, including
   a default"main.c".
1. Overwrite "main.c" with the one from this repo
1. Build the project, it should compile w/o errors.

How to build using a prebuilt Hex file:

1. Select "File" -> "Import" -> "Hex" and select the hex file from this repo.
1. Finish creating a new project based on a PIC18F26Q10

## Programming instructions for PICKit 4

Note: This board has no external power supply.  In order to program it, power
must be supplied by the programmer.

1. Under project properties, select PICKit 4
1. Select Options category: Power
1. Select "power target circuit from PICKit 4"
1. Click Apply

Connect the programmer

1. Connect the 6 pin programming header of the PICKit 4 to the remapper board.  Please be careful to orient
   programming header to match the board pins!  Look for the MCLR pin with an arrow on it.
1. Click program

## Post-programming self tests

After programming (unless the PIC18 is held in reset) it will automatically boot and run a
one-time-only series of self tests.  This is mostly to test the software and
also verifies the PIC is working correctly.

The LEDs will flash through a set of patterns which will take about 15 seconds.

At the end, all of the LEDs should remain lit, with the enable LED flashing slowly.
This indicates the tests passed and confirms all the LEDs are working.

The next time the PIC boots, it will assume it has been installed into a TRS-80 and
will start working normally.  If you boot the PIC without having it installed, the
board may behave unpredictably due to floating inputs (although there is no harm).

At the end of the tests, if an error is found, all of the LEDs will flash in an
alternating pattern.  This means there is either a bug in the code or a problem with
the board.  Either way, this needs to be fixed. If you try to install the board
into a computer, it will refuse to work (as the error status is saved into EEPROM).
In order to re-run the tests, you must re-program the PIC.

## Front LEDs

The LEDs are there to tell you that the board is working and other useful information
(and I need blikenlights).

Otherwise, they are optional (and you obviously can't see them when
the computer is assembled).

The Green enable LED will be lit whenever the disable switch is not closed.

The Red row (and bank) lights show you which mapping is currently selected.
For example, when the first row is lit (next to "0 1 2 3") and the bank is off,
then the mapping of drives will be unchanged.  There are 8 pre-programmed drive mappings.

Additionally, you can save a "default" mapping which is always restored
upon power on of the computer.  This can be any of the 8 pre-programmed
drive maps.

Note that the default mapping is not affected by a computer
reset.  You can take advantage of this by temporarily changing the drive
mapping (and reseting the computer) to force it to boot from another drive.
Unless the mapping is saved, then this temporary mapping will be forgotten
once the computer is powered off.

Whenever the current mapping matches this saved mapping, the Blue light
next to "Default" will be lit.

Finally, the row light will flash periodically to indicate that the PIC
controller is actually alive.

## Back jumpers

There are two jumpers on the back of the board (on the same header used for programming).

The run jumper must be installed before installing the floppy remapper board
(i.e. whenever you aren't trying to program it).

The "M4P mode" jumper should be installed when installing the flopper remapper
into a TRS-80 Model 4P computer **and** you want to add support for external
floppy drives.  Otherwise, this jumper can be left off.

M4P mode (v.s. non-M4P mode) will be indicated by the flashing pattern of the
row light.  When in M4P mode, the selected row light will "double" flash.  Otherwise
the selected row light will slowly flash.

The flashing of the row light also tells you that the MCU is heathy.

## Front headers

An optional disable switch (e.g. SPST) may be installed.  When these pins
are shorted, floppy drive re-mapping will be disabled.

When in M4P mode, the ~DS2 and ~DS3 pins should be connected to a special
floppy drive cable and routed to an external connector out of the back
of the M4P computer.  This provides support for external floppy drives
just like on the Model 3 and 4 computers.

For Model 4 gate array and Model 4P non-gate array computers, an extra
motherboard modification is required.  This is what the third pin on the
output signal header is for (see below).

## Installation in a Model 3 or Model 4 (non-gate array)

TBD

## Installation in a Model 4 Gate array

![Model 4](/images/install-m4-v3.jpg)

## Installation in a Model 4P Gate array

![Model 4P](/images/install-m4p-v3.jpg)

## Installation in a Model 4P (non-gate array)

Sorry, I don't have one of these yet...

## Other TRS-80 Models

TBD

## Floppy cable build instructions (Model 4P only)

On the Model 4P, I built a custom floppy cable which adds an external interface for two floppy drives.

![floppy_cable2](/images/floppy_cable2.jpg)

![floppy_cable1](/images/floppy_cable1.jpg)

Start with a 24" IDC 34-pin IDC extension cable.  This has a male and female 34 pin connector on each end:

https://www.ebay.com/itm/24-inch-34-Pin-IDC-Floppy-Drive-Ribbon-Extension-Cable-Cord-CablesOnline-FF-004/270837785829?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649

You also need two floppy drive connectors (34-pin card edge female IDC), I ordered a bag here:

https://www.ebay.com/itm/5Pack-34-Pin-Card-Edge-Female-IDC-Connector-for-2-54mm-Pitch-Flat-Ribbon-Cable/272723281626?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649

Steps:

1. Remove your existing floppy cable from the M4P.  This is useful for sizing purposes only.  You do not need to modify it.  Keep it for backup purposes!
1. Carefully remove the female connector from 24" extension cable.  You need to reuse this connector.  Cut off the damaged part of the ribbon cable.
1. (Using a vise) Carefully install two Female card edge connectors and the one female IDC connector (removed above) at approximately the same locations as your original floppy cable.  You'll now have a cable that looks like your original one, except that the cable continues past the female IDC connector providing an external male IDC connector.
1. Look at your original floppy cable Female card edge connectors.  If you see that some connectors have been removed, you will have to remove the same connectors from the new cable.  This allows the connector to determine which drive is 0 and which drive is 1.

![floppy_card_edge](/images/floppy_card_edge.jpg)

1. Using an X-acto knife, separate out DS0 and DS1 (pins 10 and 12) from the floppy cable just after the female IDC connector.  These lines should lead towards the male IDC connector.  It is okay if you just cut pin 11 as it is a redundant ground.
1. Connect a two wire ribbon cable to pins 10 and 12.
1. Connect the other end of the two pin ribbon cable to a 2 pin dupont header.
1. Install the cable into the M4P, replacing your original cable.
1. Connect the dupont header to the floppy remapper board.  Note that pin 10 should connect to DS2 and pin 12 should connect to DS3.
1. The rest of the floppy cable will be routed out the back of the M4P.

## Changing the drive mapping

TBD

## Using the disable switch

To avoid unexpected behaivor (i.e accidents), if any drive is currently
active when the disable switch is toggled, the mapping will not be changed.
As soon as the drive stops, the new mapping state will take effect.

## Theory of operation

TBD



