/*
 * File:   hal_timer3.c
 * Author: redaa
 *
 * Created on November 7, 2023, 2:34 PM
 */


#include "hal_timer3.h"


static timer3_preload;
static inline void Timer3_Mode_Select(const timer3_t *_timer);

#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
static inline void Timer3_Interrupt_Config(const timer3_t *_timer);
static interrupt_handler_fun TMR3_interrupt_handler = NULL;
#endif


Std_ReturnType Timer3_Init(const timer3_t *_timer)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOK;
    } else {
        TIMER3_MODULE_DISABLE();
        TIMER3_PRESACLER_SELECT(_timer->timer3_prescaler_value);
        Timer3_Mode_Select(_timer);
        TIMER3_RW_8_BIT_REGISTER_ENABLE_();
        timer3_preload=_timer->timer3_preload_value;
        Timer3_Write_value(_timer,_timer->timer3_preload_value);
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
        Timer3_Interrupt_Config(_timer);
#endif
        TIMER3_MODULE_ENABLE();
    }
    return ret;
}

Std_ReturnType Timer3_DeInit(const timer3_t *_timer)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOK;
    } else {
        TIMER3_MODULE_DISABLE();
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
        TIMER3_interruptDisable();
#endif
    }
    return ret;
}
Std_ReturnType Timer3_Write_value(const timer3_t *_timer,uint16 _value)
{
     Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOK;
    } else {
        TMR3H=((uint8)(_value>>8));
        TMR3L=((uint8)_value);
    }
    return ret;
}
Std_ReturnType Timer3_Read_value(const timer3_t *_timer,uint16 *_value)
{
    Std_ReturnType ret = E_OK;
    uint8 l_tmr3l=ZERO_INIT,l_tmr3h=ZERO_INIT;
    if (NULL == _timer) {
        ret = E_NOK;
    } else {
        l_tmr3l=TMR3L;
        l_tmr3h=TMR3H;
        *_value=(uint16)((l_tmr3h<<8)+l_tmr3l);
    }
    return ret;
}

#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE

void TMR3_ISR(void) {
    TIMER3_interruptflag_clear();
    TMR3H = ((uint8) (timer3_preload >> 8));
    TMR3L = ((uint8) timer3_preload);
    if (TMR3_interrupt_handler) {
        TMR3_interrupt_handler();
    }
}
#endif

/*-----------------------------helper functions---------------------------*/

static inline void Timer3_Mode_Select(const timer3_t *_timer) {
    if (TIMER3_TIMER_MODE_ENABLE_CFG == _timer->timer3_source_mode) {
        TIMER3_TIMER_MODE_ENABLE();
    } else if (TIMER3_COUNTER_MODE_ENABLE_CFG == _timer->timer3_source_mode) {
        TIMER3_COUNTER_MODE_ENABLE();
        if (TIMER3_ASYNC_COUNTER_MODE_ENABLE_CFG == _timer->timer3_counter_mode) {
            TIMER3_ASYNC_COUNTER_MODE_ENABLE();
        } else if (TIMER3_SYNC_COUNTER_MODE_ENABLE_CFG == _timer->timer3_counter_mode) {
            TIMER3_SYNC_COUNTER_MODE_ENABLE1 ();
        } else {
            /*Nothing*/
        }
    } else {
        /*Nothing*/
    }
}

#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE

static inline void Timer3_Interrupt_Config(const timer3_t *_timer) {
    TIMER3_interruptEnable();
    TIMER3_interruptflag_clear();
    TMR3_interrupt_handler = _timer->TMR3_Iterrupt_Handler;
#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
    INTERRUPT_priorityLevelsEnable();
    if (Interrupt_high_priority == _timer->priority) {
        INTERRUPT_GlobalInterruptHighEnable();
        TIMER3_highpriorityset();
    } else if (interrupt_low_priority == _timer->priority) {
        INTERRUPT_GlobalInterruptlowEnable();
        TIMER3_lowpriorityset();
    } else {
        /*nothing*/
    }
#else 
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif
}
#endif

