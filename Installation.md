# TRS-80_floppy_remapper

## Installation in a Model 3 or Model 4 (non-gate array)

1. Disassemble your TRS-80 so that you have access to the floppy disk controller board.
1. Install a socket for the remapper board.  See U6 in this image below:
<br/>![Model 3](/images/install-m3-v3.jpg)
1. Connect the "Run mode" jumper on the back of the remapper board.
1. Plug in the remapper board into the socket.
1. (optional) connect your disable switch to the remapper board.
1. Note: The 3-pin output signals on the remapper board are not needed for this computer.
1. Put your TRS-80 back together.

## Installation in a Model 4 Gate array

1. Disassemble your TRS-80 so that you have access to the motherboard.
1. Install a socket for the remapper board.
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
1. Install a socket for the remapper board.
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
