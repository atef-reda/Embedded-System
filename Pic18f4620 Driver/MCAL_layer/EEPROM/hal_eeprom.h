/* 
 * File:   hal_eeprom.h
 * Author: redaa
 *
 * Created on September 26, 2023, 3:00 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/*section: includes */
#include "xc.h"
#include "../mcal_std_types.h"
#include "../interrupt/mcal_external_interrupt.h"
#include "../GPIO/hal_gpio.h"
/*section : macro declarations */

 /*Flash Program Or EEPROM Select*/
#define ACCESS_FLASH_PROGRAM_MEMORY         1
#define ACCESS_EEPROM_PROGRAM_MEMORY        0
 /*Flash Program /EEPROM or Configuration Select*/
#define ACCESS_CONFIG_REGISTER              1
#define ACCESS_EEPROM_FLASH_MEMORY          0
 /*Flash Program / Data EEPROM Enable */
#define ALLOW_WRITE_CYCLES_FLASH_EEPROM     1
#define INHIPTS_WRITE_CYCLES_FLASH_EEPROM   0
 /*Write Control*/
#define INITIATE_DATA_EEPROM_WRITE          1
#define DATA_EEPROM_WRITE_COMPLETED         0
 /*Read Control*/
#define INITIATE_DATA_EEPROM_Read           1
#define DATA_EEPROM_Read_COMPLETED          0
 /*Write The Required Sequence*/
#define WRITE_0X55                          0X55
#define WRITE_0XAA                          0XAA


/*section: macro functions declarations */
#define GLOBAL_INTERRUPT_STATUS()   INTCONbits.GIE
#define EEADRHIGST(bAdd)                (uint8)((bAdd>>8)&(0x03))
#define EEADRLIST(bAdd)                 (uint8)(bAdd&0xFF)
/*section: data types declarations*/
/*section: function declarations*/
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd,uint8 bData);
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd,uint8 *bData);


#endif	/* HAL_EEPROM_H */

