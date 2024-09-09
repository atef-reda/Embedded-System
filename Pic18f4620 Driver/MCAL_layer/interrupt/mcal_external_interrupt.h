/* 
 * File:   mcal_external_interrupt.h
 * Author: Home?
 *
 * Created on September 7, 2023, 11:40 AM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H
/*..............includes.............*/
#include "mcal_interrupt_config.h"
/*...............macro declarations........*/
#if INTERRUPT_Priority_INTX_Levels_Enable ==  INTERRUPT_feature_ENABLE 
/*this routine clears the interrupt enable for the external interrupt,INT0 */
#define EXT_INT0_interruptDisable()  (INTCONbits.INT0IE=0)
/*this routine sets the interrupt enable for the external interrupt,INT0*/
#define EXT_INT0_interruptEnable()  (INTCONbits.INT0IE=1)
/*this routine clears the interrupt flag for the external interrupt,INT0  */
#define EXT_INT0_interruptflag_clear()  (INTCONbits.INT0IF=0)
/*this routine set the edge detect  of th external interrupt to negative edge */
#define EXT_INT0_RisingEdgeset()         (INTCON2bits.INTEDG0=1)
/* this routine set the edge detect of the external interrupt to the positive edge */
#define EXT_INT0_FallingEdgeset()          (INTCON2bits.INTEDG0=0)

/*this routine clears the interrupt enable for the external interrupt,INT1 */
#define EXT_INT1_interruptDisable()  (INTCON3bits.INT1IE=0)
/*this routine sets the interrupt enable for the external interrupt,INT1*/
#define EXT_INT1_interruptEnable()  (INTCON3bits.INT1IE=1)
/*this routine clears the interrupt flag for the external interrupt,INT1 */
#define EXT_INT1_interruptflag_clear()  (INTCON3bits.INT1IF=0)
/*this routine set the edge detect  of th external interrupt to negative edge */
#define EXT_INT1_RisingEdgeset()        (INTCON2bits.INTEDG1=1)
/* this routine set the edge detect of the external interrupt to the positive edge */
#define EXT_INT1_FallingEdgeset()          (INTCON2bits.INTEDG1=0)


/*this routine clears the interrupt enable for the external interrupt,INT2 */
#define EXT_INT2_interruptDisable() (INTCON3bits.INT2IE=0)
/*this routine sets the interrupt enable for the external interrupt,INT2*/
#define EXT_INT2_interruptEnable()  (INTCON3bits.INT2IE=1)
/*this routine clears the interrupt flag for the external interrupt,INT2  */
#define EXT_INT2_interruptflag_clear()  (INTCON3bits.INT2IF=0)
/*this routine set the edge detect  of th external interrupt to negative edge */
#define EXT_INT2_RisingEdgeset()           (INTCON2bits.INTEDG2=1)
/* this routine set the edge detect of the external interrupt to the positive edge */
#define EXT_INT2_FallingEdgeset()           (INTCON2bits.INTEDG2=0)

#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
/*this routine set the INT1 External interrupt priority to be high priority*/
#define EXT_INT1_highpriorityset()           (INTCON3bits.INT1IP=1)
/*this routine set the INT1 External interrupt priority to be low priority*/
#define EXT_INT1_lowpriorityset()             (INTCON3bits.INT1IP=0)
/*this routine set the INT2 External interrupt priority to be high priority*/
#define EXT_INT2_highpriorityset()           (INTCON3bits.INT2IP=1)
/*this routine set the INT2 External interrupt priority to be low priority*/
#define EXT_INT2_lowpriorityset()           (INTCON3bits.INT2IP=0)


#endif 

#endif
#if EXTERNAL_INTERRUPT_onchange_FEATURE_Enable == INTERRUPT_feature_ENABLE 

/*this routine clears the interrupt enable for the external interrupt,RBX */
#define EXT_RBx_interruptDisable() (INTCONbits.RBIE=0)
/*this routine sets the interrupt enable for the external interrupt,RBX*/
#define EXT_RBx_interruptEnable()  (INTCONbits.RBIE=1)
/*this routine clears the interrupt flag for the external interrupt,RBX  */
#define EXT_RBx_interruptflag_clear()  (INTCONbits.RBIF=0)

#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
/*this routine set the RBx External interrupt priority to be high priority*/
#define EXT_RBx_highpriorityset()           (INTCON2bits.RBIP=1)
/*this routine set the RBx External interrupt priority to be low priority*/
#define EXT_RBx_lowpriorityset()           (INTCON2bits.RBIP=0)
#endif

#endif
/*...............macro function declarations......*/

/*...............data type declarations......*/
typedef enum {
    interrupt_falling_edge = 0,
    interrupt_rising_edge
} interrupt_INTX_edge;

typedef enum {
    interrupt_External_INT0 = 0,
    interrupt_External_INT1,
    interrupt_External_INT2
} interrupt_INTX_scr;

typedef struct{
    void (* EXT_InterruptHandler)(void);
        pin_config_t mcu_pin;
        interrupt_INTX_edge edge;
        interrupt_INTX_scr source  ;
        interrupt_priority_cfg priority ;
}interrupt_INTX_t;

typedef struct {
    void (* EXT_InterruptHandler_high)(void);
    void (* EXT_InterruptHandler_low)(void);
    pin_config_t mcu_pin;
    interrupt_priority_cfg priority;
} interrupt_RBx_t;
/*................software interfaces declarations........*/
Std_ReturnType Interrupt_INTX_init(const interrupt_INTX_t *int_obj); 
Std_ReturnType Interrupt_INTX_DeInit(const interrupt_INTX_t *int_obj); 
Std_ReturnType Interrupt_RBX_Init(const interrupt_RBx_t *int_obj); 
Std_ReturnType Interrupt_RBX_DeInit(const interrupt_RBx_t *int_obj); 

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

