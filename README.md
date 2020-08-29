# TRS-80_floppy_remapper

![front of board](/images/front-v3.jpg)![back of board](/images/back-v3.jpg)

## Introduction

This board dynamically remaps the floppy disk drives (e.g. 0 through 3) in vintage
TRS-80 Model 3, 4, and 4P computers.

The main reason for remapping the floppy drives on these computers
is to enable booting from drives other than the fixed internal drive 0.  This is particualy
useful when paired with a modern external floppy disk emulator.

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

My goal for this project was to enable the features above while
requiring the fewest (and least invasive) modifications possible.

**WARNING**: This is a hobby project, that I've done for fun, and am sharing my effort for others
to enjoy.  This project requires some soldering and assumes you are very comfortable working around
electronics.  Deadly high voltage is present on these computers!  Do not proceed if you don't know
what you are doing!  I make no claim that these instructions are complete, correct, easy to
follow, or you won't damage your computer.  If this worries you at all, this project isn't for you.

### More information and background about this project:

http://www.vcfed.org/forum/showthread.php?75460-My-floppy-remapper-project-version-2

## Design and PCB files (how to make boards)

1. [design files](/design): (schematic and pin map)
1. [PCB files](/design/pcb_info): (gerbers, bill of material, centroid)

## Programming information

You can build a programmable image from source, or use the pre-built image I've supplied.

[Programming files](/program): (MPLAB project source code and compiled HEX file)

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

## Programming using a PICKit 4

Note: This board has no external power supply.  In order to program it, power
must be supplied by the programmer.

1. Under project properties, select PICKit 4
1. Select Options category: Power
1. Select "power target circuit from PICKit 4"
1. Click Apply

Connect the programmer and program the board:

1. Connect the 6 pin programming header of the PICKit 4 to the remapper board.  Please be careful to orient
   programming header to match the board pins!  Look for the MCLR pin with an arrow on it.  The 6th pin
   of the PICKit 4 header is not used and will not connect to anything.  Nothing should be
   connected to the two "Run mode" jumper pins. 
1. Click Program device in the IDE

![prog-header-v3](/images/prog-header-v3.jpg)

## Board self tests

After programming (unless held in reset) the PIC will automatically boot and run a
one-time series of self tests.  This is mostly to test the software and
also verifies the PIC is working correctly.

The LEDs will flash through a set of patterns which will take about 15 seconds.

At the end, all of the LEDs should remain lit, with the enable LED flashing slowly.
This indicates the tests passed and confirms all the LEDs are working.

Download programming video here: ![programming-v3](/images/programming-v3.mp4)

The next time the PIC boots, it will assume it has been installed into a TRS-80 and
will start working normally.  If you boot the PIC without having it installed, the
board may behave unpredictably due to floating inputs (although there is no harm).

At the end of the tests, if an error is found, all of the LEDs will flash in an
alternating pattern.  This means there is either a bug in the code or a problem with
the board.  Either way, this needs to be fixed. If you try to install the board
into a computer, it will refuse to work (as the error status is saved into EEPROM).
In order to re-run the tests, you must re-program the PIC.

## Front LEDs

![leds-v3](/images/leds-v3.jpg)

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

![jumpers-v3](/images/jumpers-v3.jpg)

