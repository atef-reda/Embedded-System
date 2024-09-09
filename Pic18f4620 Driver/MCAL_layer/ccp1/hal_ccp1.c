/*
 * File:   hal_ccp1.c
 * Author: redaa
 *
 * @brief Header file for CCP1 module HAL functions.
 * Created on November 8, 2023, 8:55 PM
 */

#include "hal_ccp1.h"

/**
 * @brief Initializes the CCP1 module.
 *
 * This function configures and initializes the CCP1 module.
 *
 * @param ccp_obj The CCP1 object.
 * @return Return status indicating the success or failure of the initialization.
 *         - Returns E_OK on success
 *         - Returns E_NOK on failure
 */


#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
static inline void CCP1_Interrupt_Config(const ccp_t  *ccp_obj);
static interrupt_handler_fun CCP1_interrupt_handler = NULL;
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
static inline void CCP2_Interrupt_Config(const ccp_t  *ccp_obj);
static interrupt_handler_fun CCP2_interrupt_handler = NULL;
#endif
static Std_ReturnType CCP_CAPTURE_MODE_CFG(const ccp_t *ccp_obj);
static Std_ReturnType CCP_COMPARE_MODE_CFG(const ccp_t *ccp_obj);
static void CCP_Capture_Timer_Select(const ccp_t *ccp_obj);

Std_ReturnType CCP_Init(const ccp_t *ccp_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == ccp_obj) {
        ret = E_NOK;
    } else {
        /*Disable Module*/
        if (CCP1_INST == ccp_obj->ccp_inst) {
                    CCP1_SET_MODE(CCP_MODULE_DISABLE);
                } else if (CCP2_INST == ccp_obj->ccp_inst) {
                    CCP2_SET_MODE(CCP_MODULE_DISABLE);
                } else {
                    /*Nothing*/
        }
#if (CCP_CAPTURE_MODE_SELECTED_CFG==CCP1_SELECTED_MODE_CFG||CCP_CAPTURE_MODE_SELECTED_CFG==CCP2_SELECTED_MODE_CFG)
        if (CCP_CAPTURE_MODE_SELECTED == ccp_obj->ccp_mode) {
            CCP_CAPTURE_MODE_CFG(ccp_obj);
        }
#endif
#if (CCP_COMPAER_MODE_SELECTED_CFG==CCP1_SELECTED_MODE_CFG||CCP_COMPAER_MODE_SELECTED_CFG==CCP2_SELECTED_MODE_CFG)
        if (CCP_COMPARE_MODE_SELECTED == ccp_obj->ccp_mode) {
            CCP_COMPARE_MODE_CFG(ccp_obj);
        }
#endif
        
       
#if (CCP_PWM_MODE_SELECTED_CFG==CCP1_SELECTED_MODE_CFG||CCP_PWM_MODE_SELECTED_CFG==CCP2_SELECTED_MODE_CFG)
         if (CCP_PWM_MODE_SELECTED == ccp_obj->ccp_mode) {
            if (CCP_PWM_MODE == ccp_obj->ccp_mode_variant) {
                if (CCP1_INST == ccp_obj->ccp_inst) {
                    CCP1_SET_MODE(CCP_PWM_MODE);
                } else if (CCP2_INST == ccp_obj->ccp_inst) {
                    CCP2_SET_MODE(CCP_PWM_MODE);
                } else {
                    /*Nothing*/
                }
                /*initialize frequency for PWM*/
                PR2 = (uint8) ((_XTAL_FREQ / (ccp_obj->pwm_frequency * 4.0 * ccp_obj->timer2_postscaler_value * ccp_obj->timer2_prescaler_value)) - 1);
            } else {
                ret = E_NOK;
            }
        }
#endif

        /*Pin Initialize*/
        gpio_pin_initialize(&(ccp_obj->ccp_pin));
        /*Interrupt Configurations*/
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
        CCP1_Interrupt_Config(ccp_obj);
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
        CCP2_Interrupt_Config(ccp_obj);
#endif

    }
    return ret;
}
/**
 * @brief Deinitializes the CCP1 module.
 *
 * This function deinitializes the CCP1 module.
 *
 * @param ccp_obj The CCP1 object.
 * @return Return status indicating the success or failure of the deinitialization.
 *         - Returns E_OK on success
 *         - Returns E_NOK on failure
 */
