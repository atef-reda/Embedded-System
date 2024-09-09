/* 
 * File:   hal_adc.h
 * Author: redaa
 *
 * Created on September 29, 2023, 8:43 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/*section: includes */
#include "hal_adc_cfg.h"
#include "xc.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "../interrupt/mcal_external_interrupt.h"
/*--------------section : macro declarations ---------------*/
/* A/D Conversion Status bit / A/D conversion in progress/ A/D Idle*/
#define ADC_CONVERSION_STATUS() (ADCON0bits.GO_DONE)
/*start the analog_to_digital conversion */
#define ADC_START_CONVERSION() (ADCON0bits.GO_DONE=1)
/* A/D Converter module is enabled / A/D Converter module is disabled*/
#define ADC_CONVERTER_ENABLE()  (ADCON0bits.ADON=1)
#define ADC_CONVERTER_DISABLE()  (ADCON0bits.ADON=0)

/**
 * 
 * @param Voltage Reference Configuration
 * @brief ADC Enable voltage Reference  VREF- (AN2)/  VREF+ (AN3)
 * ADC Disable Voltage Reference Vss Vdd
 */
#define ADC_VOLTAGE_REFERANCE_ENABLE()   do{ADCON1bits.VCFG1=1;\
                                          ADCON1bits.VCFG0=1; }while(0)
#define ADC_VOLTAGE_REFERANCE_DISABLE()  do{ADCON1bits.VCFG1=0;\
                                          ADCON1bits.VCFG0=0; }while(0)
/*
 * when ADC_AN4_ANLOG_FUNCTIONALITY configured ,this means AN4,AN3,AN2,AN1,AN0 
 * are analog Functionality 
 */
#define ADC_AN0_ANLOG_FUNCTIONALITY()    0X0E
#define ADC_AN1_ANLOG_FUNCTIONALITY()    0X0D
#define ADC_AN2_ANLOG_FUNCTIONALITY()    0X0C
#define ADC_AN3_ANLOG_FUNCTIONALITY()    0X0B
#define ADC_AN4_ANLOG_FUNCTIONALITY()    0X0A
#define ADC_AN5_ANLOG_FUNCTIONALITY()    0X09
#define ADC_AN6_ANLOG_FUNCTIONALITY()    0X08
#define ADC_AN7_ANLOG_FUNCTIONALITY()    0X07
#define ADC_AN8_ANLOG_FUNCTIONALITY()    0X06
#define ADC_AN9_ANLOG_FUNCTIONALITY()    0X05
#define ADC_AN10_ANLOG_FUNCTIONALITY()   0X04
#define ADC_AN11_ANLOG_FUNCTIONALITY()   0X03
#define ADC_AN12_ANLOG_FUNCTIONALITY()   0X02
#define ADC_ALL_ANLOG_FUNCTIONALITY()    0X00
#define ADC_ALL_DIGITAL_FUNCTIONALITY()  0X0F

#define ADC_RESULT_RIGHT 0X01
#define ADC_RESULT_LEFT  0X00

#define ADC_VOLTAGE_REFERANCE_ENABLED   0X01
#define ADC_VOLTAGE_REFERANCE_DISABLED  0X00
/*
 * @brief Analog-To-Digital Port Configuration Control
 * @note Example ADC_ANLOG_DIGITAL_PORT_CONFIGURATION(ADC_AN7_ANLOG_FUNCTIONALITY());
 * when ADC_AN4_ANLOG_FUNCTIONALITY configured ,this means AN4,AN3,AN2,AN1,AN0 
 * are analog Functionality 
 */
#define ADC_ANLOG_DIGITAL_PORT_CONFIGURATION(_CONFIG)    (ADCON1bits.PCFG=_CONFIG)
/*ADC Result Format Select Bit*/
#define ADC_RESULT_RIGHT_FORMAT()    (ADCON0bits.ADON=1)
#define ADC_RESULT_LEFT_FORMAT()    (ADCON0bits.ADON=0)
/*section: macro functions declarations */
/*section: data types declarations*/
typedef enum
{
    ADC_CHANAL_AN0,
    ADC_CHANAL_AN1,
    ADC_CHANAL_AN2,
    ADC_CHANAL_AN3,
    ADC_CHANAL_AN4,
    ADC_CHANAL_AN5,
    ADC_CHANAL_AN6,
    ADC_CHANAL_AN7,
    ADC_CHANAL_AN8,
    ADC_CHANAL_AN9,
    ADC_CHANAL_AN10,
    ADC_CHANAL_AN11,
    ADC_CHANAL_AN12,
}adc_chanel_select_t;

/**
 * @brief A/D acquisition time select
 * @note acquisition time is time required for ADC to capture the
 * input voltage during conversion
 * 
 * @note acquisition time of a successive approximation register (SAR) is required
 * time to charge the holding capacitor
 */
typedef enum
{
    ADC_0_TAD,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD,
}adc_acquisition_time_t;
typedef enum
{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64,
}adc_conversion_clock_t;

typedef struct {
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
    void (* ADC_Iterrupt_Handler)(void);
#if INTERRUPT_Priority_Levels_Enable==INTERRUPT_feature_ENABLE
    interrupt_priority_cfg priority;
#endif
    
#endif
    adc_acquisition_time_t acquisition_time;
    adc_conversion_clock_t conversion_clock;
    adc_chanel_select_t chanel_select;
    uint8 voltage_referance : 1;
    uint8 result_format : 1;
}adc_conf_t;
/*----------------section: function declarations------------------*/
Std_ReturnType ADC_Init(const adc_conf_t *_adc);
Std_ReturnType ADC_DeInit(const adc_conf_t *_adc);
Std_ReturnType ADC_Select_Channel(const adc_conf_t *_adc,const adc_chanel_select_t channel);
Std_ReturnType ADC_Start_Conversion(const adc_conf_t *_adc);
Std_ReturnType ADC_Is_Conversion_Done(const adc_conf_t *_adc,uint8 *conversion_status);
Std_ReturnType ADC_Get_Conversion_Result(const adc_conf_t *_adc,uint16 *conversion_result);
Std_ReturnType ADC_Get_Conversion_Blocking(const adc_conf_t *_adc,adc_chanel_select_t channel,uint16 *conversion_result);
Std_ReturnType ADC_Start_Conversion_Interrupt(const adc_conf_t *_adc, adc_chanel_select_t channel);


#endif	/* HAL_ADC_H */

