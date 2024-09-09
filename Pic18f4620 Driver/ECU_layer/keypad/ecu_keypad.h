/* 
 * File:   ecu_keypad.h
 * Author: Home?
 *
 * Created on August 27, 2023, 10:58 AM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/*____________include_ _ _ __  __ _ _ _*/
#include "ecu_keypad_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
/*................macro declaration...................*/
#define ecu_keypad_row      4
#define ecu_keypad_columns  4
/*...................data type declaration............*/
typedef struct{
    pin_config_t keypad_row_pins[ecu_keypad_row];
    pin_config_t keypad_columns_pins[ecu_keypad_columns];
}keypad_t;
/*....................software interfaces declaration */
Std_ReturnType keypad_initialize( const keypad_t *keypad_object);
Std_ReturnType keypad_get_value( const keypad_t *keypad_object,uint8 *value);
#endif	/* ECU_KEYPAD_H */

