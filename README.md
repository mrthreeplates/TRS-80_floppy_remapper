# TRS-80_floppy_remapper

![front of board](/images/front-v3.jpg)![back of board](/images/back-v3.jpg)

## Introduction

This board dynamically remaps the floppy disk drives (numbered 0 through 3) in vintage
TRS-80 Model 3, 4, and 4P computers.

Additionally, this board adds support for two external floppy drives on Model 4P
computers (which only support two internal drives).

Note: A special floppy cable is required on the Model 4P which extends the floppy drive bus
out of the back of the computer.  Instructions TBD.

The main reason for remapping the floppy drives on these computers
is to enable booting from drives other than the fixed internal drive 0.  This is particualy
useful when paired with an external floppy disk emulator.

Remapping of the drives is selectable via software control using an "out" command, enabling one of eight
pre-programmed floppy disk maps.  Software can also set the default power up mapping (if desired).

A physical disable switch can installed which disables the selected floppy mapping.

In order to install this board, the floppy drive controller's 74LS174 chip (a hex D flip-flop) must be removed
and a 16 pin socket installed in its place.  This board replaces the function of the 74LS174.  Additionally, the
model 4 Gate-array and model 4 non-gate array computers require a minor board modification.

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

## Jumpers

There are two jumpers on the board.

The run jumper must be installed before installing the floppy remapper board.

The "M4P mode" jumper should be installed when installing the flopper remapper
into a TRS-80 Model 4P computer **and** you want to add support for external
floppy drives.  Otherwise, this jumper can be left off.

M4P mode (v.s. non-M4P mode) will be indicated by the flashing pattern of the
row lights.  When in M4P mode, the selected row light will "double" flash.  Otherwise
the selected row light will slowly flash.

The flashing of the row light also tells you that the MCU is heathy.

## Front headers

An optional disable switch (e.g. SPST) may be installed.  When these pins
are shorted, the floppy drive re-mapping will be disabled.

When in M4P mode, the ~DS2 and ~DS3 pins should be connected to a special
floppy drive cable and routed to an external connector out of the back
of the M4P computer.  This provides support for external floppy drives
just like on the Model 3 and 4 computers.

For Model 4 gate array and Model 4P non-gate array computers, an extra
motherboard modification is required.  This is what the third pin on the
output signal header is for.  Instructions TBD...


