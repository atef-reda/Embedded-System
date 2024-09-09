/* 
 * File:   ecu_relay_h.h
 * Author: Home?
 *
 * Created on August 25, 2023, 3:56 PM
 */

#ifndef ECU_RELAY_H_H
#define	ECU_RELAY_H_H
/*section:  includes*/
#include "ecu_relay_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h" 
/*section : macro declaration*/
#define relay_on_Status      0x01U
#define relay_off_Status     0x00U
/*___ _ _ _ _ _ _ _ _data type declaration */
typedef struct {
    uint8 relay_port :4;
    uint8 relay_pin :3;
    uint8 relay_status :1;
    
}relay_t;
/*_ __ __ _ _ _ _ _ _software interfaces declarations _ _ _ _ _ __ _ _ __*/
Std_ReturnType relay_initialize(const relay_t *relay );
Std_ReturnType relay_turn_on(const relay_t *relay);
Std_ReturnType relay_turn_off(const relay_t *relay);

#endif	/* ECU_RELAY_H_H */

