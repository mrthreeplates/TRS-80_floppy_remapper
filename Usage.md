# TRS-80_floppy_remapper

## Changing the drive mapping

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
as it is just an array.

Notice that, in the map list, the boot drive always equals the map # modulo 4.
The first 4 maps are the ones I thought most useful and
I added a second set of 4 maps as alternates.  This hopefully
will make the mappings easier to remember.  I suspect that a printed
cheat sheet is probably still a good idea.

The remapper board maintains both the current map number
and a default map number (which can be different).

The current mapping is always displayed on the row and bank LEDs
(unless overidden by the disable switch).  If
the current map matches the default saved map, then the default LED
will be lit.

At first power on (of the TRS-80), the default map number is restored from EEPROM.
Upon first programming the PIC, this default map number is set to 0.

The current mapping as well as the default mapping is changed via an out instruction
(most easily done in basic).  The command to use is:

    out 244, 3 + map# * 4

Replace 'map#' with a number from 0 through 7.

The map change will take place immediately (as long as disable switch isn't shorted).  The
drive motors will turn on briefly as a harmless side effect (see Theory of operation).

Note that the current map will be used even if the TRS-80 reboots or is reset
(just as long as the remapper board has power).  This is useful to set
a temporary mapping which you want reverted later.

When the TRS-80 is powered off, the current map will be forgotten.

If you want to make a map# default for power up, then add 128 as follows:

    out 244, 3 + map# * 4 + 128

FYI: Here is a quick explaination of where the '3', '4' and '128' magic numbers come from.
The PIC is monitoring the 6-bits of the Hex D Flip-flop.  I use the low two bits
as a flag to the PIC that I am actually sending a new mapping (that is where the 3 comes from).
The next 3 bits encodes the map # (multiplying by 4 does the 2 bit shift needed).  Adding
128 (setting bit 7), is the flag that tells the PIC to save the map into EEPROM.  More
detail is in the Theory of operation section.

If you can actually see the remapper board (with the computer on), the enable state, current map,
and default map status will be visible on the LEDs.  This lets you confirm the out
instruction and disable siwtch are doing what you want (and is kinda fun).  This is
most easily done on the Model 4 GA.

It may be a good idea to reset the computer after changing the drive mapping.
This will depend on wether or not the DOS your are running will get confused
by the change in floppy drives.

If you want to verify that the mapping is as you expect, use the dir
command or one of the following the out commands:

Command | effect
--------| -------
out 244, 1 | turn on drive 0 for 2 seconds
out 244, 2 | turn on drive 1 for 2 seconds
out 244, 4 | turn on drive 2 for 2 seconds
out 244, 8 | turn on drive 3 for 2 seconds

Don't try to set more than one drive at a time (by OR'ing the drive select bits together)
with the above command, as this is the "trick" to how the remapper works (and may be
interpreted as setting the map # as described above).

Also, I wouldn't recommend sending any of the above out commands while a drive is
actually in use doing i/o (if this is even possible?).

## Using the disable switch

Whenever the disable switch is shorted, the remapper board
will not affect the drive mapping (i.e effectively map #0 is forced).

Note: You can still set the current and default mapping
even with the disable switch shorted (the change just won't
take effect until the disable switch is unset).

To avoid unexpected behaivor (i.e accidents), if any drive is currently
active when the disable switch is toggled, the mapping will not be changed.
As soon as the drive stops, the new mapping state will take effect.

I've added a hardware debounce circuit, so noisy switch contacts
shouldn't be a problem.  I've not been able to confuse the
PIC by toggling the switch rapidly, but this isn't something
I'd recommend doing.
