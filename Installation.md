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
and bend up pin 1 (as very cleanly done by pski [here](http://www.vcfed.org/forum/showthread.php?75460-My-floppy-remapper-project-version-2&p=635048#post635048)).  Or, you could carefully cut pin 1, bend it up slighty, and solder a
wire to it.  If I had to do this over again, I like these last two options
much better than cutting a trace.  Hindsight is 20/20.
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

**Unverified! I don't have a TRS-80 M4P non-gate array, so the following is just based on the schematic.**

Note: due to the chip spacing, I suspect the remapper board (if at U32), might end up being
under the graphics option board (if present).  I am really curious to find out if this will
work (or what adjustment might be needed).  At the very least, Kapton tape may be needed
to avoid a short.

Please follow the same steps as the 4P Gate array (see above).

Additionally, you will need to hook up the extra output pin (labeled HLT/RDY) on the remapper board:

1. Open up a schematic of the M4P Non-Gate array:
<br/>![Model 4p non-ga schematic](/images/m4p-nonga-schem.jpg)
1. **Please confirm your board matches this schematic, or find the equivalent chips and pins.**
1. In the diagram above, U32 (red circle) should be the 74LS174 which needs to be socketed.  The Green circle
is a NOR gate which combines drive select 0 and 1, this is fed into an inverter (yellow circle) and
finally drives the HLT/RDY signals (blue circle) on floppy disk controller IC.
1. I recommend cutting pin 12 of U74 (yellow circle) and slightly bending the pin up so
that it no longer makes contact with the motherboard.  This will interrupt
the signal to the floppy controller.
1. WARNING: if you want to revert this modification, you can carefully bend the pin
back down to resolder it to the motherboard.  In the worst case,
you can simply replace the IC.  This is the least invasive modification that
I can think of and (IMO) is definitely better than cutting a trace on the motherboard.
1. Create a single wire jumper, with a grabber on one end and dupont header on the other.  See the M4 GA installation instructions above as an example.
1. Connect the grabber end to either pin 23 or pin 32 (pick one) of the floppy disk controller (U13).
1. Connect the other end of the jumper wire to the 3rd pin of the remapper board labelled (HLT/RDY).
1. Note: This wire allows the remapper board to drive HLT/RDY based on all four drive select lines instead of the 2 supported in the original design.

## Other TRS-80 Models

TBD
