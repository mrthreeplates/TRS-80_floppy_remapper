# TRS-80_floppy_remapper

## V3 Design and PCB files (how to make boards)

* [Design files](/design): (schematic and pin map)
* Datasheets: [PIC18F26Q10](http://ww1.microchip.com/downloads/en/DeviceDoc/PIC18F26-45-46Q10-Data-Sheet-40001996D.pdf), [74LS174](https://www.ti.com/lit/ds/symlink/sn74ls174.pdf)
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

