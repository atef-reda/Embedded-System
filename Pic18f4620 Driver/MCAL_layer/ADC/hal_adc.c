/*
 * File:   hal_adc.c
 * Author: redaa
 *
 * Created on September 29, 2023, 8:44 PM
 */


#include "hal_adc.h"


static interrupt_handler_fun ADC_interrupt_handler=NULL;


static void inline adc_input_channel_port_configure( const adc_chanel_select_t channel);
static void inline adc_select_result_format(const adc_conf_t *_adc);
static void inline adc_confegration_referance(const adc_conf_t *_adc);
/**
 * 
 * @param _adc
 * @return 
 */
Std_ReturnType ADC_Init(const adc_conf_t *_adc) {
    Std_ReturnType ret = E_OK;
    if (NULL == _adc) {
        ret = E_NOK;
    } else {
        /*Disable the ADC*/
        ADC_CONVERTER_DISABLE();
        /*Configure the acquisition time*/
        ADCON2bits.ACQT = _adc->acquisition_time;
        /*Configure The Configuration Clock*/
        ADCON2bits.ADCS = _adc->conversion_clock;
        /*Configure The Default Channel*/
        ADCON0bits.CHS = _adc->chanel_select;
        adc_input_channel_port_configure(_adc->chanel_select);
        /*Configure The Interrupt*/
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
        ADC_interruptEnable();
        ADC_interruptflag_clear();
        ADC_interrupt_handler = _adc->ADC_Iterrupt_Handler;
#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
        INTERRUPT_priorityLevelsEnable();
        if (Interrupt_high_priority == _adc->priority) {
            INTERRUPT_GlobalInterruptHighEnable();
            ADC_highpriorityset();
        } else if (interrupt_low_priority == _adc->priority) {
            INTERRUPT_GlobalInterruptlowEnable();
            ADC_lowpriorityset();
        } else {
            /*nothing*/
        }
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
      

        
#endif
        /*Configure The Result Format*/
        adc_select_result_format(_adc);
        /*Configure The Voltage Reference*/
       adc_confegration_referance(_adc);
        /*Enable The ADC*/
        ADC_CONVERTER_ENABLE();
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @return 
 */
Std_ReturnType ADC_DeInit(const adc_conf_t *_adc) {
    Std_ReturnType ret = E_OK;
    if (NULL == _adc) {
        ret = E_NOK;
    } else {
        /*Disable the ADC*/
        ADC_CONVERTER_DISABLE();
        /*Configure The Interrupt*/
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
                ADC_interruptDisable();
#endif
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @param channel
 * @return 
 */
Std_ReturnType ADC_Select_Channel(const adc_conf_t *_adc,const adc_chanel_select_t channel) {
    Std_ReturnType ret=E_OK;
    if(NULL ==_adc) {
        ret = E_NOK;
    } else {
        ADCON0bits.CHS = channel;
        adc_input_channel_port_configure(channel);
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @return 
 */
Std_ReturnType ADC_Start_Conversion(const adc_conf_t *_adc) {
    Std_ReturnType ret = E_OK;
    if (NULL == _adc) {
        ret = E_NOK;
    } else {
        ADC_START_CONVERSION();
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @param conversion_status
 * @return 
 */
Std_ReturnType ADC_Is_Conversion_Done(const adc_conf_t *_adc, uint8 *conversion_status) {
    Std_ReturnType ret = E_OK;
    if ((NULL == _adc) || (NULL == conversion_status)) {
        ret = E_NOK;
    } else {
        *conversion_status = (uint8) (!ADCON0bits.GO_nDONE);
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @param conversion_result
 * @return 
 */
Std_ReturnType ADC_Get_Conversion_Result(const adc_conf_t *_adc, uint16 *conversion_result) {
    Std_ReturnType ret = E_OK;
    if ((NULL == _adc) || NULL == conversion_result) {
        ret = E_NOK;
    } else {
        if (ADC_RESULT_RIGHT == _adc->result_format) {
            *conversion_result = ((uint16) (((ADRESH << 8) + ADRESL)));
        } else if (ADC_RESULT_RIGHT == _adc->result_format) {
            *conversion_result = ((uint16) (((ADRESH << 8) + ADRESL)) >> 6);
        } else {
            *conversion_result = ((uint16) (((ADRESH << 8) + ADRESL)));
        }
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @param channel
 * @param conversion_status
 * @return 
 */
Std_ReturnType ADC_Get_Conversion_Blocking(const adc_conf_t *_adc, adc_chanel_select_t channel, uint16 *conversion_result) {
    Std_ReturnType ret = E_OK;
    if (NULL == _adc) {
        ret = E_NOK;
    } else {
        /*select the A/D channel*/
        ret=ADC_Select_Channel(_adc,channel);
        /*start the conversion*/
        ret=ADC_Start_Conversion(_adc);
        /*check if conversion is completed*/
        while(ADCON0bits.GO_nDONE);
        ADC_Get_Conversion_Result(_adc,conversion_result);
    }
    return ret;
}

Std_ReturnType ADC_Start_Conversion_Interrupt(const adc_conf_t *_adc, adc_chanel_select_t channel) {
    Std_ReturnType ret = E_OK;
    if (NULL == _adc) {
        ret = E_NOK;
    } else {
        /*select the A/D channel*/
        ret=ADC_Select_Channel(_adc,channel);
        /*start the conversion*/
        ret=ADC_Start_Conversion(_adc);
    return ret;
}
}

static void inline adc_input_channel_port_configure( const adc_chanel_select_t channel) {
    switch (channel) {
        case ADC_CHANAL_AN0:
            set_bit(TRISA, _TRISA_RA0_POSN);
            break;
        case ADC_CHANAL_AN1:
            set_bit(TRISA, _TRISA_RA1_POSN);
            break;
        case ADC_CHANAL_AN2:
            set_bit(TRISA, _TRISA_RA2_POSN);
            break;
        case ADC_CHANAL_AN3:
            set_bit(TRISA, _TRISA_RA3_POSN);
            break;
        case ADC_CHANAL_AN4:
            set_bit(TRISA, _TRISA_RA5_POSN);
            break;
        case ADC_CHANAL_AN5:
            set_bit(TRISA, _TRISE_RE0_POSN);
            break;
        case ADC_CHANAL_AN6:
            set_bit(TRISA, _TRISE_RE1_POSN);
            break;
        case ADC_CHANAL_AN7:
            set_bit(TRISA, _TRISE_RE2_POSN);
            break;
        case ADC_CHANAL_AN8:
            set_bit(TRISA, _TRISB_RB2_POSN);
            break;
        case ADC_CHANAL_AN9:
            set_bit(TRISA, _TRISB_RB3_POSN);
            break;
        case ADC_CHANAL_AN10:
            set_bit(TRISA, _TRISB_RB1_POSN);
            break;
        case ADC_CHANAL_AN11:
            set_bit(TRISA, _TRISB_RB4_POSN);
            break;
        case ADC_CHANAL_AN12:
            set_bit(TRISA, _TRISB_RB0_POSN);
            break;
        default:
            /*Nothing*/
            break;
    }
}

static void inline adc_select_result_format(const adc_conf_t *_adc) {
    if (ADC_RESULT_LEFT == _adc->result_format) {
        ADC_RESULT_LEFT_FORMAT();
    } else if (ADC_RESULT_RIGHT == _adc->result_format) {
        ADC_RESULT_RIGHT_FORMAT();
    } else {
        ADC_RESULT_RIGHT_FORMAT();
    }
}

static void inline adc_confegration_referance(const adc_conf_t *_adc) {
    if (ADC_VOLTAGE_REFERANCE_ENABLED == _adc->voltage_referance) {
        ADC_VOLTAGE_REFERANCE_ENABLE();
    } else if (ADC_VOLTAGE_REFERANCE_DISABLED == _adc->voltage_referance) {
        ADC_VOLTAGE_REFERANCE_DISABLE();
    } else {
        ADC_VOLTAGE_REFERANCE_DISABLE();
    }
}
void ADC_ISR(void)
{
    ADC_interruptflag_clear();
    if(ADC_interrupt_handler)
    {
        ADC_interrupt_handler();
    }
}

