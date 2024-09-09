/* 
 * File:   ecu_button.c
 * Author: Home?
 *
 * Created on August 9, 2023, 4:43 PM
 */
#include "ecu_button.h"
/**
 * 
 * @param btn
 * @return 
 */
Std_ReturnType BUTTON_initialize(const button_t *btn){
    Std_ReturnType ret =E_NOK;
    if(NULL== btn){
        ret=E_NOK;
    }
    else{
      ret =  gpio_pin_direction_intialize(&btn->button_pin);
    }
    return ret ;
}
/**
 * 
 * @param btn
 * @param btn_state
 * @return 
 */
Std_ReturnType button_read_state(const button_t *btn ,button_state_t *btn_state){
     Std_ReturnType ret =E_NOK;
     logic_t pin_logic_status =  GPIO_low;

    if((NULL== btn)||(NULL ==btn_state)){
        ret=E_NOK;
    }
    else{
        gpio_pin_read_logic(&(btn->button_pin),&pin_logic_status);
        if(button_active_high== btn->button_connection){
            if(GPIO_high==pin_logic_status){
               *btn_state =  button_pressed;
            }else{
                *btn_state = button_released ;
            }
        }else if(button_active_low== btn->button_connection){
            if(GPIO_high==pin_logic_status){
                *btn_state = button_released;
            }else{
                *btn_state =  button_pressed;
            }
            
        }else{/*nothing */}
        ret =E_OK;
    }
    return ret ;
}