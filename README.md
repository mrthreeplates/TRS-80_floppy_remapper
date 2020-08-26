# TRS-80_floppy_remapper

Information about the project:

http://www.vcfed.org/forum/showthread.php?75460-My-floppy-remapper-project-version-2

![front of board](/images/front-v3.jpg)![back of board](/images/back-v3.jpg)

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

1. Select "File" -> "Import" -> Hex and select the hex file from this repo.
2. Finish creating a new project based on a PIC18F26Q10

Programming instructions for PICKit 4

1. Under project properties, select PICKit 4
2. Select Options category: Power
3. Select "power target circuit from PICKit 4"
   Note: This is required as there is no external power supply for the remapper board.
4. Click Apply
5. Connect 6 pin header to remapper board, please be careful to orient
   connector to match pins!  MCLR has an arrow on it.
6. Click program.

Ordering from PCBway:

https://www.pcbway.com/project/shareproject/Tandy_Radio_Shack_TRS_80_Floppy_Disk_Remapper.html

