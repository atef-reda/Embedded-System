#include "ecu_relay_h.h"
/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType relay_initialize(const relay_t *relay ){
    Std_ReturnType ret =E_OK;
    if( NULL == relay ){
        ret = E_NOK;
    }else{
        pin_config_t pin_obj ={
            .port = relay ->relay_port,
            .pin = relay->relay_pin,
            .direction =  GPIO_DIRECTION_output,
           .logic = relay->relay_status
        };
        gpio_pin_initialize(&pin_obj);
    }
    return ret;
}
/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType relay_turn_on(const relay_t *relay){ 
    Std_ReturnType ret =E_OK;
    if( NULL == relay ){
        ret = E_NOK;
    }else{
        pin_config_t pin_obj ={
            .port = relay ->relay_port,
            .pin = relay->relay_pin,
            .direction =  GPIO_DIRECTION_output,
           .logic = relay->relay_status
        };
        gpio_pin_write_logic(&pin_obj, GPIO_high);
        
    }
    return ret;
    
}
/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType relay_turn_off(const relay_t *relay){
     Std_ReturnType ret =E_OK;
    if( NULL == relay ){
        ret = E_NOK;
    }else{
         pin_config_t pin_obj ={
            .port = relay ->relay_port,
            .pin = relay->relay_pin,
            .direction =  GPIO_DIRECTION_output,
           .logic = relay->relay_status
        };
        gpio_pin_write_logic(&pin_obj, GPIO_low);
        
    }
    return ret;
}