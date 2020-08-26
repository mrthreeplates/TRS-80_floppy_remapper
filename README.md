# TRS-80_floppy_remapper

![front of board](/images/front-v3.jpg)![back of board](/images/back-v3.jpg)

Information about the project:

http://www.vcfed.org/forum/showthread.php?75460-My-floppy-remapper-project-version-2

[design files](/design): (schematic and pin map).

[PCB files](/design/pcb_info): (gerbers, bill of materials, centroid)

[Programming files](/program) (MPLAB project source code and compiled HEX file)

Build instruction with MPLAB X IDE

1. Create a new project based on a PIC18F26Q10
2. Under your projects tab, "Important Files", right click to "Add item to important Files"
   Select "MyConfig.mc3" from this repo and add it.
   
   Ref: https://microchipdeveloper.com/mcc:mcc-config, scroll down
   to "Adding an Existing Configuration File to a Project".
   
3. Open MCC
4. Click "Generate".  You should now have a list of "mcc_generated" files now, including
   a default"main.c".
5. Overwrite "main.c" with the one from this repo
6. Build the project, it should compile w/o errors.

Alternatively, you can import the prebuilt hex file into a new project.

1. Select "File" -> "Import" -> "Hex" and select the hex file from this repo.
2. Finish creating a new project based on a PIC18F26Q10

Programming instructions for PICKit 4

1. Under project properties, select PICKit 4
2. Select Options category: Power
3. Select "power target circuit from PICKit 4"
   Note: This is required as there is no external power supply for the remapper board.
4. Click Apply
5. Connect the 6 pin programming header to the remapper board, please be careful to orient
   programming header to match the board pins!  Look for the MCLR pin with an arrow on it.
6. Click program.

After programming (unless the PIC18 is held in reset) it will boot and run a
one-time-only series of self tests.  This is mostly to test the software and
also verifies the PIC is working correctly.

The LEDs will flash through a set of patterns which will take about 15 seconds.

At the end, all of the LEDs should remain lit, with the enable LED flashing slowly.
This indicates the tests passed and allows you to verify all the LEDs are working.

The next time the PIC boots, it will assume it has been installed into a TRS-80 and
will start working normally.  If you boot the PIC without having it installed, the
board may behave unpredictably due to floating inputs (although there is no harm).

At the end of the tests, if an error is found, all of the LEDs will flash in an
alternating pattern.  This means there is either a bug in the code or a problem with
the board.  Either way, this needs to be fixed. If you try to install the board
into a computer, it will refuse to work (as the error status is saved into EEPROM).
In order to re-run the tests, you must re-program the PIC.

Ordering boards from PCBway:

https://www.pcbway.com/project/shareproject/Tandy_Radio_Shack_TRS_80_Floppy_Disk_Remapper.html
