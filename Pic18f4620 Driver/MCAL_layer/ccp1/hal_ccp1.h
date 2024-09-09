/* 
 * File:   hal_ccp1.h
 * Author: redaa
 *
 * Created on November 8, 2023, 8:54 PM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/*section: includes */
#include "ccp1_cfg.h"
#include <xc.h>
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupt/mcal_internal_interrupt.h"
/*section : macro declarations */
#define CCP_MODULE_DISABLE                 ((uint8)0X00)

#define CCP_CAPTURE_MODE_1_FALLING_EDGE    ((uint8)0X04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE     ((uint8)0X05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE     ((uint8)0X06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE    ((uint8)0X07)

#define CCP_COMPARE_MODE_SET_PIN_LOW       ((uint8)0X08)
#define CCP_COMPARE_MODE_SET_PIN_HIGH      ((uint8)0X09)
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH   ((uint8)0X02)
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT  ((uint8)0X0A)
#define CCP_COMPARE_MODE_GEN_EVENT         ((uint8)0X0B)

#define CCP_PWM_MODE                       ((uint8)0X0C)

/* ccp1_capture_mode_state */
#define CCP_CAPTURE_NOT_READY              0X00
#define CCP_CAPTURE_READY                  0X01
/* ccp1_compare_mode_state */
#define CCP_COMPARE_NOT_READY              0X00
#define CCP_COMPARE_READY                  0X01

/*------------ timer2 pre_scaler -------------*/
#define CCP_PRESCALER_VALUE_DIV_1            1
#define CCP_PRESCALER_VALUE_DIV_4            4
#define CCP_PRESCALER_VALUE_DIV_16           16

/*------------ timer2 post_scaler -------------*/
#define CCP_POSTSCALER_VALUE_DIV_1             1
#define CCP_POSTSCALER_VALUE_DIV_2             2
#define CCP_POSTSCALER_VALUE_DIV_3             3
#define CCP_POSTSCALER_VALUE_DIV_4             4
#define CCP_POSTSCALER_VALUE_DIV_5             5
#define CCP_POSTSCALER_VALUE_DIV_6             6
#define CCP_POSTSCALER_VALUE_DIV_7             7
#define CCP_POSTSCALER_VALUE_DIV_8             8
#define CCP_POSTSCALER_VALUE_DIV_9             9
#define CCP_POSTSCALER_VALUE_DIV_10            10
#define CCP_POSTSCALER_VALUE_DIV_11            11
#define CCP_POSTSCALER_VALUE_DIV_12            12
#define CCP_POSTSCALER_VALUE_DIV_13            13
#define CCP_POSTSCALER_VALUE_DIV_14            14
#define CCP_POSTSCALER_VALUE_DIV_15            15
#define CCP_POSTSCALER_VALUE_DIV_16            16
/*section: macro functions declarations */
#define CCP1_SET_MODE(_CONFIG_)             (CCP1CONbits.CCP1M=_CONFIG_)
#define CCP2_SET_MODE(_CONFIG_)             (CCP2CONbits.CCP2M=_CONFIG_)

//#define 

/*section: data types declarations*/
typedef union {

    struct {
        uint8 ccpr_low;
        uint8 ccpr_high;
    };

    struct {
        uint16 ccpr_16_bit;
    };
} ccp_reg_t;

typedef enum
{
    CCP_CAPTURE_MODE_SELECTED,
    CCP_COMPARE_MODE_SELECTED,
    CCP_PWM_MODE_SELECTED,
}ccp_mode_t;
typedef enum
{
    CCP1_INST,
    CCP2_INST
}ccp_inst_t;

typedef enum
{
    CCP1_CCP2_TIMER1,
    CCP2_TIMER3_CCP1_TIMER1,
    CCP2_CCP1_TIMER3,
}ccp_capture_timer_t;
typedef struct {
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
    void (* CCP1_Iterrupt_Handler)(void);
#if INTERRUPT_Priority_Levels_Enable==INTERRUPT_feature_ENABLE
    interrupt_priority_cfg ccp1_priority;
#endif
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
    void (* CCP2_Iterrupt_Handler)(void);
#if INTERRUPT_Priority_Levels_Enable==INTERRUPT_feature_ENABLE
    interrupt_priority_cfg ccp2_priority;
#endif
#endif
    
    ccp_mode_t ccp_mode;
    ccp_inst_t  ccp_inst;
    uint8 ccp_mode_variant;
    pin_config_t ccp_pin;
    ccp_capture_timer_t ccp_capture_timer;
#if (CCP_PWM_MODE_SELECTED_CFG==CCP1_SELECTED_MODE_CFG||CCP_PWM_MODE_SELECTED_CFG==CCP2_SELECTED_MODE_CFG)
    uint32 pwm_frequency;
    uint8 timer2_prescaler_value : 2;
    uint8 timer2_postscaler_value : 4;
#endif

} ccp_t;
/*section: function declarations*/
Std_ReturnType CCP_Init(const ccp_t *ccp_obj);
Std_ReturnType CCP_DeInit(const ccp_t *ccp_obj);
#if CCP_CAPTURE_MODE_SELECTED_CFG==CCP1_SELECTED_MODE_CFG
Std_ReturnType CCP1_Is_Capture_Mode_Ready(uint8 *capture_status);
Std_ReturnType CCP1_Capture_Mode_Read_Value(uint16 *capture_value);

#endif
#if CCP_COMPAER_MODE_SELECTED_CFG==CCP1_SELECTED_MODE_CFG
    
Std_ReturnType CCP1_Is_Compare_Complete(uint8 *compare_status);
Std_ReturnType CCP1_Compare_Mode_Set_Value(const ccp_t *ccp_obj,uint16 compare_value);
#endif
#if CCP_PWM_MODE_SELECTED_CFG==CCP1_SELECTED_MODE_CFG
Std_ReturnType CCP_Pwm_Set_Duty(const ccp_t *ccp_obj,const uint8 duty);
Std_ReturnType CCP_Pwm_Start(const ccp_t *ccp_obj);
Std_ReturnType CCP_Pwm_End(const ccp_t *ccp_obj);
#endif
#endif	/* HAL_CCP1_H */

