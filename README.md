# TRS-80_floppy_remapper

![front of board](/img/front-v3.jpg)![back of board](/img/back-v3.jpg)

Sample build instructions with MPLAB X IDE

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

Note: The other files (Makefile and mcc_generated_files/*)
in this repo are provided as reference, and shouldn't be needed.

Programming instructions for PICKit 4

1. Under project properties, select PICKit 4
2. Select Options category: Power
3. Select "power target circuit from PICKit 4"
   Note: This is required as there is no external power supply for the remapper board.
4. Click Apply
5. Connect 6 pin header to remapper board, please be careful to orient
   connector to match pins!  MCLR has an arrow on it.
6. Click program.

