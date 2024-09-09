/* 
 * File:   ecu_button.h
 * Author: Home?
 *
 * Created on August 9, 2023, 4:43 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H
/*section:  includes*/
#include "ecu_button_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h" 
/*section : macro declaration*/

typedef enum{
    button_pressed,
      button_released      
}button_state_t;

typedef enum{
    button_active_high,
    button_active_low
}button_active_t;
typedef struct {
    pin_config_t button_pin;
    button_state_t button_state;
     button_active_t button_connection;
}button_t ;


/*_ _ _ _ _ _ _ _ _ _ _software interfaces declarations _ _ _ __ _ __ _ _ __ _ */
Std_ReturnType BUTTON_initialize(const button_t *btn);
Std_ReturnType button_read_state(const button_t *btn ,button_state_t *btn_state);

#endif	/* ECU_BUTTON_H */

