/* 
 * File:   ecu_Led.
 * Author: Home?
 *
 * Created on July 28, 2023, 11:43 PM
 */
#include "ecu_Led.h"
/**
 * @breif 
 * @param led : pointer to the led module configuration 
 * @return 
 */
    Std_ReturnType led_initilaize(const led_t *led){
    Std_ReturnType ret =E_NOK;
    if(NULL == led){
        ret = E_NOK ;
    }
    else{
        pin_config_t pin_obj ={.port=led->port ,.pin =led->pin,
            .direction= GPIO_DIRECTION_output,.logic =led->led_status

        };
       gpio_pin_initialize(&pin_obj);

    }
    
    return ret ;
}
/**
 * @breif turn the led on 
 * @param led : pointer to the led module configuration 
 * @return 
 */
Std_ReturnType led_turn_on(const led_t *led){
    Std_ReturnType ret =E_OK;
    if(NULL == led){
        ret = E_NOK ;
    }
    else{
         pin_config_t pin_obj ={.port=led->port ,.pin =led->pin,
            .direction= GPIO_DIRECTION_output,.logic =led->led_status
        };
                    gpio_pin_write_logic(&pin_obj,GPIO_high);
 
    }
    return ret ;
    
}
/**
 * @breif turn the led off 
 * @param led : pointer to the led module configuration 
 * @return 
 */
Std_ReturnType led_turn_off(const led_t *led){
    Std_ReturnType ret =E_OK;
    if(NULL == led){
        ret = E_NOK ;
        
    }
    else{
         pin_config_t pin_obj ={.port=led->port ,.pin =led->pin,
            .direction= GPIO_DIRECTION_output,.logic =led->led_status
                    

        };
          gpio_pin_write_logic(&pin_obj,GPIO_low);
    }
    return ret ;
    
}
/**
 * @breif toggle the led 
 * @param led : pointer to the led module configuration 
 * @return 
 */
Std_ReturnType led_turn_toggle(const led_t *led ){
    Std_ReturnType ret =E_OK;
    if(NULL == led){
        ret = E_NOK ;
    }
    else{
        pin_config_t pin_obj ={.port=led->port ,.pin =led->pin,
            .direction= GPIO_DIRECTION_output,.logic =led->led_status
             
        };
        gpio_pin_toggle_logic(&pin_obj);
        
        
    }
    return ret ;
    
}