Std_ReturnType CCP_DeInit(const ccp_t *ccp_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == ccp_obj) {
        ret = E_NOK;
    } else {

        if (CCP_PWM_MODE == ccp_obj->ccp_mode_variant) {
            if (CCP1_INST == ccp_obj->ccp_inst) {
                CCP1_SET_MODE(CCP_MODULE_DISABLE);
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
                CCP1_interruptDisable();
#endif
            } else if (CCP2_INST == ccp_obj->ccp_inst) {
                CCP2_SET_MODE(CCP_MODULE_DISABLE);
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
                CCP2_interruptDisable();
#endif
            } else {
                /*Nothing*/
            }
        }
    }
    return ret;
}
#if CCP_CAPTURE_MODE_SELECTED_CFG == CCP1_SELECTED_MODE_CFG
/**
 * @brief Checks if the CCP1 capture mode is ready.
 *
 * This function checks if the CCP1 capture mode is ready for capturing.
 *
 * @param capture_status Pointer to the capture status variable.
 * @return Return status indicating the success or failure of the check.
 *         - Returns E_OK if capture mode is ready
 *         - Returns E_NOK if capture mode is not ready
 */
Std_ReturnType CCP1_Is_Capture_Mode_Ready(uint8 *capture_status) {
    Std_ReturnType ret = E_OK;
    if (NULL == capture_status) {
        ret = E_NOK;
    } else {
        if (CCP_CAPTURE_READY == PIR1bits.CCP1IF) {
            *capture_status = CCP_CAPTURE_READY;
            CCP1_interruptflag_clear();
        } else {
            *capture_status = CCP_CAPTURE_NOT_READY;
        }
    }
    return ret;
}

/**
 * @brief Reads the value captured in CCP1 capture mode.
 *
 * This function reads the value captured in CCP1 capture mode.
 *
 * @param capture_value Pointer to the capture value variable.
 * @return Return status indicating the success or failure of the read operation.
 *         - Returns E_OK on success
 *         - Returns E_NOK on failure
 */
Std_ReturnType CCP1_Capture_Mode_Read_Value(uint16 *capture_value) {
    Std_ReturnType ret = E_OK;
    ccp_reg_t capture_reg_value = {
        .ccpr_low = 0,
        .ccpr_high = 0
    };
    if (NULL == capture_value) {
        ret = E_NOK;
    } else {
        capture_reg_value.ccpr_low == CCPR1L;
        capture_reg_value.ccpr_high == CCPR1H;
        *capture_value = capture_reg_value.ccpr_16_bit;

    }
    return ret;
}
#endif

#if CCP_COMPAER_MODE_SELECTED_CFG == CCP1_SELECTED_MODE_CFG

/**
 * @brief Checks if the CCP1 compare mode is complete.
 *
 * This function checks if the CCP1 compare mode operation is complete.
 *
 * @param compare_status Pointer to the compare status variable.
 * @return Return status indicating the success or failure of the check.
 *         - Returns E_OK if compare mode is complete
 *         - Returns E_NOK if compare mode is not complete
 */
Std_ReturnType CCP_Is_Compare_Complete(uint8 *compare_status) {
    Std_ReturnType ret = E_OK;
    if (NULL == compare_status) {
        ret = E_NOK;
    } else {
        if (CCP_COMPARE_READY == PIR1bits.CCP1IF) {
            *compare_status = CCP_COMPARE_READY;
            CCP1_interruptflag_clear();
        } else {
            *compare_status = CCP_COMPARE_NOT_READY;
        }
    }
    return ret;
}
/**
 * @brief Sets the value for CCP1 compare mode.
 *
 * This function sets the value for CCP1 compare mode.
 *
 * @param compare_value Pointer to the compare value variable.
 * @return Return status indicating the success or failure of the set operation.
 *         - Returns E_OK on success
 *         - Returns E_NOK on failure
 */
Std_ReturnType CCP1_Compare_Mode_Set_Value(const ccp_t *ccp_obj, uint16 compare_value) {
    Std_ReturnType ret = E_OK;
    ccp_reg_t compare_temp_value = {
        .ccpr_low = 0,
        .ccpr_high = 0
    };
    if (NULL == ccp_obj) {
        ret = E_NOK;
    } else {
        compare_temp_value.ccpr_16_bit = compare_value;
        if (CCP1_INST == ccp_obj->ccp_inst) {
            CCPR1L = compare_temp_value.ccpr_low;
            CCPR1H = compare_temp_value.ccpr_high;
        } else if (CCP2_INST == ccp_obj->ccp_inst) {
            CCPR2L = compare_temp_value.ccpr_low;
            CCPR2H = compare_temp_value.ccpr_high;
        } else {
            /*Nothing*/
        }
    }
    return ret;
}
#endif

