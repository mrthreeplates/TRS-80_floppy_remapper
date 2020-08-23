/**
  MEMORY Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    memory.c

  @Summary
    This is the generated driver implementation file for the MEMORY driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This file provides implementations of driver APIs for MEMORY.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.79.0
        Device            :  PIC18F26Q10
        Driver Version    :  4.20
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB             :  MPLAB X 5.30
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "memory.h"


/**
  Section: Flash Module APIs
*/

uint8_t FLASH_ReadByte(uint32_t flashAddr)
{
    //Set TBLPTR with the target byte address
    TBLPTRU = (uint8_t)((flashAddr & 0x00FF0000) >> 16);
    TBLPTRH = (uint8_t)((flashAddr & 0x0000FF00)>> 8);
    TBLPTRL = (uint8_t)(flashAddr & 0x000000FF);

    //Perform table read to move one byte from NVM to TABLAT
    asm("TBLRD");

    return (TABLAT);
}

uint16_t FLASH_ReadWord(uint32_t flashAddr)
{
    //Set TBLPTR with the target byte address
    NVMADRU = (uint8_t) ((flashAddr & 0x00FF0000) >> 16);
    NVMADRH = (uint8_t) ((flashAddr & 0x0000FF00) >> 8);
    NVMADRL = (uint8_t) (flashAddr & 0x000000FF);
    
    //NVMCON1.RD operations are not affected by NVMEN, ignore NVMEN
    NVMCON1bits.RD = 1;
    while (NVMCON1bits.RD);
    
    return ((((uint16_t)NVMDATH) << 8) | NVMDATL);
}

/**
 * @brief This routine reads one block from given address of Program Flash Memory
 *        into device Sector RAM
 * @return None
 * @param [in] Starting address of a Program Flash Memory block
 * @example This API is local to memory module and will be used by FLASH_WriteWord() API
 */
static void FLASH_ReadSector(uint32_t flashAddr)
{
    uint8_t GIEBitValue = INTCONbits.GIE;
        
    //Enable NVM access
    NVMCON0bits.NVMEN = 1;

    //Set NVMADR with the target word address
    NVMADRU = (uint8_t) ((flashAddr & 0x00FF0000) >> 16);
    NVMADRH = (uint8_t) ((flashAddr & 0x0000FF00) >> 8);
    NVMADRL = (uint8_t) (flashAddr & 0x000000FF);
    
    //Disable all interrupt
    INTCONbits.GIE = 0;

    //Perform the unlock sequence
    NVMCON2 = 0xBB;
    NVMCON2 = 0x44;

    //Start sector read and wait for the operation to complete
    NVMCON1bits.SECRD = 1;
    while (NVMCON1bits.SECRD);

    //Restore the interrupts
    INTCONbits.GIE = GIEBitValue;

    //Disable NVM access
    NVMCON0bits.NVMEN = 0;
}

/**
 * @brief This routine writes one block from Sector RAM to given address of Program Flash Memory
 * @return None
 * @param [in] Starting address of a Program Flash Memory block
 * @example This API is local to memory module and will be used by FLASH_WriteWord() API
 */
static void FLASH_WriteSector(uint32_t flashAddr)
{
    uint8_t GIEBitValue = INTCONbits.GIE;
    
    //Enable NVM access
    NVMCON0bits.NVMEN = 1;

    //Set NVMADR with the target word address
    NVMADRU = (uint8_t) ((flashAddr & 0x00FF0000) >> 16);
    NVMADRH = (uint8_t) ((flashAddr & 0x0000FF00) >> 8);
    NVMADRL = (uint8_t) (flashAddr & 0x000000FF);

    //Disable all interrupt
    INTCONbits.GIE = 0;

    //Perform the unlock sequence
    NVMCON2 = 0xDD;
    NVMCON2 = 0x22;

    //Start sector write and wait for the operation to complete
    NVMCON1bits.SECWR = 1;
    while (NVMCON1bits.SECWR);

    //Restore the interrupts
    INTCONbits.GIE = GIEBitValue;

    //Disable NVM access
    NVMCON0bits.NVMEN = 0;
}

