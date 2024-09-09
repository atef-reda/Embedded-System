/* 
 * File:   mcal_manager_interrupt.h
 * Author: Home?
 *
 * Created on September 7, 2023, 11:42 AM
 */

#ifndef MCAL_MANAGER_INTERRUPT_H
#define	MCAL_MANAGER_INTERRUPT_H
/*..............includes.............*/
#include "mcal_interrupt_config.h"
#include "../ADC/hal_adc.h"
#include "../Timer/hal_timer0.h"
#include "../Timer/hal_timer1.h"
#include "../Timer/hal_timer2.h"
#include "../Timer/hal_timer3.h"
#include "../ccp1/hal_ccp1.h"
/*...............macro declarations........*/
/*...............macro function declarations......*/
/*...............data type declarations......*/
/*................software interfaces declarations........*/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 RB4_source);
void RB5_ISR(uint8 RB5_source);
void RB6_ISR(uint8 RB6_source);
void RB7_ISR(uint8 RB7_source);
void ADC_ISR(void);
void TMR0_ISR(void);
void TMR1_ISR(void);
void TMR2_ISR(void);
void TMR3_ISR(void);
void CCP1_ISR(void);
void CCP2_ISR(void);
void ESURT_TX_ISR(void);
void ESURT_RX_ISR(void);
void MSSP_I2C_ISR(void);
void MSSP_I2C_BC_ISR(void);







#endif	/* MCAL_MANAGER_INTERRUPT_H */