#if CCP_PWM_MODE_SELECTED_CFG == CCP1_SELECTED_MODE_CFG

/**
 * @brief Sets the duty cycle for CCP1 PWM mode.
 *
 * This function sets the duty cycle for CCP1 PWM mode.
 *
 * @param duty The duty cycle value to be set.
 * @return Return status indicating the success or failure of the set operation.
 *         - Returns E_OK on success
 *         - Returns E_NOK on failure
 */
Std_ReturnType CCP_Pwm_Set_Duty(const ccp_t *ccp_obj, const uint8 duty) {
    Std_ReturnType ret = E_OK;
    uint16 l_duty_temp = 0;
    if (NULL == ccp_obj) {
        ret = E_NOK;
    } else {

        l_duty_temp = (uint16) ((PR2 + 1)*(duty / 100.0)*4);
        if (CCP1_INST == ccp_obj->ccp_inst) {
            CCP1CONbits.DC1B = (uint8) (l_duty_temp & 0x0003);
            CCPR1L = (uint8) (l_duty_temp >> 2);
        } else if (CCP2_INST == ccp_obj->ccp_inst) {
            CCP2CONbits.DC2B = (uint8) (l_duty_temp & 0x0003);
            CCPR2L = (uint8) (l_duty_temp >> 2);
        } else {
            /*Nothing*/
        }
    }


    return ret;
}

/**
 * @brief Starts CCP1 PWM mode.
 *
 * This function starts CCP1 PWM mode operation.
 *
 * @return Return status indicating the success or failure of the start operation.
 *         - Returns E_OK on success
 *         - Returns E_NOK on failure
 */
Std_ReturnType CCP_Pwm_Start(const ccp_t *ccp_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == ccp_obj) {
        ret = E_NOK;
    } else {
        if (CCP1_INST == ccp_obj->ccp_inst) {
            CCP1CONbits.CCP1M = CCP_PWM_MODE;
        } else if (CCP2_INST == ccp_obj->ccp_inst) {
            CCP2CONbits.CCP2M = CCP_PWM_MODE;
        } else {
            /*Nothing*/
        }
    }

    return ret;
}

/**
 * @brief Ends CCP1 PWM mode.
 *
 * This function ends CCP1 PWM mode operation.
 *
 * @return Return status indicating the success or failure of the end operation.
 *         - Returns E_OK on success
 *         - Returns E_NOK on failure
 */
Std_ReturnType CCP_Pwm_End(const ccp_t *ccp_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == ccp_obj) {
        ret = E_NOK;
    } else {
        if (CCP1_INST == ccp_obj->ccp_inst) {
            CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;
        } else if (CCP2_INST == ccp_obj->ccp_inst) {
            CCP2CONbits.CCP2M = CCP_MODULE_DISABLE;
        } else {
            /*Nothing*/
        }
    }


    return ret;
}
#endif

#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE

void CCP1_ISR(void) {
    CCP1_interruptflag_clear();
    if (CCP1_interrupt_handler) {
        CCP1_interrupt_handler();
    }
}
#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE

void CCP2_ISR(void) {
    CCP2_interruptflag_clear();
    if (CCP2_interrupt_handler) {
        CCP2_interrupt_handler();
    }
}
#endif

/*---------------- helper functions ----------------*/


#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE

static inline void CCP1_Interrupt_Config(const ccp_t *ccp_obj) {
    CCP1_interruptEnable();
    CCP1_interruptflag_clear();
    CCP1_interrupt_handler = ccp_obj->CCP1_Iterrupt_Handler;
#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
    INTERRUPT_priorityLevelsEnable();
    if (Interrupt_high_priority == ccp_obj->ccp1_priority) {
        INTERRUPT_GlobalInterruptHighEnable();
        CCP1_highpriorityset();
    } else if (interrupt_low_priority == ccp_obj->ccp1_priority) {
        INTERRUPT_GlobalInterruptlowEnable();
        CCP1_lowpriorityset();
    } else {
        /*nothing*/
    }
#else 
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif
    
    
}
#endif


