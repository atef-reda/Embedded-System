/* 
 * File:   mcal_external_interrupt.c
 * Author: Home?
 *
 * Created on September 7, 2023, 11:40 AM
 */
#include "mcal_external_interrupt.h"
static interrupt_handler_fun INT0_interrupt_handler=NULL;
static interrupt_handler_fun INT1_interrupt_handler=NULL;
static interrupt_handler_fun INT2_interrupt_handler=NULL;

static interrupt_handler_fun RB4_interrupt_handler_high=NULL;
static interrupt_handler_fun RB4_interrupt_handler_low=NULL;

static interrupt_handler_fun RB5_interrupt_handler_high=NULL;
static interrupt_handler_fun RB5_interrupt_handler_low=NULL;

static interrupt_handler_fun RB6_interrupt_handler_high=NULL;
static interrupt_handler_fun RB6_interrupt_handler_low=NULL;

static interrupt_handler_fun RB7_interrupt_handler_high=NULL;
static interrupt_handler_fun RB7_interrupt_handler_low=NULL;

static Std_ReturnType interrupt_INTx_enable(const interrupt_INTX_t *int_obj);
static Std_ReturnType interrupt_INIx_Disable(const interrupt_INTX_t *int_obj);
static Std_ReturnType interrupt_INTx_priority_init(const interrupt_INTX_t *int_obj);
static Std_ReturnType interrupt_INIx_Edge_init(const interrupt_INTX_t *int_obj);
static Std_ReturnType interrupt_INIx_pin_init(const interrupt_INTX_t *int_obj);
static Std_ReturnType interrupt_INIx_clear_flag(const interrupt_INTX_t *int_obj);

