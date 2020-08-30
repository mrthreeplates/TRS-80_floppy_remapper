# TRS-80_floppy_remapper

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