The "Run mode" jumper must be installed before installing the floppy remapper board
(i.e. whenever you aren't trying to program it).

The "M4P mode" jumper should be installed when installing the flopper remapper
into a TRS-80 Model 4P computer **and** you want to add support for external
floppy drives.  Otherwise, this jumper can be left off.

M4P mode (v.s. non-M4P mode) will be indicated by the flashing pattern of the
row light.  When in M4P mode, the selected row light will "double" flash.  Otherwise
the selected row light will slowly flash.

The flashing of the row light also tells you that the MCU is heathy.

## Front headers

![front-header-v3](/images/front-header-v3.jpg)

An optional disable switch (e.g. SPST) may be installed.  When these pins
are shorted, floppy drive re-mapping will be disabled.

When in M4P mode, the ~DS2 and ~DS3 pins should be connected to a special
floppy drive cable and routed to an external connector out of the back
of the M4P computer.  This provides support for external floppy drives
just like on the Model 3 and 4 computers.

For Model 4 gate array and Model 4P non-gate array computers, an extra
motherboard modification is required.  This is what the third pin on the
output signal header is for (see installation instructions below).

## Floppy cable build instructions (Model 4P only)

On the Model 4P, you'd need a custom floppy cable which adds an external interface for two floppy drives.  This also connects to the remapper board, providing the drive select lines for the external drives:

![floppy_cable2](/images/floppy_cable2.jpg)

Start with a 24" IDC 34-pin IDC extension cable.  This has a male and female 34 pin connector on each end:

https://www.ebay.com/itm/24-inch-34-Pin-IDC-Floppy-Drive-Ribbon-Extension-Cable-Cord-CablesOnline-FF-004/270837785829

You also need two floppy drive connectors (34-pin card edge female IDC), I ordered a bag here:

https://www.ebay.com/itm/5Pack-34-Pin-Card-Edge-Female-IDC-Connector-for-2-54mm-Pitch-Flat-Ribbon-Cable/272723281626

Steps:

1. Remove your existing floppy cable from the M4P.  This is useful for sizing purposes only.  You do not need to modify it.  Keep it for backup purposes!
1. Carefully remove the female connector from the 24" extension cable.  You need to reuse this connector.  Trim off the damaged part of the ribbon cable.
1. (Using a vise) carefully install two female card edge connectors and the one female IDC connector (removed above) at approximately the same locations (separation) as your original floppy cable.  You'll now have a cable that looks like your original, except that the cable continues past where it normally connects to the M4P motherboard.  This part will go out the back of the model 4P.
1. Look at your original floppy cable Female card edge connectors.  If you see that some connectors have been removed (most likely), you will have to remove the same connectors from the new cable.  Mine pulled out with pliers easily.  The missing pins allows the connector to determine which drive is 0 and which drive is 1.  Look carefully at the following image noting the missing pins:

![floppy_card_edge](/images/floppy_card_edge.jpg)

1. Using an X-acto knife, carefully separate out drive select 0 and 1 (pins 10 and 12) from the floppy cable just after the female IDC connector.  These lines should lead towards the male IDC connector.  It is okay if you just cut pin 11 as it is a redundant ground.
1. Connect a two wire ribbon cable to pins 10 and 12.
1. Connect the other end of the two pin ribbon cable to a 2 pin dupont header.

The spliced in wire should like this (ignore the extra cuts on pins 6 and 14 I made, these aren't necessary):

![floppy_cable1](/images/floppy_cable1.jpg)

## Installation of the socket for the remapper board (common on all models)

Important notes before you get started:
1. The remapper board replaces (emulates) a 74LS174 Hex D-Flip flop on the floppy
controller board or motherboard (depending on your model).  You need to locate this specific IC (in case there are more than
one 74LS174) on your model of computer.  As there are differences between board revisions,
even for the same model of computer, I cannot tell you which chip (i.e. Uxx) is the correct one.
To make matters worse, there are errors in the Radio Shack schematics which incorrectly label some
of these chips.  Also, these schematics may not account for board revisions.  However, I'll list what I know
and offer some ways to confirm you have the right IC.  **This is just a long way of saying double
check you have the right IC before you start!**
1. Depending upon which model of TRS-80 you have (and what options), there isn't much room
to install the remapper board (considering adjacent components, vertical clearance, etc).
In particular, the graphics boards on the Model 4/4P and serial board on the M4P, do
come very close to the remapper board.  I've tried to carefully design the PCB so that it works in all of the
computers that I have.  However, it is possible
that it won't work for you.  So the first issue you need to be concerned about is the fit
and to ensure that nothing will rub, touch or potentially short out.  **Again, a long way of saying,
double check the physical fit of the remapper board before you start (especially on the M4P)!**.
1. If there is any possibility of a short between the remapper board and something close by,
use some insulation (like kapton tape), just to be safe.  Pay close attention to the M4P as it
is very tight when assembled.
1. It is likely, unless you are very careful, you may destroy your 74LS174 when removing it from the board.
It is a good idea to have a few known good spares (and extra sockets), just in case.
1. The nice thing about installing a socket is that you can always put a new 74LS174 back in
to revert this modification.

For reference, here are the IC numbers from my computers (your computer may be different!):

Computer | Board revision | IC
------------ | ------------- | ------------
TRS-80 M3 | unknown | U6
TRS-80 M4 GA | unknown | U79
TRS-80 M4P GA | unknown | U34

Steps:
1. Locate the 74LS174 IC which handles the drive select lines.  The best way to be certain
is to bring up a copy of the relevant schematic from your computer and check
some pins with an ohmmeter.
1. Here is an example from a M4P GA:
![m4p-ga-schem](/images/m4p-ga-schem.jpg)
1. The yellow circle highlights some of the key the floppy signals (such as drive select, etc).
This tells us we are in the right area.
1. The green circle highlights the actual floppy disk controller chip, and is also a good indicator we
are in the right place.
1. Finally, the red circle represents the 74LS174 which latches the floppy signals.  This is the IC we want
want to remove and replace with a socket.
1. Note that if you look at the reference designator on my schematic (U54), it does not match my board.
This kind of mistake is easy to spot since we are looking for a 74LS174.
1. Confirm you have the right IC by checking the connections with adjacent chips.  For example, in the schematic
above the blue circle shows that the DRVSEL line of the floppy support gate array (pin 15) should
be connected directly to pin 9 of the 74LS174.  If you validate a few of these connections, you can
be certain you have the right IC.
Here is an image of my board with the correct IC circled in red:
![m4p-ga-ic](/images/m4p-ga-ic.jpg)
1. Carefully desolder the IC.  I used a desoldering tool to minimize damage to the
board.  Clipping the pins off of the 74LS174 is easier, but destorys the chip.  Be careful
not to damage any of the traces.
1. Solder in a quality replacement socket, preferably one with machine pins.
1. If you want to double check that you haven't damaged anything, you can insert the
74LS174 back in to confirm that your computer still works.

## Installation of an (optional) disable switch (common on all models)

Notes:
1. As the floppy maps are software selectable, having an
external switch to disable the board isn't strictly necessary.  However, I find it adds to the convenience.  The downside is
that you likely need to drill a hole into your case and you have more hardware to make and install.
1. WARNING: The M4P does have one quirk in that it does not have BASIC built into ROM.  This means
that you could theoretically get yourself into trouble with the remappper board if you configured it
to boot from a non-existant floppy (and also saved this as your power on default).  If you did this, you'd
be unable to boot.  Obviously there are ways to recover, but in the worst case, you may need to dissasemble
your M4P to get at the remapper board. This might be a reason enough to install a disable switch on a M4P.
1. I like physical switches so I've installed them anyway.  IMO: the case mod is minor (one hidden drill hole),
and it justifies my purchase of a fancy label maker (ok, this is the real reason).

Steps:
1. Using a SPST switch, two-conductor wire, and a 2-pin dupont header, assemble a disable switch like what is shown below:
![disable-switch](/images/disable-switch.jpg)
1. Find a good place to mount the switch.  On my Model 3 and 4, I put them on the right side near the back.  The wire
only has to be long enough to reach the remapper board.  On my Model 4P, I installed the switch in the recessed
back compartment.
![disable-switch](/images/disable-top.jpg)
2. For the sake of future owners, put a label on the switch (and so you don't forget what it does).
![disable-switch](/images/disable-bottom.jpg)

## Installation in a Model 3 or Model 4 (non-gate array)

1. Disassemble your TRS-80 so that you have access to the floppy disk controller board.
1. Install a socket for the remapper board (refer to instructions above).

![Model 3](/images/install-m3-v3.jpg)

1. Plug in the remapper board into the socket.
1. (optional) connect your disable switch to the remapper board.
1. Put your TRS-80 back together.

## Installation in a Model 4 Gate array

1. Disassemble your TRS-80 so that you have access to the motherboard board.
1. Install a socket for the remapper board (refer to instructions above).
1. Plug in the remapper board into the socket.

![Model 4](/images/install-m4-v3.jpg)

1. Make a simple one pin jumper with a grabber connector on one end and dupont header on the other.
1. Plug in the remapper board into the socket.
1. WIP ... Locate the EXTBUS signal... this goes to pin 1 of ...., this is U95 on my board.  Cut the trace above pin 1 of U95
1. Connect the grabber connector to pin 1 of U95.  Connect the other end to the EXTBUS output of the remapper board.
1. (optional) connect your disable switch to the remapper board.
1. Put your TRS-80 back together.

## Installation in a Model 4P Gate array

1. Disassemble your TRS-80 so that you have access to the motherboard board.
1. Install a socket for the remapper board (refer to instructions above).
1. Plug in the remapper board into the socket.
1. Install the custom floppy cable into the M4P, replacing your original cable.
1. Connect the dupont header to the floppy remapper board.  Note that pin 10 should connect to ~DS2 and pin 12 should connect to ~DS3.

![Model 4P](/images/install-m4p-v3.jpg)

1. The rest of the floppy cable can be routed out the back of the M4P.

![floppy_cable_back](/images/floppy_cable_back.jpg)

1. (optional) connect your disable switch to the remapper board.
1. Put your TRS-80 back together.

## Installation in a Model 4P (non-gate array)

Sorry, I don't have one of these yet...

## Other TRS-80 Models

TBD

## Changing the drive mapping

TBD

## Using the disable switch

To avoid unexpected behaivor (i.e accidents), if any drive is currently
active when the disable switch is toggled, the mapping will not be changed.
As soon as the drive stops, the new mapping state will take effect.

## Theory of operation

TBD



