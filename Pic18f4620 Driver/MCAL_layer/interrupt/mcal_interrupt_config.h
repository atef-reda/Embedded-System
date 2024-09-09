/* 
 * File:   mcal_interrupt_config.h
 * Author: Home?
 *
 * Created on September 7, 2023, 11:48 AM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H
/*..............includes.............*/
#include "xc.h"
#include "../mcal_std_types.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
/*...............macro declarations........*/
#define INTERRUPT_ENABLE  1
#define INTERRUPT_DISABLE 0
#define INTERRUPT_OCCUR   1
#define INTERRUPT_DISOCCUR 0  
#define INTERRUPT_PRIORITY_ENABLE  1
#define INTERRUPT_PRIORITY_DISABlE 0
/*...............macro function declarations......*/
#if INTERRUPT_Priority_Levels_Enable ==INTERRUPT_feature_ENABLE 
/*this macro will enable priority levels on interrupt*/
#define INTERRUPT_priorityLevelsEnable()      (RCONbits.IPEN =1)
/*this macro will disable priority levels on interrupt*/
#define INTERRUPT_priorityLevelsDisable()       (RCONbits.IPEN=0)

/*this macro will enable high priority global interrupts*/
#define INTERRUPT_GlobalInterruptHighEnable()  (INTCONbits.GIEH=1)
/*this macro will disable high priority global interrupts*/
#define INTERRUPT_GlobalInterruptHighDisable()  (INTCONbits.GIEH=0)

/*this macro will enable low priority global interrupts*/
#define INTERRUPT_GlobalInterruptlowEnable()  (INTCONbits.GIEL=1)
/*this macro will disable low priority global interrupts*/
#define INTERRUPT_GlobalInterruptlowDisable()  (INTCONbits.GIEL=0)
#endif 
/*this macro will enable  global interrupts*/
#define INTERRUPT_GlobalInterruptEnable()  (INTCONbits.GIE=1)
/*this macro will disable  global interrupts*/
#define INTERRUPT_GlobalInterruptDisable()  (INTCONbits.GIE=0)
/*This macro will enable peripheral interrupts*/
#define INTERRUPT_PeripheralInterruptEnable()   (INTCONbits.PEIE=1)
/*This macro will enable peripheral interrupts*/
#define INTERRUPT_PeripheralInterruptDisable()   (INTCONbits.PEIE=0)
 

/*...............data type declarations......*/
typedef void (*interrupt_handler_fun)(void);
typedef enum {
    interrupt_low_priority = 0,
    Interrupt_high_priority
} interrupt_priority_cfg;
/*................software interfaces declarations........*/


#endif	/* MCAL_INTERRUPT_CONFIG_H */

