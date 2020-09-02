# TRS-80_floppy_remapper

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
motherboard modification is required.  The third pin on the
output signal header provides the extra signal needed for these computers
(see the installation instructions for more info).
