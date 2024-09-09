/* 
 * File:   hal_timer1.h
 * Author: redaa
 *
 * Created on November 4, 2023, 4:37 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/*section: includes */
#include <xc.h>
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "../interrupt/mcal_external_interrupt.h"
/*section : macro declarations */

#define TIMER1_COUNTER_MODE_ENABLE_CFG          1
#define TIMER1_TIMER_MODE_ENABLE_CFG            0

#define TIMER1_ASYNC_COUNTER_MODE_ENABLE_CFG    1  
#define TIMER1_SYNC_COUNTER_MODE_ENABLE_CFG     0  

#define TIMER1_OSC_ENABLE_CFG                   1
#define TIMER1_OSC_DISABLE_CFG                  0

#define TIMER1_PRESCALER_VALUE_DIV_1            0
#define TIMER1_PRESCALER_VALUE_DIV_2            1
#define TIMER1_PRESCALER_VALUE_DIV_4            2
#define TIMER1_PRESCALER_VALUE_DIV_8            3

#define TIMER1_RW_16_BIT_REGISTER_ENABLE_CFG    1
#define TIMER1_RW_8_BIT_REGISTER_ENABLE_CFG     0

/*section: macro functions declarations */
#define TIMER1_MODULE_ENABLE()                   (T1CONbits.TMR1ON=1)
#define TIMER1_MODULE_DISABLE()                  (T1CONbits.TMR1ON=0)

#define TIMER1_TIMER_MODE_ENABLE()               (T1CONbits.TMR1CS=0)
#define TIMER1_COUNTER_MODE_ENABLE()             (T1CONbits.TMR1CS=1)

#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()       (T1CONbits.T1SYNC=1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE1()       (T1CONbits.T1SYNC=0)

#define TIMER1_OSC_HW_ENABLE()                   (T1CONbits.T1OSCEN=1)
#define TIMER1_OSC_HW_DISABLE()                  (T1CONbits.T1OSCEN=0)

#define TIMER1_PRESACLER_SELECT(_PRESCALER_)     (T1CONbits.T1CKPS=_PRESCALER_)

#define TIMER1_SYS_CLK_STATUS()                  (T1CONbits.T1RUN)

#define TIMER1_RW_16_BIT_REGISTER_ENABLE_()      (T1CONbits.RD16=1)
#define TIMER1_RW_8_BIT_REGISTER_ENABLE_()       (T1CONbits.RD16=0)

/*section: data types declarations*/
typedef struct {
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
    void (* TMR1_Iterrupt_Handler)(void);
#if INTERRUPT_Priority_Levels_Enable==INTERRUPT_feature_ENABLE
    interrupt_priority_cfg priority;
#endif
#endif
    uint16 timer1_preload_value;
    uint8 timer1_prescaler_value : 2;
    uint8 timer1_source_mode : 1;
    uint8 timer1_regisetr_wr_mode : 1;
    uint8 timer1_osc_cfg : 1;
    uint8 timer1_counter_mode : 1;
    uint8 timer1_resarvied_value : 2;
} timer1_t;
/*section: function declarations*/
Std_ReturnType Timer1_Init(const timer1_t *_timer);
Std_ReturnType Timer1_DeInit(const timer1_t *_timer);
Std_ReturnType Timer1_Write_value(const timer1_t *_timer,uint16 _value);
Std_ReturnType Timer1_Read_value(const timer1_t *_timer,uint16 *_value);

#endif	/* HAL_TIMER1_H */

