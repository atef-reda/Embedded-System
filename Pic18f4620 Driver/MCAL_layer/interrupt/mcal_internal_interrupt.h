/* 
 * File:   mcal_internal_interrupt.h
 * Author: Home?
 *
 * Created on September 7, 2023, 11:41 AM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H
/*..............includes.............*/
#include "mcal_interrupt_config.h"
/*...............macro declarations........*/
/*...............macro function declarations......*/
                /*ADC MODULE*/
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
/*this routine clears the interrupt enable for the adc module*/
#define ADC_interruptDisable()  (PIE1bits.ADIE=0)
/*this routine sets the interrupt enable for the adc module*/
#define ADC_interruptEnable()  (PIE1bits.ADIE=1)
/*this routine clears the interrupt flag for the adc module*/
#define ADC_interruptflag_clear()  (PIR1bits.ADIF=0) 

#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
/*this routine set the adc interrupt priority to be high priority*/
#define ADC_highpriorityset()           (IPR1bits.ADIP=1)
/*this routine set the adc interrupt priority to be low priority*/
#define ADC_lowpriorityset()             (IPR1bits.ADIP=0)
#endif 

#endif
                   /*TIMER0 MEDULE*/
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
/*this routine clears the interrupt enable for the timer0 module*/
#define TIMER0_interruptDisable()     (INTCONbits.TMR0IE=0)
/*this routine sets the interrupt enable for the timer0 module*/
#define TIMER0_interruptEnable()      (INTCONbits.TMR0IE=1)
/*this routine clears the interrupt flag for the timer0 module*/
#define TIMER0_interruptflag_clear()  (INTCONbits.TMR0IF=0)

#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
/*this routine set the timer0 interrupt priority to be high priority*/
#define TIMER0_highpriorityset()          (INTCON2bits.TMR0IP=1)
/*this routine set the timer0 interrupt priority to be low priority*/
#define TIMER0_lowpriorityset()           (INTCON2bits.TMR0IP=0)
#endif 

#endif

                   /*TIMER1 MEDULE*/
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
/*this routine clears the interrupt enable for the timer1 module*/
#define TIMER1_interruptDisable()     (PIE1bits.TMR1IE=0)
/*this routine sets the interrupt enable for the timer1 module*/
#define TIMER1_interruptEnable()      (PIE1bits.TMR1IE=1)
/*this routine clears the interrupt flag for the timer1 module*/
#define TIMER1_interruptflag_clear()  (PIR1bits.TMR1IF=0)

#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
/*this routine set the timer1 interrupt priority to be high priority*/
#define TIMER1_highpriorityset()          (IPR1bits.TMR1IP=1)
/*this routine set the timer1 interrupt priority to be low priority*/
#define TIMER1_lowpriorityset()           (IPR1bits.TMR1IP=0)
#endif 

#endif

                   /*TIMER2 MEDULE*/
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
/*this routine clears the interrupt enable for the timer2 module*/
#define TIMER2_interruptDisable()         (PIE1bits.TMR2IE=0)
/*this routine sets the interrupt enable for the timer2 module*/
#define TIMER2_interruptEnable()          (PIE1bits.TMR2IE=1)
/*this routine clears the interrupt flag for the timer2 module*/
#define TIMER2_interruptflag_clear()      (PIR1bits.TMR2IF=0)

#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
/*this routine set the timer2 interrupt priority to be high priority*/
#define TIMER2_highpriorityset()          (IPR1bits.TMR2IP=1)
/*this routine set the timer2 interrupt priority to be low priority*/
#define TIMER2_lowpriorityset()           (IPR1bits.TMR2IP=0)
#endif 

#endif

                   /*TIMER3 MEDULE*/
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
/*this routine clears the interrupt enable for the timer3 module*/
#define TIMER3_interruptDisable()         (PIE2bits.TMR3IE=0)
/*this routine sets the interrupt enable for the timer3 module*/
#define TIMER3_interruptEnable()          (PIE2bits.TMR3IE=1)
/*this routine clears the interrupt flag for the timer3 module*/
#define TIMER3_interruptflag_clear()      (PIR2bits.TMR3IF=0)

#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
/*this routine set the timer3 interrupt priority to be high priority*/
#define TIMER3_highpriorityset()          (IPR2bits.TMR3IP=1)
/*this routine set the timer3 interrupt priority to be low priority*/
#define TIMER3_lowpriorityset()           (IPR2bits.TMR3IP=0)
#endif 
#endif 
                   /*CCP1 MEDULE*/
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
/*this routine clears the interrupt enable for the CCP1 module*/
#define CCP1_interruptDisable()         (PIE1bits.CCP1IE=0)
/*this routine sets the interrupt enable for the CCP1 module*/
#define CCP1_interruptEnable()          (PIE1bits.CCP1IE=1)
/*this routine clears the interrupt flag for the CCP1 module*/
#define CCP1_interruptflag_clear()      (PIR1bits.CCP1IF=0)

