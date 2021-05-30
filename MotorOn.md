# TRS-80_floppy_remapper

## Enabling selective Motor Control (optional)

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

