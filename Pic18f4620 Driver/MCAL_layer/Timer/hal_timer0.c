/*
 * File:   hal_timer0.c
 * Author: redaa
 *
 * Created on October 29, 2023, 4:19 PM
 */


#include "hal_timer0.h"
static timer0_preload=ZERO_INIT;
static inline void Timer0_Prescaler_Config(const timer0_t *_timer);
static inline void Timer0_Mode_Select(const timer0_t *_timer);
static inline void Timer0_Register_Size_Config(const timer0_t *_timer);

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
static inline void Timer0_Interrupt_Config(const timer0_t *_timer);
#endif

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
static interrupt_handler_fun TMR0_interrupt_handler = NULL;
#endif

/**
 * 
 * @param _timer
 * @return 
 */
Std_ReturnType Timer0_Init(const timer0_t *_timer) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOK;
    } else {
        TIMER0_MODULE_DISABLE();
        Timer0_Prescaler_Config(_timer);
        Timer0_Mode_Select(_timer);
        Timer0_Register_Size_Config(_timer);
        timer0_preload=_timer->timer0_preload_value;
        Timer0_Write_value(_timer,_timer->timer0_preload_value);
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
        Timer0_Interrupt_Config(_timer);
#endif
        TIMER0_MODULE_ENABLE();
    }
    return ret;
}

/**
 * 
 * @param _timer
 * @return 
 */
Std_ReturnType Timer0_DeInit(const timer0_t *_timer) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {

        ret = E_NOK;
    } else {
        TIMER0_MODULE_DISABLE();
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
        TIMER0_interruptDisable();
#endif
    }
    return ret;
}

/**
 * 
 * @param _timer
 * @param _value
 * @return 
 */
Std_ReturnType Timer0_Write_value(const timer0_t *_timer, uint16 _value) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOK;
    } else {
        TMR0H=((uint8)(_value>>8));
        TMR0L=((uint8)_value);
    }
    return ret;
}

/**
 * 
 * @param _timer
 * @param _value
 * @return 
 */
Std_ReturnType Timer0_Read_value(const timer0_t *_timer, uint16 *_value) {
    Std_ReturnType ret = E_OK;
    uint8 l_tmr0l=ZERO_INIT,l_tmr0h=ZERO_INIT;
    if (NULL == _timer) {
        ret = E_NOK;
    } else {
        l_tmr0l=TMR0L;
        l_tmr0h=TMR0H;
        *_value=(uint16)((l_tmr0h<<8)+l_tmr0l);
    }
    return ret;
}


#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE

void TMR0_ISR(void) {
    TIMER0_interruptflag_clear();
    TMR0H = ((uint8) (timer0_preload >> 8));
    TMR0L = ((uint8) timer0_preload);
    if (TMR0_interrupt_handler) {
        TMR0_interrupt_handler();
    }
}
#endif

static inline void Timer0_Prescaler_Config(const timer0_t *_timer) {
    if (TIMER0_PRESCALER_ENABLE_CFG == _timer->timer0_prescaler_enable) {
        T0CONbits.T0PS = _timer->timer0_prescaler_value;
        TIMER0_PRESCALER_ENABLE();
    } else if (TIMER0_PRESCALER_DISABLE_CFG == _timer->timer0_prescaler_enable) {
        TIMER0_PRESCALER_DISABLE();
    } else {
        /*Nothing*/
    }
}

static inline void Timer0_Mode_Select(const timer0_t *_timer) {
    if (TIMER0_TIMER_MODE_ENABLE_CFG == _timer->timer0_source_mode) {
        TIMER0_TIMER_MODE_ENABLE();
    } else if (TIMER0_COUNTER_MODE_ENABLE_CFG == _timer->timer0_source_mode) {
        TIMER0_COUNTER_MODE_ENABLE();
        if (TIMER0_COUNTER_RASING_EDGE_CFG == _timer->timer0_counter_edge) {
            TIMER0_COUNTER_RASING_EDGE_ENABLE();
        } else if (TIMER0_COUNTER_FALLING_EDGE_CFG == _timer->timer0_counter_edge) {
            TIMER0_COUNTER_FALLING_EDGE_ENABLE();
        } else {
            /*Nothing*/
        }

    } else {
        /*Nothing*/
    }
}

static inline void Timer0_Register_Size_Config(const timer0_t *_timer) {
    if (TIMER0_REGISTER_8_BIT_ENABLE_CFG == _timer->timer0_register_size) {
        TIMER0_REGISTER_8_BIT_ENABLE();
    } else if (TIMER0_REGISTER_16_BIT_ENABLE_CFG == _timer->timer0_register_size) {
        TIMER0_REGISTER_16_BIT_ENABLE();
    } else {
        /*Nothing*/
    }
}



#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE

static inline void Timer0_Interrupt_Config(const timer0_t *_timer) {
    TIMER0_interruptEnable();
    TIMER0_interruptflag_clear();
    TMR0_interrupt_handler = _timer->ADC_Iterrupt_Handler;
#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
    INTERRUPT_priorityLevelsEnable();
    if (Interrupt_high_priority == _timer->priority) {
        INTERRUPT_GlobalInterruptHighEnable();
        TIMER0_highpriorityset();
    } else if (interrupt_low_priority == _timer->priority) {
        INTERRUPT_GlobalInterruptlowEnable();
        TIMER0_lowpriorityset();
    } else {
        /*nothing*/
    }
#else 
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif
}
#endif