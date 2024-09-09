/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: Home?
 *
 * Created on September 7, 2023, 2:09 PM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

#define INTERRUPT_feature_ENABLE 1U 
//#define INTERRUPT_Priority_Levels_Enable           INTERRUPT_feature_ENABLE  
#define INTERRUPT_Priority_INTX_Levels_Enable      INTERRUPT_feature_ENABLE 
#define EXTERNAL_INTERRUPT_onchange_FEATURE_Enable INTERRUPT_feature_ENABLE 
#define ADC_INTERRUPT_FEATURE_ENABLE               INTERRUPT_feature_ENABLE 
#define TIMER0_INTERRUPT_FEATURE_ENABLE            INTERRUPT_feature_ENABLE 
#define TIMER1_INTERRUPT_FEATURE_ENABLE            INTERRUPT_feature_ENABLE 
#define TIMER2_INTERRUPT_FEATURE_ENABLE            INTERRUPT_feature_ENABLE 
#define TIMER3_INTERRUPT_FEATURE_ENABLE            INTERRUPT_feature_ENABLE 
#define CCP1_INTERRUPT_FEATURE_ENABLE              INTERRUPT_feature_ENABLE 
#define CCP2_INTERRUPT_FEATURE_ENABLE              INTERRUPT_feature_ENABLE 
#define ESURT_TX_INTERRUPT_FEATURE_ENABLE          INTERRUPT_feature_ENABLE 
#define ESURT_RX_INTERRUPT_FEATURE_ENABLE          INTERRUPT_feature_ENABLE 
#define MSSP_I2C_INTERRUPT_FEATURE_ENABLE          INTERRUPT_feature_ENABLE 
#endif	/* MCAL_INTERRUPT_GEN_CFG_H */

