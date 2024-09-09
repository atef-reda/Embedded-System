#include "ecu_dc_motor.h"

Std_ReturnType dc_motor_initilaize (const dc_motor_t *dc_motor ){
    Std_ReturnType ret =E_OK;
    if(NULL ==dc_motor){
        ret =E_NOK;
    }else{
       
        
        
          gpio_pin_initialize(&dc_motor->dc_motor[0]);
           gpio_pin_initialize(&dc_motor->dc_motor[1]);      
    }
    return ret;
    
}
Std_ReturnType dc_motor_move_right(const dc_motor_t *dc_motor ){
     Std_ReturnType ret =E_OK;
    if(NULL ==dc_motor){
        ret =E_NOK;
    }else{
        gpio_pin_write_logic(&dc_motor->dc_motor[0],GPIO_high);
        gpio_pin_write_logic(&dc_motor->dc_motor[1],GPIO_low);
    }
    return ret;
}
Std_ReturnType dc_motor_move_left(const dc_motor_t *dc_motor ){
     Std_ReturnType ret =E_OK;
    if(NULL ==dc_motor){
        ret =E_NOK;
    }else{
         gpio_pin_write_logic(&dc_motor->dc_motor[0],GPIO_low);
        gpio_pin_write_logic(&dc_motor->dc_motor[1],GPIO_high);
        
    }
    return ret;
}
Std_ReturnType dc_motor_stop(const dc_motor_t *dc_motor ){
     Std_ReturnType ret =E_OK;
    if(NULL ==dc_motor){
        ret =E_NOK;
    }else{
        
          gpio_pin_write_logic(&dc_motor->dc_motor[0],GPIO_low);
        gpio_pin_write_logic(&dc_motor->dc_motor[1],GPIO_low);
    }
    return ret;
}