uint8_t sectorRAM __at(0xD00);
void FLASH_WriteWord(uint32_t flashAddr, uint16_t word)
{
    uint16_t *secramWordPtr = (uint16_t*) & sectorRAM;
    uint32_t blockStartAddr = (uint32_t) (flashAddr & ((END_FLASH - 1) ^ ((ERASE_FLASH_BLOCKSIZE * 2) - 1)));
    uint8_t offset = (uint8_t) ((flashAddr & ((ERASE_FLASH_BLOCKSIZE * 2) - 1)) / 2);
        
    //Read existing block into Sector RAM
    FLASH_ReadSector(blockStartAddr);

    //Erase the given block
    FLASH_EraseBlock(blockStartAddr);

    //Modify Sector RAM for the given word to be written to Program Flash Memory
    secramWordPtr += offset;
    *secramWordPtr = word;

    //Write Sector RAM contents to given Program Flash Memory block
    FLASH_WriteSector(blockStartAddr);
}

int8_t FLASH_WriteBlock(uint32_t flashAddr, uint16_t *flashWrBufPtr)
{
    uint16_t *secramWordPtr = (uint16_t*) & sectorRAM;
    uint32_t blockStartAddr = (uint32_t) (flashAddr & ((END_FLASH - 1) ^ ((ERASE_FLASH_BLOCKSIZE * 2) - 1)));
    uint8_t i;

    //Block write must start at the beginning of a row
    if (flashAddr != blockStartAddr)
    {
        return -1;
    }

    //Copy application buffer contents to Buffer RAM
    for (i = 0; i < WRITE_FLASH_BLOCKSIZE; i++)
    {
        *secramWordPtr++ = flashWrBufPtr[i];
    }

    //Erase the given block
    FLASH_EraseBlock(flashAddr);

    //Write Sector RAM contents to given Program Flash Memory block
    FLASH_WriteSector(flashAddr);

    return 0;
}

void FLASH_EraseBlock(uint32_t flashAddr)
{
    uint8_t GIEBitValue = INTCONbits.GIE;
    
    NVMCON0bits.NVMEN = 1;    // Enable NVM access

    //Set NVMADR with the target word address
    NVMADRU = (uint8_t) ((flashAddr & 0x00FF0000) >> 16);
    NVMADRH = (uint8_t) ((flashAddr & 0x0000FF00) >> 8);
    NVMADRL = (uint8_t) (flashAddr & 0x000000FF);

    //Disable all interrupts
    INTCONbits.GIE = 0;

    //Perform the unlock sequence
    NVMCON2 = 0xCC;
    NVMCON2 = 0x33;

    //Start block erase and wait for the operation to complete
    NVMCON1bits.SECER = 1;
    while (NVMCON1bits.SECER);

    //Restore the interrupts
    INTCONbits.GIE = GIEBitValue;

    //Disable NVM access
    NVMCON0bits.NVMEN = 0;
}

/**
  Section: Data EEPROM Module APIs
*/
void DATAEE_WriteByte(uint16_t bAdd, uint8_t bData)
{
    uint8_t GIEBitValue = INTCONbits.GIE;
    
    //Set NVMADR with the target word address: 0x310000 - 0x3103FF
    NVMADRU = 0x31;
    NVMADRH = (uint8_t)((bAdd & 0xFF00) >> 8);
    NVMADRL = (uint8_t)(bAdd & 0x00FF);

    //Load NVMDATL with desired byte
    NVMDATL = (uint8_t)(bData & 0xFF);
    
    //Enable NVM access
    NVMCON0bits.NVMEN = 1;
    
    //Disable interrupts
    INTCONbits.GIE = 0;

    //Perform the unlock sequence
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;

    //Start DATAEE write and wait for the operation to complete
    NVMCON1bits.WR = 1;
    while (NVMCON1bits.WR);

    //Restore all the interrupts
    INTCONbits.GIE = GIEBitValue;

    //Disable NVM access
    NVMCON0bits.NVMEN = 0;
}

uint8_t DATAEE_ReadByte(uint16_t bAdd)
{
    //Set NVMADR with the target word address: 0x310000 - 0x3103FF
    NVMADRU = 0x31;
    NVMADRH = (uint8_t)((bAdd & 0xFF00) >> 8);
    NVMADRL = (uint8_t)(bAdd & 0x00FF);
    

    //Start DATAEE read
    NVMCON1bits.RD = 1;
    NOP();  // NOPs may be required for latency at high frequencies
    NOP();

    return (NVMDATL);
}

void MEMORY_ISR(void)
{
    /* TODO : Add interrupt handling code */
    PIR7bits.NVMIF = 0;
}
/**
 End of File
*/