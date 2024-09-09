/* 
 * File:   hal_timer2.h
 * Author: redaa
 *
 * Created on November 7, 2023, 2:33 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/*section: includes */
#include <xc.h>
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "../interrupt/mcal_external_interrupt.h"
/*section : macro declarations */
/*------------ timer2 pre_scaler -------------*/
#define TIMER2_PRESCALER_VALUE_DIV_1            0
#define TIMER2_PRESCALER_VALUE_DIV_4            1
#define TIMER2_PRESCALER_VALUE_DIV_16           2

/*------------ timer2 post_scaler -------------*/
#define TIMER2_POSTSCALER_VALUE_DIV_1             0
#define TIMER2_POSTSCALER_VALUE_DIV_2             1
#define TIMER2_POSTSCALER_VALUE_DIV_3             2
#define TIMER2_POSTSCALER_VALUE_DIV_4             3
#define TIMER2_POSTSCALER_VALUE_DIV_5             4
#define TIMER2_POSTSCALER_VALUE_DIV_6             5
#define TIMER2_POSTSCALER_VALUE_DIV_7             6
#define TIMER2_POSTSCALER_VALUE_DIV_8             7
#define TIMER2_POSTSCALER_VALUE_DIV_9             8
#define TIMER2_POSTSCALER_VALUE_DIV_10            9
#define TIMER2_POSTSCALER_VALUE_DIV_11            10
#define TIMER2_POSTSCALER_VALUE_DIV_12            11
#define TIMER2_POSTSCALER_VALUE_DIV_13            12
#define TIMER2_POSTSCALER_VALUE_DIV_14            13
#define TIMER2_POSTSCALER_VALUE_DIV_15            14
#define TIMER2_POSTSCALER_VALUE_DIV_16            15
/*section: macro functions declarations */
#define TIMER2_MODULE_ENABLE()                   (T2CONbits.TMR2ON=1)
#define TIMER2_MODULE_DISABLE()                  (T2CONbits.TMR2ON=0)


#define TIMER2_PRESCALER_SELECT(_PRESCALER_)                 (T2CONbits.T2CKPS=_PRESCALER_)
#define TIMER2_POSTSCALER_SELECT(_POSTSCALER_)               (T2CONbits.TOUTPS=_POSTSCALER_)

/*section: data types declarations*/
typedef struct {
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
    void (* TMR2_Iterrupt_Handler)(void);
#if INTERRUPT_Priority_Levels_Enable==INTERRUPT_feature_ENABLE
    interrupt_priority_cfg priority;
#endif
#endif
    uint8 timer2_preload_value;
    uint8 timer2_prescaler_value : 2;
    uint8 timer2_postscaler_value : 4;
    uint8 timer2_resarvied_value : 2;
} timer2_t;
/*section: function declarations*/
Std_ReturnType Timer2_Init(const timer2_t *_timer);
Std_ReturnType Timer2_DeInit(const timer2_t *_timer);
Std_ReturnType Timer2_Write_value(const timer2_t *_timer,uint8 _value);
Std_ReturnType Timer2_Read_value(const timer2_t *_timer,uint8 *_value);


#endif	/* HAL_TIMER2_H */

