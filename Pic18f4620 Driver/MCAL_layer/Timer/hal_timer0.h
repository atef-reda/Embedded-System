/* 
 * File:   hal_timer0.h
 * Author: redaa
 *
 * Created on October 29, 2023, 4:19 PM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H
/*section: includes */
#include <xc.h>
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "../interrupt/mcal_external_interrupt.h"
/*section : macro declarations */
#define TIMER0_PRESCALER_ENABLE_CFG        1
#define TIMER0_PRESCALER_DISABLE_CFG       0

#define TIMER0_COUNTER_RASING_EDGE_CFG     1
#define TIMER0_COUNTER_FALLING_EDGE_CFG    0

#define TIMER0_TIMER_MODE_ENABLE_CFG       1
#define TIMER0_COUNTER_MODE_ENABLE_CFG     0

#define TIMER0_REGISTER_8_BIT_ENABLE_CFG   1
#define TIMER0_REGISTER_16_BIT_ENABLE_CFG  0
/*section: macro functions declarations */
#define TIMER0_PRESCALER_ENABLE()                (T0CONbits.PSA=0)
#define TIMER0_PRESCALER_DISABLE()               (T0CONbits.PSA=1)

#define TIMER0_COUNTER_RASING_EDGE_ENABLE()      (T0CONbits.T0SE=0)
#define TIMER0_COUNTER_FALLING_EDGE_ENABLE()     (T0CONbits.T0SE=1)

#define TIMER0_TIMER_MODE_ENABLE()               (T0CONbits.T0CS=0)
#define TIMER0_COUNTER_MODE_ENABLE()             (T0CONbits.T0CS=1)

#define TIMER0_REGISTER_8_BIT_ENABLE()           (T0CONbits.T08BIT=1)
#define TIMER0_REGISTER_16_BIT_ENABLE()          (T0CONbits.T08BIT=0)

#define TIMER0_MODULE_ENABLE()                   (T0CONbits.TMR0ON=1)
#define TIMER0_MODULE_DISABLE()                  (T0CONbits.TMR0ON=0)

/*section: data types declarations*/
typedef enum {
    TIMER0_PRESCALER_DIV_BY_2,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256,
} timer0_prescaler_select_t;

typedef struct {
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
    void (* ADC_Iterrupt_Handler)(void);
#if INTERRUPT_Priority_Levels_Enable==INTERRUPT_feature_ENABLE
    interrupt_priority_cfg priority ;
#endif
#endif

    timer0_prescaler_select_t timer0_prescaler_value;
    uint16 timer0_preload_value;
    uint8 timer0_prescaler_enable : 1;
    uint8 timer0_counter_edge : 1;
    uint8 timer0_source_mode : 1;
    uint8 timer0_register_size : 1;
    uint8 timer0_resarvied_value : 4;
} timer0_t;
/*section: function declarations*/
Std_ReturnType Timer0_Init(const timer0_t *_timer);
Std_ReturnType Timer0_DeInit(const timer0_t *_timer);
Std_ReturnType Timer0_Write_value(const timer0_t *_timer,uint16 _value);
Std_ReturnType Timer0_Read_value(const timer0_t *_timer,uint16 *_value);
#endif	/* HAL_TIMER0_H */

