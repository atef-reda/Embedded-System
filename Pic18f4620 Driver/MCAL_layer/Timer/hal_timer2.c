/*
 * File:   hal_timer2.c
 * Author: redaa
 *
 * Created on November 7, 2023, 2:34 PM
 */

#include "hal_timer2.h"


static uint8 timer2_preload=ZERO_INIT;

#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
static inline void Timer2_Interrupt_Config(const timer2_t *_timer);
#endif
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
static interrupt_handler_fun TMR2_interrupt_handler = NULL;
#endif


Std_ReturnType Timer2_Init(const timer2_t *_timer){
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOK;
    } else {
        TIMER2_MODULE_DISABLE();
        TIMER2_PRESCALER_SELECT(_timer->timer2_prescaler_value);
        TIMER2_POSTSCALER_SELECT(_timer->timer2_postscaler_value);
        timer2_preload = _timer->timer2_preload_value;
        TMR2=_timer->timer2_preload_value;
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
        Timer2_Interrupt_Config(_timer);
#endif
        TIMER2_MODULE_ENABLE();
    }
    return ret;
}
Std_ReturnType Timer2_DeInit(const timer2_t *_timer){
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOK;
    } else {
        TIMER2_MODULE_DISABLE();
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
        TIMER2_interruptDisable();
#endif
    }
    return ret;
}

Std_ReturnType Timer2_Write_value(const timer2_t *_timer, uint8 _value) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOK;
    } else {
        TMR2=_value;
    }
    return ret;
}

Std_ReturnType Timer2_Read_value(const timer2_t *_timer, uint8 *_value) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOK;
    } else {
        *_value=TMR2;
    }
    return ret;
}

#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE

void TMR2_ISR(void) {
    TIMER2_interruptflag_clear();
    TMR2 = timer2_preload;
    if (TMR2_interrupt_handler) {
        TMR2_interrupt_handler();
    }
}
#endif

/*-----------------  HELPER FUNCTIONS  -----------------*/
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE

static inline void Timer2_Interrupt_Config(const timer2_t *_timer) {
    TIMER2_interruptEnable();
    TIMER2_interruptflag_clear();
    TMR2_interrupt_handler = _timer->TMR2_Iterrupt_Handler;
#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
    INTERRUPT_priorityLevelsEnable();
    if (Interrupt_high_priority == _timer->priority) {
        INTERRUPT_GlobalInterruptHighEnable();
        TIMER2_highpriorityset();
    } else if (interrupt_low_priority == _timer->priority) {
        INTERRUPT_GlobalInterruptlowEnable();
        TIMER2_lowpriorityset();
    } else {
        /*nothing*/
    }
#else 
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif
}
#endif