#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
static inline void CCP2_Interrupt_Config(const ccp_t *ccp_obj) {
    CCP2_interruptEnable();
    CCP2_interruptflag_clear();
    CCP2_interrupt_handler = ccp_obj->CCP2_Iterrupt_Handler;
#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
    INTERRUPT_priorityLevelsEnable();
    if (Interrupt_high_priority == ccp_obj->ccp2_priority) {
        INTERRUPT_GlobalInterruptHighEnable();
        CCP2_highpriorityset();
    } else if (interrupt_low_priority == ccp_obj->ccp2_priority) {
        INTERRUPT_GlobalInterruptlowEnable();
        CCP2_lowpriorityset();
    } else {
        /*nothing*/
    }
#else 
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif
    
    
}
#endif


static void CCP_Capture_Timer_Select(const ccp_t *ccp_obj) {
    if (CCP1_CCP2_TIMER1 == ccp_obj->ccp_capture_timer) {
        /* Timer1 is the capture/compare clock source for the CCP modules*/
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    } else if (CCP2_TIMER3_CCP1_TIMER1 == ccp_obj->ccp_capture_timer) {
        /* Timer3 is the capture/compare clock source for CCP2;*/
        /*Timer1 is the capture/compare clock source for CCP1*/
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    } else if (CCP2_CCP1_TIMER3 == ccp_obj->ccp_capture_timer) {
        /* Timer3 is the capture/compare clock source for the CCP modules*/
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 1;
    } else {
        /*Nothing*/
    }
}

#if (CCP_COMPAER_MODE_SELECTED_CFG==CCP1_SELECTED_MODE_CFG||CCP_COMPAER_MODE_SELECTED_CFG==CCP2_SELECTED_MODE_CFG)

static Std_ReturnType CCP_COMPARE_MODE_CFG(const ccp_t *ccp_obj)
{
    Std_ReturnType ret = E_OK;
        ret = E_OK;
        if (CCP1_INST == ccp_obj->ccp_inst) {
            switch (ccp_obj->ccp_mode_variant) {
                case CCP_COMPARE_MODE_SET_PIN_LOW:
                    CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
                    break;
                case CCP_COMPARE_MODE_SET_PIN_HIGH:
                    CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
                    break;
                case CCP_COMPARE_MODE_TOGGLE_ON_MATCH:
                    CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
                    break;
                case CCP_COMPARE_MODE_GEN_SW_INTERRUPT:
                    CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
                    break;
                case CCP_COMPARE_MODE_GEN_EVENT:
                    CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);
                    break;
                default:
                    ret = E_NOK;
                    break;
            }
        } else if (CCP2_INST == ccp_obj->ccp_inst) {
            switch (ccp_obj->ccp_mode_variant) {
                case CCP_COMPARE_MODE_SET_PIN_LOW:
                    CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
                    break;
                case CCP_COMPARE_MODE_SET_PIN_HIGH:
                    CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
                    break;
                case CCP_COMPARE_MODE_TOGGLE_ON_MATCH:
                    CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
                    break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT:
                CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
                break;
            case CCP_COMPARE_MODE_GEN_EVENT:
                CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);
                break;
            default:
                ret = E_NOK;
                break;
        }
    } else {
        /*Nothing*/
    }
    CCP_Capture_Timer_Select(ccp_obj);
    return ret;
}
#endif


#if (CCP_CAPTURE_MODE_SELECTED_CFG==CCP1_SELECTED_MODE_CFG||CCP_CAPTURE_MODE_SELECTED_CFG==CCP2_SELECTED_MODE_CFG)
static Std_ReturnType CCP_CAPTURE_MODE_CFG(const ccp_t *ccp_obj)
{
    Std_ReturnType ret = E_OK;
        ret = E_OK;
        if (CCP1_INST == ccp_obj->ccp_inst) {
            switch (ccp_obj->ccp_mode_variant) {
                case CCP_CAPTURE_MODE_1_FALLING_EDGE:
                    CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_1_RISING_EDGE:
                    CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_4_RISING_EDGE:
                    CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_16_RISING_EDGE:
                    CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);
                    break;
                default:
                    ret = E_NOK;
                    break;
            }
        } else if (CCP2_INST == ccp_obj->ccp_inst) {
           switch (ccp_obj->ccp_mode_variant) {
                case CCP_CAPTURE_MODE_1_FALLING_EDGE:
                    CCP2_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_1_RISING_EDGE:
                    CCP2_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_4_RISING_EDGE:
                    CCP2_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_16_RISING_EDGE:
                    CCP2_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);
                    break;
                default:
                    ret = E_NOK;
                    break;
            }
    } else {
        /*Nothing*/
    }
    CCP_Capture_Timer_Select(ccp_obj);
    return ret;
}
#endif