static Std_ReturnType INT0_SetInterruptHandler(void(*INT0_interrupt_handler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void(*INT1_interrupt_handler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void(*INT2_interrupt_handler)(void));
static Std_ReturnType interrupt_INIx_SetInterruptHandler(const interrupt_INTX_t *int_obj);

static Std_ReturnType interrupt_RBx_enable(const interrupt_RBx_t *int_obj);
static Std_ReturnType interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType interrupt_RBx_priority_init(const interrupt_RBx_t *int_obj);
static Std_ReturnType interrupt_RBx_pin_init(const interrupt_RBx_t *int_obj);
/**
 * 
 * @param int_obj
 * @return 
 */
    Std_ReturnType Interrupt_INTX_init(const interrupt_INTX_t *int_obj){
    Std_ReturnType ret =E_NOK;
    if(NULL == int_obj){
        ret =E_NOK;
    }else{
        /*disable the external interrupt */
        ret =interrupt_INIx_Disable(int_obj);
        /*clear interrupt flag : external interrupt did not occur*/
        ret =interrupt_INIx_clear_flag(int_obj);
        /*configure external interrupt edge */
        ret =interrupt_INIx_Edge_init(int_obj);
#if INTERRUPT_Priority_Levels_Enable ==INTERRUPT_feature_ENABLE  

         /*configure external interrupt priority */
        ret =interrupt_INTx_priority_init(int_obj);
#endif
        /*configure external interrupt I/O pin */
        ret =interrupt_INIx_pin_init(int_obj);
        /*configure external interrupt callback */
        ret =interrupt_INIx_SetInterruptHandler(int_obj);
        
        /*enable the external interrupt*/
        ret = interrupt_INTx_enable(int_obj);
    }
    return ret;
    
}
void INT0_ISR(void){
    /*the INT0 external interrupt  occurred(must be cleared in software)*/
    EXT_INT0_interruptflag_clear();
    /* code */
    
    /*callback function gets  called every  time this ISR executes*/
    if(INT0_interrupt_handler){INT0_interrupt_handler();}
}
void INT1_ISR(void){
    /*the INT1 external interrupt  occurred(must be cleared in software)*/
    EXT_INT1_interruptflag_clear();
    /* code */
    
    /*callback function gets  called every  time this ISR executes*/
    if(INT1_interrupt_handler){INT1_interrupt_handler();}
}
void INT2_ISR(void){
    /*the INT2 external interrupt  occurred(must be cleared in software)*/
    EXT_INT2_interruptflag_clear();
    /* code */
    
    /*callback function gets  called every  time this ISR executes*/
    if(INT2_interrupt_handler){INT2_interrupt_handler();}
}
void RB4_ISR(uint8 RB4_source){
  /*the RB4 external interrupt  occurred(must be cleared in software)*/
        EXT_RBx_interruptflag_clear();
        /* code */
    
    /*callback function gets  called every  time this ISR executes*/
        if(0==RB4_source){
            if(RB4_interrupt_handler_high){RB4_interrupt_handler_high();}
    else{
        /*nothing*/
         }
        }else if (1==RB4_source){
            if(RB4_interrupt_handler_low){RB4_interrupt_handler_low();}
    else{
        /*nothing*/
    }
            
        }else{
            /*nothing*/
        }
    
}
void RB5_ISR(uint8 RB5_source){
  /*the RB4 external interrupt  occurred(must be cleared in software)*/
        EXT_RBx_interruptflag_clear();
        /* code */
    
    /*callback function gets  called every  time this ISR executes*/
        if(0==RB5_source){
            if(RB5_interrupt_handler_high){RB5_interrupt_handler_high();}
    else{
        /*nothing*/
         }
        }else if (1==RB5_source){
            if(RB5_interrupt_handler_low){RB5_interrupt_handler_low();}
    else{
        /*nothing*/
    }
            
        }else{
            /*nothing*/
        }
   
}
void RB6_ISR(uint8 RB6_source){
  /*the RB4 external interrupt  occurred(must be cleared in software)*/
        EXT_RBx_interruptflag_clear();
        /* code */
    
    /*callback function gets  called every  time this ISR executes*/
        if(0==RB6_source){
            if(RB6_interrupt_handler_high){RB6_interrupt_handler_high();}
    else{
        /*nothing*/
         }
        }else if (1==RB6_source){
            if(RB6_interrupt_handler_low){RB6_interrupt_handler_low();}
    else{
        /*nothing*/
    }
            
        }else{
            /*nothing*/
        }
   
}
void RB7_ISR(uint8 RB7_source){
  /*the RB4 external interrupt  occurred(must be cleared in software)*/
        EXT_RBx_interruptflag_clear();
        /* code */
    
    /*callback function gets  called every  time this ISR executes*/
        if(0==RB7_source){
            if(RB7_interrupt_handler_high){RB7_interrupt_handler_high();}
    else{
        /*nothing*/
         }
        }else if (1==RB7_source){
            if(RB7_interrupt_handler_low){RB7_interrupt_handler_low();}
    else{
        /*nothing*/
    }
            
        }else{
            /*nothing*/
        }
   
}
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTX_DeInit(const interrupt_INTX_t *int_obj){
    Std_ReturnType ret =E_NOK;
    if(NULL == int_obj){
        ret =E_NOK;
    }else{
        ret =interrupt_INIx_Disable(int_obj);
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType interrupt_RBx_enable(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret =E_OK;
    if(NULL == int_obj){
        ret =E_NOK;
    }else{
        EXT_RBx_interruptEnable();
        #if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
        INTERRUPT_priorityLevelsEnable();
        if(interrupt_low_priority==int_obj->priority){
            /*this macro will enable low priority global interrupts*/
            INTERRUPT_GlobalInterruptlowEnable();
    /*this routine set the RBx External interrupt priority to be low priority*/
               EXT_RBx_lowpriorityset();

        }
        else if (Interrupt_high_priority==int_obj->priority){
            /*this macro will enable high priority global interrupts*/
            INTERRUPT_GlobalInterruptHighEnable();
/*this routine set the RBx External interrupt priority to be high priority*/
                        EXT_RBx_highpriorityset();

        }
        else{/*nothing*/}
#else 
         INTERRUPT_GlobalInterruptEnable();
         INTERRUPT_PeripheralInterruptEnable();
#endif  
    }
    return ret;
}
static Std_ReturnType interrupt_RBx_Disable(const interrupt_RBx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        EXT_RBx_interruptDisable();
        EXT_RBx_interruptflag_clear();
    }
    return ret;
}
#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
static Std_ReturnType interrupt_RBx_priority_init(const interrupt_RBx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        if (interrupt_low_priority == int_obj->priority) {
            /*this routine set the RBx External interrupt priority to be low priority*/
            EXT_RBx_lowpriorityset();

        } else if (Interrupt_high_priority == int_obj->priority) {

            /*this routine set the RBx External interrupt priority to be high priority*/
            EXT_RBx_highpriorityset();
        } else {
            /*nothing*/
        }
/*nothing*/
}
return ret;
}
#endif  

static Std_ReturnType interrupt_RBx_pin_init(const interrupt_RBx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    return ret;
}
static Std_ReturnType interrupt_RBx_set_InterruptHandler(const interrupt_RBx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        switch (int_obj->mcu_pin.pin) {
            case GPIO_PIN4:
                RB4_interrupt_handler_high = int_obj->EXT_InterruptHandler_high;
                RB4_interrupt_handler_low = int_obj->EXT_InterruptHandler_low;
                break;
            case GPIO_PIN5:
                RB5_interrupt_handler_high = int_obj->EXT_InterruptHandler_high;
                RB5_interrupt_handler_low = int_obj->EXT_InterruptHandler_low;
                break;
            case GPIO_PIN6:
                RB6_interrupt_handler_high = int_obj->EXT_InterruptHandler_high;
                RB6_interrupt_handler_low = int_obj->EXT_InterruptHandler_low;
                break;
            case GPIO_PIN7:
                RB7_interrupt_handler_high = int_obj->EXT_InterruptHandler_high;
                RB7_interrupt_handler_low = int_obj->EXT_InterruptHandler_low;
                break;
            default:
                ret = E_NOK;
        }
    }
    return ret;
}
Std_ReturnType Interrupt_RBX_Init(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret =E_OK;
    if(NULL == int_obj){
        ret =E_NOK;
    }else{
        /*this routine clears the interrupt disable and flag  for the external interrupt,RBX*/
        ret=interrupt_RBx_Disable(int_obj);
        /*initialize the RBX to be input*/
        ret|=interrupt_RBx_pin_init(int_obj);
        /*initialize the call back function*/
        ret|=interrupt_RBx_set_InterruptHandler(int_obj);
#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
        interrupt_RBx_priority_init(int_obj);
#endif

        /*this routine sets the interrupt enable  for the external interrupt,RBX*/
        ret|=interrupt_RBx_enable(int_obj);

    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBX_DeInit(const interrupt_RBx_t *int_obj) {
    Std_ReturnType ret = E_NOK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        /*this routine clears the interrupt disable  for the external interrupt,RBX*/
        EXT_RBx_interruptDisable();
        /*this routine clears the interrupt flag  for the external interrupt,RBX*/
        EXT_RBx_interruptflag_clear();
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType interrupt_INTx_enable(const interrupt_INTX_t *int_obj) {
    Std_ReturnType ret = E_NOK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        switch (int_obj->source) {
            case interrupt_External_INT0:
#if INTERRUPT_Priority_Levels_Enable ==INTERRUPT_feature_ENABLE 
                INTERRUPT_GlobalInterruptHighEnable();
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif

                EXT_INT0_interruptEnable();
                ret = E_OK;
                break;
                
            case interrupt_External_INT1:
#if INTERRUPT_Priority_Levels_Enable ==INTERRUPT_feature_ENABLE 
                INTERRUPT_priorityLevelsEnable();

                if (interrupt_low_priority == int_obj->priority) {
                    INTERRUPT_GlobalInterruptlowEnable();
                } else if (Interrupt_high_priority == int_obj->priority) {
                    INTERRUPT_GlobalInterruptHighEnable();
                } else {
                    /*nothing*/
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT1_interruptEnable();
                ret = E_OK;
                break;
            case interrupt_External_INT2:
                
#if INTERRUPT_Priority_Levels_Enable ==INTERRUPT_feature_ENABLE
                INTERRUPT_priorityLevelsEnable();
                if (interrupt_low_priority == int_obj->priority) {
                    INTERRUPT_GlobalInterruptlowEnable();
                } else if (Interrupt_high_priority == int_obj->priority) {
                    INTERRUPT_GlobalInterruptHighEnable();
                } else {
                    /*nothing*/
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT2_interruptEnable();
                ret = E_OK;
                break;
            default: ret = E_NOK;
        }

    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType interrupt_INIx_Disable(const interrupt_INTX_t *int_obj){
     Std_ReturnType ret =E_NOK;
    if(NULL == int_obj){
        ret =E_NOK;
    }else{
        switch(int_obj->source){
            case interrupt_External_INT0 :
                EXT_INT0_interruptDisable();
                ret =E_OK;
                break;
            case interrupt_External_INT1 :
               EXT_INT1_interruptDisable();
                ret= E_OK;
                break ;
            case interrupt_External_INT2 :
                EXT_INT2_interruptDisable();
                ret= E_OK;
                break ;
                 default: ret =E_NOK;
        }
        
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
static Std_ReturnType interrupt_INTx_priority_init(const interrupt_INTX_t *int_obj){
     Std_ReturnType ret =E_NOK;
    if(NULL == int_obj){
        ret =E_NOK;
    }else{
        switch(int_obj->source){
            
            case interrupt_External_INT1 :
                if(interrupt_low_priority==int_obj->priority){EXT_INT1_lowpriorityset();}
                else if(Interrupt_high_priority==int_obj->priority){EXT_INT1_highpriorityset();}
                else{/*nothing*/}
                ret = E_OK;
                break ;
            case interrupt_External_INT2 :
                 if(interrupt_low_priority==int_obj->priority){EXT_INT2_lowpriorityset();}
                else if(Interrupt_high_priority==(int_obj->priority)){EXT_INT2_highpriorityset();}
                else{/*nothing*/}
                ret = E_OK;
                break ;
                 default: ret =E_NOK;
        }
        
    }
    return ret;
}
#endif
/**
 * 
 * @param int_obj
 * @return 
 */

static Std_ReturnType interrupt_INIx_Edge_init(const interrupt_INTX_t *int_obj){
     Std_ReturnType ret =E_NOK;
    
        switch(int_obj->source){
            case interrupt_External_INT0 :
                if(interrupt_falling_edge==int_obj->edge){EXT_INT0_FallingEdgeset();}
                else if(interrupt_rising_edge==int_obj->edge){EXT_INT0_RisingEdgeset();}
                else{/*nothing*/}
                ret = E_OK;
                break;
            case interrupt_External_INT1 :
               if(interrupt_falling_edge==int_obj->edge){EXT_INT1_FallingEdgeset();}
                else if(interrupt_rising_edge==int_obj->edge){EXT_INT1_RisingEdgeset();}
                else{/*nothing*/}
                ret =E_OK;
                break ;
            case interrupt_External_INT2 :
                if(interrupt_falling_edge==int_obj->edge){EXT_INT2_FallingEdgeset();}
                else if(interrupt_rising_edge==int_obj->edge){EXT_INT2_RisingEdgeset();}
                else{/*nothing*/}
                ret = E_OK;
                break ;
                 default: ret =E_NOK;
        
        
    }
    return ret;
}
  /**
   * 
   * @param int_obj
   * @return 
   */  

static Std_ReturnType interrupt_INIx_pin_init(const interrupt_INTX_t *int_obj){
     Std_ReturnType ret =E_NOK;
    if(NULL == int_obj){
        ret =E_NOK;
    }else{
        ret =gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    return ret;
}
static Std_ReturnType interrupt_INIx_clear_flag(const interrupt_INTX_t *int_obj){
     Std_ReturnType ret =E_NOK;
    if(NULL == int_obj){
        ret =E_NOK;
    }else{
         switch(int_obj->source){
            case interrupt_External_INT0 :
                EXT_INT0_interruptflag_clear();
                ret =E_OK;
                break;
            case interrupt_External_INT1 :
               EXT_INT1_interruptflag_clear();
                ret =E_OK;
                break;
            case interrupt_External_INT2 :
                EXT_INT2_interruptflag_clear();
                ret= E_OK;
                break;
            default: ret =E_NOK;
        }
        
    }
    return ret;
}
static Std_ReturnType INT0_SetInterruptHandler(void(*interrupt_handler)(void)){
    Std_ReturnType ret =E_NOK;
    if(NULL == interrupt_handler){
                ret =E_NOK;
    }else{
        INT0_interrupt_handler=interrupt_handler;
        ret=E_OK;
    }
    return ret;
}
static Std_ReturnType INT1_SetInterruptHandler(void(*interrupt_handler)(void)){
     Std_ReturnType ret =E_NOK;
    if(NULL == interrupt_handler){
                ret =E_NOK;
    }else{
        INT1_interrupt_handler=interrupt_handler;
        ret=E_OK;
    }
    return ret;
}
static Std_ReturnType INT2_SetInterruptHandler(void(*interrupt_handler)(void)){
     Std_ReturnType ret =E_NOK;
    if(NULL == interrupt_handler){
                ret =E_NOK;
    }else{
        INT2_interrupt_handler=interrupt_handler;
        ret=E_OK;
    }
    return ret;
}
static Std_ReturnType interrupt_INIx_SetInterruptHandler(const interrupt_INTX_t *int_obj){
    Std_ReturnType ret =E_NOK;
    if(NULL ==int_obj){
        ret = E_NOK;
    }else{
         switch(int_obj->source){
            case interrupt_External_INT0 :
                ret=INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case interrupt_External_INT1 :
             ret=INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);

                break;
            case interrupt_External_INT2 :
            ret=INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);

                break;
            default: ret =E_NOK;
        
         }
    }
    return ret;
}