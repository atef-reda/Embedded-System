/* 
 * File:   hal_timer3.h
 * Author: redaa
 *
 * Created on November 7, 2023, 2:33 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/*section: includes */
#include <xc.h>
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "../interrupt/mcal_external_interrupt.h"
/*section : macro declarations */

#define TIMER3_COUNTER_MODE_ENABLE_CFG          1
#define TIMER3_TIMER_MODE_ENABLE_CFG            0

#define TIMER3_ASYNC_COUNTER_MODE_ENABLE_CFG    1  
#define TIMER3_SYNC_COUNTER_MODE_ENABLE_CFG     0  

#define TIMER1_OSC_ENABLE_CFG                   1
#define TIMER1_OSC_DISABLE_CFG                  0

#define TIMER3_PRESCALER_VALUE_DIV_1            0
#define TIMER3_PRESCALER_VALUE_DIV_2            1
#define TIMER3_PRESCALER_VALUE_DIV_4            2
#define TIMER3_PRESCALER_VALUE_DIV_8            3

#define TIMER3_RW_8_BIT_REGISTER_ENABLE_CFG     0
#define TIMER3_RW_16_BIT_REGISTER_ENABLE_CFG    1
/*section: macro functions declarations */
#define TIMER3_MODULE_ENABLE()                   (T3CONbits.TMR3ON=1)
#define TIMER3_MODULE_DISABLE()                  (T3CONbits.TMR3ON=0)

#define TIMER3_TIMER_MODE_ENABLE()               (T3CONbits.TMR3CS=0)
#define TIMER3_COUNTER_MODE_ENABLE()             (T3CONbits.TMR3CS=1)

#define TIMER3_ASYNC_COUNTER_MODE_ENABLE()       (T3CONbits.T3SYNC=1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE1()       (T3CONbits.T3SYNC=0)

/*--------    as in timer1 ------*/
#define TIMER3_OSC_HW_ENABLE()                   (T1CONbits.T1OSCEN=1)
#define TIMER3_OSC_HW_DISABLE()                  (T1CONbits.T1OSCEN=0)

#define TIMER3_PRESACLER_SELECT(_PRESCALER_)     (T3CONbits.T3CKPS=_PRESCALER_)

#define TIMER3_RW_8_BIT_REGISTER_ENABLE_()       (T3CONbits.RD16=0)
#define TIMER3_RW_16_BIT_REGISTER_ENABLE_()      (T3CONbits.RD16=1)
/*section: data types declarations*/
typedef struct {
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
    void (* TMR3_Iterrupt_Handler)(void);
#if INTERRUPT_Priority_Levels_Enable==INTERRUPT_feature_ENABLE
    interrupt_priority_cfg priority;
#endif
#endif
    uint16 timer3_preload_value;
    uint8 timer3_prescaler_value : 2;
    uint8 timer3_source_mode : 1;
    uint8 timer3_regisetr_wr_mode : 1;
    uint8 timer3_counter_mode : 1;
    uint8 timer3_resarvied_value : 3;
} timer3_t;
/*section: function declarations*/
Std_ReturnType Timer3_Init(const timer3_t *_timer);
Std_ReturnType Timer3_DeInit(const timer3_t *_timer);
Std_ReturnType Timer3_Write_value(const timer3_t *_timer,uint16 _value);
Std_ReturnType Timer3_Read_value(const timer3_t *_timer,uint16 *_value);



#endif	/* HAL_TIMER3_H */

