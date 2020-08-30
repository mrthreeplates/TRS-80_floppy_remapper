# TRS-80_floppy_remapper

![front of board](/images/front-v3.jpg)![back of board](/images/back-v3.jpg)

## Introduction

This board dynamically remaps the floppy disk drives (e.g. 0 through 3) in vintage
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
requiring the fewest (and least invasive) modifications possible.

**WARNING**: This project requires some soldering and assumes you are very comfortable working around
electronics.  Lethal voltage levels are present inside these computers, so please be safe!
I make no claim that the information below is complete, correct, easy to follow, you won't
damage your computer, etc.  If any of this worries you at all, this project isn't for you.

## Model 4P GA booting directly from an external floppy emulator

![Model 4P GA booting](/images/m4pga-boot.jpg)

### More information and background about this project:

* [VCF Thread on V3](http://www.vcfed.org/forum/showthread.php?75460-My-floppy-remapper-project-version-2)
* [VCF Thread on V1](http://www.vcfed.org/forum/showthread.php?70726-Booting-from-an-external-floppy-on-a-model-III&p=606759#post606759)

## V3 Design and PCB files (how to make boards)

* [design files](/design): (schematic and pin map)
* [PCB files](/design/pcb_info): (gerbers, bill of material, centroid)

Note: at this time, I don't have an easy way to order pre-assembled boards.  However, all the
files needed to have them made are listed above.  FWIW: I've had good results using PCBWay for
all of my prototypes.

If you are looking to build a simpler version of a floppy switch (not programmable
and without M4P / M4 GA support), you can read about my earlier version here:
* [V1 build info](http://www.vcfed.org/forum/showthread.php?70726-Booting-from-an-external-floppy-on-a-model-III&p=603230#post603230)

## V3 Programming information

The following assumes you are familiar with using [MPLAB X IDE](https://www.microchip.com/mplab/mplab-x-ide).
If you are not, you might want to check out some tutorials on YouTube.

You can make a programmable image from source, or use the pre-built image I've supplied.

* [Programming files](/program) (MPLAB project source code and compiled HEX file)

How to build from source:

1. Create a new project using MPLAB X IDE based on a PIC18F26Q10.
1. Under your projects tab, "Important Files", right click to "Add item to important Files"
   Select "MyConfig.mc3" from this repo and add it.
   For help see [Adding an Existing Configuration File to a Project](https://microchipdeveloper.com/mcc:mcc-config).
1. Open MCC
1. Click "Generate".  You should now have a list of "mcc_generated" files now, including
   a default "main.c".
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

1. Connect the 6 pin programming header of the PICKit 4 to the remapper board.  Please
carefully align the
   programming header to match the board pins!  Look for the MCLR pin with an arrow on it.  The 6th pin
   of the PICKit 4 header is not used and will not connect to anything.  Nothing should be
   connected to the two "Run mode" jumper pins. 
1. Click Program device in the IDE

<br/>![prog-header-v3](/images/prog-header-v3.jpg)

## Self tests

After programming (unless held in reset) the PIC will automatically boot and run a
one-time set of self tests.  This will test the software and
also verifies the PIC is working correctly.

The LEDs will flash through a set of patterns which will take about 15 seconds.

At the end, all of the LEDs should remain lit, with the enable LED flashing slowly.
This indicates the tests passed and also helps you confirm all the LEDs are working.

View the programming video here: ![programming-v3](/images/programming-v3.mp4)

The next time the PIC boots, it will assume it has been installed into a TRS-80 and
will start working normally.  If you boot the PIC without having it installed, the
board may behave unpredictably due to floating inputs (although there is no harm).

At the end of the tests, if an error is found, all of the LEDs will flash in an
alternating pattern.  This means there is either a bug in the code or a problem with
the board.
In order to clear the error, you must fix the problem and re-program the PIC.
If you accidentally try to install the board
into a computer, it will refuse to work (as the error status is saved into EEPROM).

## Front LEDs

![leds-v3](/images/leds-v3.jpg)

The LEDs are there to tell you that the board is alive, show you the current configuration,
and for [Blinkenlights](https://en.wikipedia.org/wiki/Blinkenlights).

It is unfortunate you can't see the LEDs when the computer is assembled.  Truthfully, the LEDs are optional and could be removed (along with the current limiting resistors) to save cost.
However, what would be the fun in that?

The Green "Enable" LED will be lit whenever the disable switch is not closed.

The Red row (and "Bank") LEDs show you which mapping is currently selected.
For example, when the first row LED is lit (next to "0 1 2 3") and the right "Bank" LED is off,
then the mapping of drives will be unchanged.

The row light will flash periodically to indicate that the PIC controller is alive.  The
pattern of flashing tells you if the board is in "M4P mode" or not (see jumpers below).  When
the "M4P mode" jumper is installed, the row light will double flash.  Otherwise,
the row light flashes on/off regularly.

There is a "Default" mapping which is restored
upon power on of the computer.  This can be any one of the 8 pre-programmed
drive maps.  Whenever the current mapping matches this saved mapping, the Blue LED
next to "Default" will be lit.

## Back jumpers

There are two jumpers on the back of the board (on the same header used for programming).

<br/>![jumpers-v3](/images/jumpers-v3.jpg)

The "Run mode" jumper must be installed for normal operation
(i.e. whenever you aren't trying to program it).

The "M4P mode" jumper should be installed when installing the remapper
into a TRS-80 Model 4P computer.  This jumper changes the way the PIC drives
some of the output signals (there is more info on this below).

## Front headers

![front-header-v3](/images/front-header-v3.jpg)

An optional disable switch (e.g. SPST) may be installed.  When these pins
are shorted, the floppy drive re-mapping will be effectively disabled.

When in M4P mode, the ~DS2 and ~DS3 pins should be connected to a special
floppy drive cable and routed to an external connector out of the back
of the M4P computer.  This provides support for external floppy drives
(just like on the Model 3 and 4 computers).

For Model 4 gate array and Model 4P non-gate array computers, an extra
motherboard modification is required.  This is what the third pin on the
output signal header is for (see installation instructions below).

## Floppy cable build instructions (Model 4P only)

On the Model 4P, you'll need to make a custom floppy cable which adds an externally accessible interface for two floppy drives.  This is the exact equivalent of the card edge connector on the bottom of Model 3 and Model 4 computers.  This custom cable also connects to the remapper board, which provides the necessary drive select lines for the external drives:

<br/>![floppy_cable2](/images/floppy_cable2.jpg)

Start with a 24" IDC 34-pin IDC extension cable.  This has a male and female 34 pin connector on each end:

https://www.ebay.com/itm/24-inch-34-Pin-IDC-Floppy-Drive-Ribbon-Extension-Cable-Cord-CablesOnline-FF-004/270837785829

You also need two floppy drive connectors (34-pin card edge female IDC), I ordered a bag here:

https://www.ebay.com/itm/5Pack-34-Pin-Card-Edge-Female-IDC-Connector-for-2-54mm-Pitch-Flat-Ribbon-Cable/272723281626

Steps:

1. Remove your existing floppy cable from the M4P.  This is useful for sizing and reference purposes only.  You do not need to modify it.  Keep it as a backup!
1. Carefully remove the female connector from the 24" extension cable.  You will need to reuse this connector.  Trim off the damaged part of the ribbon cable.
1. (Using a vise) carefully install two female card edge connectors and the one female IDC connector (removed above) at approximately the same locations (separation) as your original floppy cable.  You'll now have a cable that looks like your original, except that the cable continues past where it normally connects to the M4P motherboard.  This part will go out the back of the model 4P.
1. Look at your original floppy cable Female card edge connectors.  If you see that some pins have been removed, you will have to remove those same pins from your new cable.  The pins should pull out easily with pliers.  The missing pins determine which connector is drive 0 and which is drive 1.  Look carefully at the following image (as an example only) noting the missing pins:
<br/>![floppy_card_edge](/images/floppy_card_edge.jpg)
1. Using an X-acto knife, carefully separate out drive select 0 and 1 (pins 10 and 12) wires from the floppy cable just after the female IDC connector.  These wires should lead towards the male IDC connector.  It is okay if you cut wire 11 as it is a redundant ground.
1. Connect a two wire ribbon cable to wires 10 and 12.
1. Connect the other end of the two wire ribbon cable to a 2 pin dupont header.

The spliced in wire should like this (please ignore the extra cuts on wires 6 and 14, these aren't necessary):

<br/>![floppy_cable1](/images/floppy_cable1.jpg)

## Installation of the socket for the remapper board

Important notes before you get started:
1. The remapper board replaces (emulates) a 74LS174 Hex D-Flip flop on the floppy
controller board or motherboard (depending on your model).  You need to locate this
specific IC (in case there happens to be more than one 74LS174).
As there are differences between board revisions,
I cannot tell you which chip (i.e. Uxx) is the correct one.
To make matters worse, there are errors in the Radio Shack schematics which incorrectly label some
of these chips.  Also, these schematics may not account for different board revisions.  However,
I'll list what I know below and suggest a way to confirm you have the right IC.  **Please, double
check you have the right IC before you start!**
1. Depending upon which model of TRS-80 you have (and what options), there isn't much room
to install the remapper board (considering adjacent components, vertical clearance, etc).
In particular, the optional graphics board on a Model 4/4P and serial board on the M4P,
come very close to the remapper board.  I've tried to carefully design the PCB so that it works
in all of the computers that I have.  However, it is possible
that it won't work for you.  **Please,
double check the fit of the remapper board before you start (especially on the M4P)!**.
1. If there is any possibility of a short between the remapper board and something close by,
use some insulation (like kapton tape), just to be safe.  Pay close attention to the M4P as it
is very tight when assembled.
1. It is likely, unless you are very careful, you may destroy your 74LS174 when removing it from the board.
It is a good idea to have a few spares (and extra sockets), just in case.
1. The nice thing about using a socket is that you can always put a new 74LS174 back in
to revert this modification.

For reference, here are the IC numbers from my computers (your computer may be different!):

Computer | Revision | Socket | Additional mod needed
------------ | ------------- | ------------ | -----------
TRS-80 M3 | unknown | U6 | None
TRS-80 M4 non-GA | ? | U6? | None
TRS-80 M4 GA | unknown | U79 | cut trace to U95, pin 1
TRS-80 M4P non-GA | ? | U32? | ?cut trace from U74, pin 12?
TRS-80 M4P GA | unknown | U34 | None

Steps:
1. Locate the 74LS174 IC which handles the drive select lines.  Look at your schematic and use an ohmmeter to confirm you have the right chip.
1. Here is an example from a M4P GA (please substitute the schematic from your computer model!):
<br/>![m4p-ga-schem](/images/m4p-ga-schem.jpg)
1. The yellow circle highlights some of the key the floppy signals (such as drive select, etc).
This tells us we are in the right area.
1. The green circle highlights the floppy disk controller chip, and is also a good indicator we
are in the right place.
1. The red circle represents the 74LS174 which latches the floppy signals.  This is the IC we want
want to remove and replace with a socket.
1. Contrary to what the schematic says, U54 is not the right IC on my board as you'll see below.
1. You can confirm you have the right IC by checking the connections with adjacent chips.  For example, in the schematic
above, the blue circle shows that the DRVSEL line of the floppy support gate array (pin 15) should
be connected directly to pin 9 of the 74LS174.  If you validate a few of these connections, you can
be certain you have the right IC.
Here is an image of my board with the correct IC (U34) circled in red (again, this is from a M4P GA):
<br/>![m4p-ga-ic](/images/m4p-ga-ic.jpg)
1. Now that you know the correct IC, carefully desolder it using your preferred method.  Be
careful not to damage any of the traces.
1. Solder in a quality replacement socket, preferably one with machine pins.
1. Confirm you haven't damaged anything by temporarily putting the 74LS174 into the socket
to verify that your computer and floppy drives still work.

## Installation of an disable switch (optional)

Notes:
1. As the floppy maps are software selectable, having an
external switch to disable the board isn't strictly necessary.  However, I find it adds to the convenience.
1. WARNING: The M4P does have one quirk in that it does not have BASIC built into ROM.  This means
that you could theoretically get yourself into trouble with the remappper board if you configured it
to boot from a non-existant floppy (and also saved this as your power on default).  If you did this, you'd
be unable to boot.  Obviously there are ways to recover, but in the worst case, you may need to dissasemble
your M4P to get at the remapper board. This might be a reason enough to install a disable switch on a M4P.
1. I like physical switches so I've installed them anyway.  IMO: the case mod is minor (one hidden drill hole),
and it justifies my purchase of a fancy label maker (ok, this is the real reason).

Steps:
1. Using a SPST switch, two-conductor wire, and a 2-pin dupont header, assemble a disable switch like what is shown below:
<br/>![disable-switch](/images/disable-switch.jpg)
1. Find a good place to mount the switch.  On my Model 3 and 4, I put them on the right side near the back.  The wire
only has to be long enough to reach the remapper board.  On my Model 4P, I installed the switch in the recessed
back compartment.
<br/>![disable-switch](/images/disable-top.jpg)
2. For the sake of future owners, put a label on the switch (and so you don't forget what it does).
<br/>![disable-switch](/images/disable-bottom.jpg)

## Installation in a Model 3 or Model 4 (non-gate array)

1. Disassemble your TRS-80 so that you have access to the floppy disk controller board.
1. Install a socket for the remapper board (refer to instructions above).  See U6 in this image below:
<br/>![Model 3](/images/install-m3-v3.jpg)
1. Connect the "Run mode" jumper on the back of the remapper board.
1. Plug in the remapper board into the socket.
1. (optional) connect your disable switch to the remapper board.
1. Note: The 3-pin output signals on the remapper board are not needed for this computer.
1. Put your TRS-80 back together.

## Installation in a Model 4 Gate array

1. Disassemble your TRS-80 so that you have access to the motherboard.
1. Install a socket for the remapper board (refer to instructions above).
1. Connect the "Run mode" jumper on the back of the remapper board.
1. Plug in the remapper board into the socket.
<br/>![Model 4ga](/images/install-m4ga-v3.jpg)
1. You will need to create a one pin jumper wire with a grabber connector on one end and dupont header on the other.
This is the yellow wire in the image above.
1. Open up a schematic of the M4 GA (RS cat 26-2119, figure 2-24):
<br/>![Model 4ga schematic](/images/m4-ga-schem.jpg)
1. The 74LS174 is circled in red.  Note that there is a control line (EXTSEL)
which selects between the internal and external floppy disk connectors. This is driven
by the floppy disk gate array (U76, pin 20) and connects
to an output mux (U95, pin 1).  Both ends are circled in blue.
1. **Please confirm your board matches this schematic, or find the equivalent chips and pins.**  It is the
output mux that the remapper needs to control.
1. Cut the trace leading to pin 1, U95.  I did this just before U95, but
it could be done anywhere between U76 and U95.
1. WARNING: If you ever want to reverse
this modification, you'll have to re-bridge this cut!  So you might
want to think about your options here.  Another solution would be to socket U95
and bend up pin 1.  Or, you could carefully cut pin 1, and bend it up slighty, and solder a
wire to it.  If I had to do this over again, I like these last two options
better than cutting a trace.  Hindsight is 20/20.
1. Regardless of the method you use, connect one end of the wire to pin 1, U95 (which should be
isolated from the motherboard).
1. Connect the other end of the wire to the output signal pin on the remapper board labeled EXTSEL.
1. Note: the remaining 2 pins on the output signal header are not used on the M4GA.
1. (optional) connect your disable switch to the remapper board.
1. Put your TRS-80 back together.

## Installation in a Model 4P Gate array

1. Disassemble your TRS-80 so that you have access to the motherboard.
1. Install a socket for the remapper board (refer to instructions above).
1. Connect both "Run mode" and "M4P mode" jumpers on the back of the remapper board.
1. Plug in the remapper board into the socket.
1. Install the custom floppy cable into the M4P, replacing your original cable.
1. Connect the dupont header to the floppy remapper board.  Note that pin 10 should connect to ~DS2 and pin 12 should connect to ~DS3.  If you get it backwards, the external drives will be reversed.
The other pin on the output header is not used on the M4P GA:
<br/>![Model 4P](/images/install-m4p-v3.jpg)
1. The rest of the floppy cable can be routed out the back of the M4P.
<br/>![floppy_cable_back](/images/floppy_cable_back.jpg)
1. (optional) connect your disable switch to the remapper board.  Note where the disable switch is mounted in the above picture.  This seemed to me the most logical place for it.
1. Put your TRS-80 back together.

## Installation in a Model 4P (non-gate array)

WIP ... Sorry, I don't have one of these yet, so this is all TBD...

The install steps are similar to the M4P GA, except an additional mod is needed, similar to the M4 GA above.

The HLT/RDY Jumper needs to go to U13 pin 23/32 (or possibly U74/U75).  I need to examine a board to determine which is best.

Note: due to the chip spacing, I suspect the remapper board (if at U32), might have to fit
under the graphics option board (if one is present).  Hopefully there is enough space.
Kapton tape may be needed...

## Other TRS-80 Models

TBD

## Changing the drive mapping

Wow, you got this far, congratulations!  Here comes the fun stuff.

There are 8 pre-programmed (fixed) floppy drive mappings numbered 0 through 7:

Map number | Drive 0 | Drive 1 | Drive 2 | Drive 3 | Comment
------------ | ------------- | ------------ | ----------- | ----------- | ----------
#0 | 0 | 1 | 2 | 3 | No change to drive mapping or boot drive
#1 | 1 | 0 | 2 | 3 | Swap drives 0 and 1 only, boot from drive 1
#2 | 2 | 0 | 1 | 3 | Boot from drive 2
#3 | 3 | 0 | 1 | 2 | Boot from drive 3
#4 | 0 | 2 | 1 | 3 | Swap drives 1 and 2 only, boot from drive 0
#5 | 1 | 2 | 0 | 3 | Boot from drive 1
#6 | 2 | 3 | 0 | 1 | Swap 0/1 with 2/3, boot from drive 2
#7 | 3 | 2 | 0 | 1 | Swap 0/1 with 3/2, boot from drive 3

While other drive mappings are possible (24 to be exact), I think
restricting the possibilities to 8 of the most useful is a
reasonable trade-off to gain simplicity.  If your desired
mapping isn't listed above, the source code can be easily modified
as it is just a table in C.

Note: in the map list, the boot drive equals the map # modulo 4.
The first 4 maps are the ones I thought most useful and
I added the second 4 maps as alternates.  This hopefully
will make the desired map # easier to remember.  A printed
cheat sheet for the out commannd is probably still a good idea.

Whenever the disable switch is shorted, the remapper board
will not affect the drive mapping (i.e map #0 is forced).

The remapper board maintains both the current map number
and a default map number.

At first power on (of the TRS-80), the default map number is restored from EEPROM.
This could be any of the 8 mappings.  Upon first programming the PIC, this
default map number is 0.

The current mapping as well as the default mapping is changed via an out instruction
(most easily done in basic).  The command to use is:

    out 244, 3 + map# * 4

The change will take place immediately (as long as disable switch isn't shorted).  The
drive motors will turn on for 2 seconds as a harmless side effect (see Theory of operation
below for what is really going on).

Note that the current map will be remembered even if the TRS-80 reboots or is reset (as long as the remapper board has power).
When the TRS-80 is powered off, the current map will be forgotten.

If you want to also make a map# default for power up, then add 128 as follows:

    out 244, 3 + map# * 4 + 128

If you can actually see the remapper board, the current enable state, current map,
and default map status will be visible on the LEDs.  This lets you confirm the out
instruction is doing what you want (and is kinda fun).  This is most easily done
on the Model 4 GA (and harder to do on the M4P and M3/M4 non GA).

It is likely a good idea to reset the computer after changing the drive mapping
or else you may confuse whatever DOS your are running.

If you want to verify that the mapping is as you expect, use the dir
command or one of the following the out commands:

Command | effect
--------| -------
out 244, 1 | turn on drive 0 for 2 seconds
out 244, 2 | turn on drive 1 for 2 seconds
out 244, 4 | turn on drive 2 for 2 seconds
out 244, 8 | turn on drive 3 for 2 seconds

Don't try to set more than one drive at a time with the above command, as this is the "trick"
to how the remapper works.

Also, I wouldn't issue any of the above out commands while a drive is in use (if this
is even possible).  This would likely have unintended consequences (i.e. could
corrupt whatever i/o is in progress).

## Using the disable switch

The switch should behave as you expect, with one caveat.

To avoid unexpected behaivor (i.e accidents), if any drive is currently
active when the disable switch is toggled, the mapping will not be changed.
As soon as the drive stops, the new mapping state will take effect.

## TODO list / stuff I'd like to fix in V3

1. LED brightness is still not exactly right (green is still a touch bright,
blue is a touch too dim, reds are about right).
1. I'd like to eventually make my own boot roms to allow for keyboard selection of the boot drive.
This would completely eliminate any need for the disable switch (and be very convenient).

## Theory of operation

TBD
