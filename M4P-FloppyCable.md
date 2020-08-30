# TRS-80_floppy_remapper

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

