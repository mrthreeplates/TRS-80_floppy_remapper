# TRS-80_floppy_remapper

## Enabling limited Motor Control (optional)

Notes:
1. This is a new feature in V4.
1. I've repurposed two of the microcontroller's output to control floppy drive motor on signals.
1. While there are 4 possible floppy drives, I think controlling the two internal floppy drives is likely all that people will need (I hope...).
1. Despite the silkscreen inticating that you can control drives 0 and 1, I've actually made this selectable (unfortunately, only by changing the firmware).
1. Floppy MotorOn signals are inverted and sometimes require pullups (also called termination resistors).
1. See the code in main.c for different options for switching between controlling drives 0,1; drives 2,3; or internal/external drive pairs.  You can also change if the outputs are open drain (requiring a pullup), or inverted.  There are many different options, so feel free to tinker if this doesn't work for you.

Default behavior:
1. The currently checked-in code (which I hope is the most useful), assumes you want to only control "drive pairs".
1. The left pin on the MotorOn jumper (marked drive 0) actually controls the internal drives (e.g. 0 and 1).
1. The right pin (marked drive 1) actually controls the external drives (e.g. 2 and 3).
1. As the external drives are probably going to be virtual anyway, this pin probably doesn't need to be hooked up.  So, I'll skip instructions for it.
1. This leaves only the drive 0 pin.  This is intented to be connected directly to the floppy cable.  FYI: this means the MotorOn signal will be inverted.  As the internal drives typically don't have pull-ups, it will also be configured as a normal TTL output (v.s. open drain).

## General instructions

Assuming you only want to control the internal drive motors (as a pair), installation is straightforward.

All you need to do is isolate pin 16 (~MotorOn) from the floppy ribbon cable and wire it to the "drive 0" pin.  That's it!

## Model 4P gate-array install

If you have created a 4P cable following my instructions, you just need to isolate an additional wire.  Separate out pin 16 after the drive 0 and 1 connectors.  Solder a wire to it with a dupont connector on the other end.  I used a green wire below:

![M4P cable mod](/images/m4pga-motoron1.jpg)

And connect the wire to the "drive 0" pin, as done here:

![M4P install](/images/m4pga-motoron2.jpg)

## Model 4 gate-array install

As above, separate out pin 16. In this case, I used a blue wire:

![M4P cable mod](/images/m4ga-motoron1.jpg)

All tucked in:

![M4P install](/images/m4ga-motoron2.jpg)

## Using your computer with the new MotorOn control

1. Your computer should function as it did before this change, except that the internal drive motors will now only turn on when they are accessed (v.s. turning on whenever *any* drive is accessed).
1. The new MotorOn signals' timeout behavior should be unchanged (i.e. after about 2 seconds of drive inactivity all MotorOn signals will turn off).
1. You can verify this behavior using "OUT 244, x" (where x is 1, 2, 4, 8) to simulate drive activity (or drive to drive copies).
1. At a very low level, the new MotorOn signal will lag slightly (e.g. about 1us) the drive select line.  This is due to the speed of the microcontroller.  I don't think (hope) this small delay will cause any problems.
