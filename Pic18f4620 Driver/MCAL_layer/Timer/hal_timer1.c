/*
 * File:   hal_timer1.c
 * Author: redaa
 *
 * Created on November 4, 2023, 4:38 PM
 */

#include "hal_timer1.h"

static timer1_preload=ZERO_INIT;
static inline void Timer1_Mode_Select(const timer1_t *_timer);

#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
static inline void Timer1_Interrupt_Config(const timer1_t *_timer);
#endif
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
static interrupt_handler_fun TMR1_interrupt_handler = NULL;
#endif


Std_ReturnType Timer1_Init(const timer1_t *_timer){
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOK;
    } else {
        TIMER1_MODULE_DISABLE();
        TIMER1_PRESACLER_SELECT(_timer->timer1_prescaler_value);
        Timer1_Mode_Select(_timer);
        TIMER1_RW_8_BIT_REGISTER_ENABLE_();
        timer1_preload=_timer->timer1_preload_value;
        Timer1_Write_value(_timer,_timer->timer1_preload_value);
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
        Timer1_Interrupt_Config(_timer);
#endif
        TIMER1_MODULE_ENABLE();
    }
    return ret;
}
Std_ReturnType Timer1_DeInit(const timer1_t *_timer) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOK;
    } else {
        TIMER1_MODULE_DISABLE();
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
        TIMER1_interruptDisable();
#endif
    }
    return ret;
}


Std_ReturnType Timer1_Write_value(const timer1_t *_timer,uint16 _value){
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOK;
    } else {
        TMR1H=((uint8)(_value>>8));
        TMR1L=((uint8)_value);
    }
    return ret;
}


Std_ReturnType Timer1_Read_value(const timer1_t *_timer, uint16 *_value) {
    Std_ReturnType ret = E_OK;
    uint8 l_tmr1l=ZERO_INIT,l_tmr1h=ZERO_INIT;
    if (NULL == _timer) {
        ret = E_NOK;
    } else {
        l_tmr1l=TMR1L;
        l_tmr1h=TMR1H;
        *_value=(uint16)((l_tmr1h<<8)+l_tmr1l);
    }
    return ret;
}



#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE

void TMR1_ISR(void) {
    TIMER1_interruptflag_clear();
    TMR1H = ((uint8) (timer1_preload >> 8));
    TMR1L = ((uint8) timer1_preload);
    if (TMR1_interrupt_handler) {
        TMR1_interrupt_handler();
    }
}
#endif

/*-----------------------------helper functions---------------------------*/

static inline void Timer1_Mode_Select(const timer1_t *_timer) {
    if (TIMER1_TIMER_MODE_ENABLE_CFG == _timer->timer1_source_mode) {
        TIMER1_TIMER_MODE_ENABLE();
    } else if (TIMER1_COUNTER_MODE_ENABLE_CFG == _timer->timer1_source_mode) {
        TIMER1_COUNTER_MODE_ENABLE();
        if (TIMER1_ASYNC_COUNTER_MODE_ENABLE_CFG == _timer->timer1_counter_mode) {
            TIMER1_ASYNC_COUNTER_MODE_ENABLE();
        } else if (TIMER1_SYNC_COUNTER_MODE_ENABLE_CFG == _timer->timer1_counter_mode) {
            TIMER1_SYNC_COUNTER_MODE_ENABLE1 ();
        } else {
            /*Nothing*/
        }
    } else {
        /*Nothing*/
    }
}

#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE

static inline void Timer1_Interrupt_Config(const timer1_t *_timer) {
    TIMER1_interruptEnable();
    TIMER1_interruptflag_clear();
    TMR1_interrupt_handler = _timer->TMR1_Iterrupt_Handler;
#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
    INTERRUPT_priorityLevelsEnable();
    if (Interrupt_high_priority == _timer->priority) {
        INTERRUPT_GlobalInterruptHighEnable();
        TIMER1_highpriorityset();
    } else if (interrupt_low_priority == _timer->priority) {
        INTERRUPT_GlobalInterruptlowEnable();
        TIMER1_lowpriorityset();
    } else {
        /*nothing*/
    }
#else 
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif
}
#endif