#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
/*this routine set the CCP1 interrupt priority to be high priority*/
#define CCP1_highpriorityset()          (IPR1bits.CCP1IP=1)
/*this routine set the CCP1 interrupt priority to be low priority*/
#define CCP1_lowpriorityset()           (IPR1bits.CCP1IP=0)
#endif 


#endif

                   /*CCP2 MEDULE*/
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
/*this routine clears the interrupt enable for the CCP2 module*/
#define CCP2_interruptDisable()         (PIE2bits.CCP2IE=0)
/*this routine sets the interrupt enable for the CCP2 module*/
#define CCP2_interruptEnable()          (PIE2bits.CCP2IE=1)
/*this routine clears the interrupt flag for the CCP2 module*/
#define CCP2_interruptflag_clear()      (PIR2bits.CCP2IF=0)

#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
/*this routine set the CCP2 interrupt priority to be high priority*/
#define CCP2_highpriorityset()          (IPR2bits.CCP2IP=1)
/*this routine set the CCP2 interrupt priority to be low priority*/
#define CCP2_lowpriorityset()           (IPR2bits.CCP2IP=0)
#endif 


#endif

                   /*ESURT_TX MEDULE*/
#if ESURT_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
/*this routine clears the interrupt enable for the ESURT_TX module*/
#define ESURT_TX_interruptDisable()         (PIE1bits.TXIE=0)
/*this routine sets the interrupt enable for the ESURT_TX module*/
#define ESURT_TX_interruptEnable()          (PIE1bits.TXIE=1)

#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
/*this routine set the ESURT_TX interrupt priority to be high priority*/
#define ESURT_TX_highpriorityset()          (IPR1bits.TXIP=1)
/*this routine set the ESURT_TX interrupt priority to be low priority*/
#define ESURT_TX_lowpriorityset()           (IPR1bits.TXIP=0)
#endif 


#endif

                   /*ESURT_RX MEDULE*/
#if ESURT_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
/*this routine clears the interrupt enable for the ESURT_RX module*/
#define ESURT_RX_interruptDisable()         (PIE1bits.RCIE=0)
/*this routine sets the interrupt enable for the ESURT_RX module*/
#define ESURT_RX_interruptEnable()          (PIE1bits.RCIE=1)

#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
/*this routine set the ESURT_RX interrupt priority to be high priority*/
#define ESURT_RX_highpriorityset()          (IPR1bits.RCIP=1)
/*this routine set the ESURT_RX interrupt priority to be low priority*/
#define ESURT_RX_lowpriorityset()           (IPR1bits.RCIP=0)
#endif 


#endif

                   /*ESURT_I2c MEDULE*/
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
/* This routine clears the interrupt enable for the MSSP I2C Module */
#define MSSP_I2C_InterruptDisable()         (PIE1bits.SSPIE = 0)
#define MSSP_I2C_BUS_COL_InterruptDisable() (PIE2bits.BCLIE = 0)
/* This routine sets the interrupt enable for the MSSP I2C Module */
#define MSSP_I2C_InterruptEnable()          (PIE1bits.SSPIE = 1)
#define MSSP_I2C_BUS_COL_InterruptEnable()  (PIE2bits.BCLIE = 1)
/* This routine clears the interrupt flag for the MSSP I2C Module */
#define MSSP_I2C_InterruptFlagClear()         (PIR1bits.SSPIF = 0)
#define MSSP_I2C_BUS_COL_InterruptFlagClear() (PIR2bits.BCLIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_feature_ENABLE 
/* This routine set the MSSP I2C Module Interrupt Priority to be High priority */
#define MSSP_I2C_HighPrioritySet()          (IPR1bits.SSPIP = 1)
#define MSSP_I2C_BUS_COL_HighPrioritySet()  (IPR2bits.BCLIP = 1)
/* This routine set the MSSP I2C Module Interrupt Priority to be Low priority */
#define MSSP_I2C_LowPrioritySet()           (IPR1bits.SSPIP = 0)
#define MSSP_I2C_BUS_COL_LowPrioritySet()   (IPR2bits.BCLIP = 0)
#endif
#endif
/*...............data type declarations......*/
/*................software interfaces declarations........*/

#endif	/* MCAL_INTERNAL_INTERRUPT_H */
