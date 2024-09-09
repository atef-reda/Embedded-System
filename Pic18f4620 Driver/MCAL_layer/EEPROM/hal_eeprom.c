/*
 * File:   hal_eeprom.c
 * Author: redaa
 *
 * Created on September 26, 2023, 3:01 PM
 */


#include "hal_eeprom.h"


/**
 * 
 * @param bAdd
 * @param bData
 * @return 
 */
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData) {
    Std_ReturnType ret = E_OK;
    /*Read the interrupt status "Enabled or Disabled" */
    uint8 Global_Interrupt_Status= GLOBAL_INTERRUPT_STATUS();
    /*Update The Address Register*/
    EEADRH=EEADRHIGST(bAdd);
    EEADR =EEADRLIST(bAdd);
    /*Update The Register Data*/
    EEDATA=bData;
    /*Select The Access Data EEPROM Memory*/
    EECON1bits.EEPGD=ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS=ACCESS_EEPROM_FLASH_MEMORY;
    /*Allow Write Cycle TO Flash/EEPROM*/
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
    /*Disable All Interrupts "Global Interrupts"*/
    INTERRUPT_GlobalInterruptDisable();
    /*Write The Required Sequence*/
    EECON2 = WRITE_0X55;
    EECON2 = WRITE_0XAA;
    /*Initiates a Data EEPROM Erase/Write Cycle*/
    EECON1bits.WR=INITIATE_DATA_EEPROM_WRITE;
    /*Wait For Write To Be Complete*/
    while(EECON1bits.WR)
    {
        
    }
    /*Inhabits Write Cycle TO Flash/EEPROM*/
    EECON1bits.WREN=INHIPTS_WRITE_CYCLES_FLASH_EEPROM;
    /*Restore the interrupt status "Enabled or Disabled" */
    INTCONbits.GIE=Global_Interrupt_Status;
    return ret;
}

/**
 * 
 * @param bAdd
 * @param bData
 * @return 
 */

Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData) {
    Std_ReturnType ret = E_OK;
    if (NULL == bData) {
        ret = E_NOK;
    } else {
        /*Update The Address Register*/
        EEADRH = EEADRHIGST(bAdd);
        EEADR = EEADRLIST(bAdd);
        /*Select Access Data EEPROM Memory*/
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS = ACCESS_EEPROM_FLASH_MEMORY;
        /*Initiates a Data EEPROM Read Cycle*/
        EECON1bits.RD = INITIATE_DATA_EEPROM_Read;
        /*Delay Two Cycle*/
        NOP();
        NOP();
        /*Return Data*/
        *bData = EEDATA;
    }
    return ret;
}