/* 
 * File:   mcal_manager_interrupt.c
 * Author: Home?
 *
 * Created on September 7, 2023, 11:42 AM
 */
#include "mcal_manager_interrupt.h"
static volatile uint8 RB4_flag =1 ,RB5_flag =1 ,RB6_flag =1 ,RB7_flag =1 ;
#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE
void __interrupt() interruptManagerHigh(void){
 if((INTERRUPT_ENABLE==INTCONbits.INT0IE) &&(INTERRUPT_OCCUR==INTCONbits.INT0IF)){
        INT0_ISR();
    }else{
        /*nothing*/
    }
  if((INTERRUPT_ENABLE==INTCON3bits.INT2IE) &&(INTERRUPT_OCCUR==INTCON3bits.INT2IF)){
        INT2_ISR();
    }else{
        /*nothing*/
    }
 

}
void __interrupt(low_priority) interruptManagerLow(void){
if((INTERRUPT_ENABLE==INTCON3bits.INT1IE) &&(INTERRUPT_OCCUR==INTCON3bits.INT1F)){
        INT1_ISR();
    }else{
        /*nothing*/
    }

}
    

#else
void __interrupt() interruptManager(void){
    if((INTERRUPT_ENABLE==INTCONbits.INT0IE) &&(INTERRUPT_OCCUR==INTCONbits.INT0IF)){
        INT0_ISR();
    }else{
        /*nothing*/
    }
    if((INTERRUPT_ENABLE==INTCON3bits.INT1IE) &&(INTERRUPT_OCCUR==INTCON3bits.INT1IF)){
        INT1_ISR();
    }else{
        /*nothing*/
    }
    if((INTERRUPT_ENABLE==INTCON3bits.INT2IE) &&(INTERRUPT_OCCUR==INTCON3bits.INT2IF)){
        INT2_ISR();
    }else{
        /*nothing*/
    }
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) &&(INTERRUPT_OCCUR==INTCONbits.RBIF)&&
            (PORTBbits.RB4==GPIO_high)&& (RB4_flag ==1)){
        RB4_flag =0;
        RB4_ISR(0);
    }else{
        /*nothing*/
    }
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) &&(INTERRUPT_OCCUR==INTCONbits.RBIF)&&
            (PORTBbits.RB4==GPIO_low) && (RB4_flag ==0) ){
        RB4_flag =1;
        RB4_ISR(1);
    }else{
        /*nothing*/
    }
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) &&(INTERRUPT_OCCUR==INTCONbits.RBIF)&&
            (PORTBbits.RB5==GPIO_high)&& (RB5_flag ==1)){
            RB5_flag =0;
        RB5_ISR(0);
    }else{
        /*nothing*/
    }
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) &&(INTERRUPT_OCCUR==INTCONbits.RBIF)&&
            (PORTBbits.RB5==GPIO_low)&& (RB5_flag ==0) ){
        RB5_flag =1;
        RB5_ISR(1);
    }else{
        /*nothing*/
    }
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) &&(INTERRUPT_OCCUR==INTCONbits.RBIF)&&
            (PORTBbits.RB6==GPIO_high)&& (RB6_flag ==1)){
        RB6_flag =0;
        RB6_ISR(0);
    }else{
        /*nothing*/
    }
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) &&(INTERRUPT_OCCUR==INTCONbits.RBIF)&&
            (PORTBbits.RB6==GPIO_low)&& (RB6_flag ==0) ){
         RB6_flag =1;
        RB6_ISR(1);
    }else{
        /*nothing*/
    }
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) &&(INTERRUPT_OCCUR==INTCONbits.RBIF)&&
            (PORTBbits.RB7==GPIO_high)&& (RB7_flag ==1)){
         RB7_flag =0;
        RB7_ISR(0);
    }else{
        /*nothing*/
    }
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) &&(INTERRUPT_OCCUR==INTCONbits.RBIF)&&
            (PORTBbits.RB7==GPIO_low)&& (RB7_flag ==0) ){
         RB7_flag =1;
        RB7_ISR(1);
    }else{
        /*nothing*/
    }
    if ((INTERRUPT_ENABLE == PIE1bits.ADIE) &&(INTERRUPT_OCCUR == PIR1bits.ADIF)) {
        ADC_ISR();
    } else {
        /*nothing*/
    } 
    if ((INTERRUPT_ENABLE == INTCONbits.TMR0IE) &&(INTERRUPT_OCCUR == INTCONbits.TMR0IF)) {
        TMR0_ISR();
    } else {
        /*nothing*/
    } 
    
     if ((INTERRUPT_ENABLE == PIE1bits.TMR1IE) &&(INTERRUPT_OCCUR == PIR1bits.TMR1IF)) {
        TMR1_ISR();
    } else {
        /*nothing*/
    } 
    
    if ((INTERRUPT_ENABLE == PIE1bits.TMR2IE) &&(INTERRUPT_OCCUR == PIR1bits.TMR2IF)) {
        TMR2_ISR();
    } else {
        /*nothing*/
    } 
    
    if ((INTERRUPT_ENABLE == PIE2bits.TMR3IE) &&(INTERRUPT_OCCUR == PIR2bits.TMR3IF)) {
        TMR3_ISR();
    } else {
        /*nothing*/
    } 
    
    if ((INTERRUPT_ENABLE == PIE1bits.CCP1IE) &&(INTERRUPT_OCCUR == PIR1bits.CCP1IF)) {
        CCP1_ISR();
    } else {
        /*nothing*/
    } 
    if ((INTERRUPT_ENABLE == PIE2bits.CCP2IE) &&(INTERRUPT_OCCUR == PIR2bits.CCP2IF)) {
        CCP2_ISR();
    } else {
        /*nothing*/
    } 
    if ((INTERRUPT_ENABLE == PIE1bits.TXIE) &&(INTERRUPT_OCCUR == PIR1bits.TXIF)) {
        ESURT_TX_ISR();
    } else {
        /*nothing*/
    } 
    if ((INTERRUPT_ENABLE == PIE1bits.RCIE) &&(INTERRUPT_OCCUR == PIR1bits.RCIF)) {
        ESURT_RX_ISR();
    } else {
        /*nothing*/
    } 
    if ((INTERRUPT_ENABLE == PIE1bits.SSPIE) &&(INTERRUPT_OCCUR == PIR1bits.SSPIF)) {
        MSSP_I2C_ISR();
    } else {
        /*nothing*/
    } 
    if ((INTERRUPT_ENABLE == PIE2bits.BCLIE) &&(INTERRUPT_OCCUR == PIR2bits.BCLIF)) {
        MSSP_I2C_BC_ISR();
    } else {
        /*nothing*/
    } 

}

#endif