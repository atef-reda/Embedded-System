/* 
 * File:   ecu_dc_motor.h
 * Author: Home?
 *
 * Created on August 25, 2023, 8:51 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H
/*_ _ _ _ _ _ _ _ _ _ includes_ _ _ __ _ _ _ _ _ _*/
#include "ecu_dc_motor_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
/*_ _ _ _ __ _ ________macro declarations________ _ _ _  _ _ _ _ _*/
#define dc_motor_on_Status 0x01U
#define dc_motor_off_Status 0x00U
/*_ _ __ __ _____ __ _ _ _ _  data type declarations_ _ _ __ _ __ __*/

typedef struct{
   pin_config_t dc_motor[2];
}dc_motor_t;
/*__________software interfaces declarations___________*/
Std_ReturnType dc_motor_initilaize (const dc_motor_t *dc_motor );
Std_ReturnType dc_motor_move_right(const dc_motor_t *dc_motor );
Std_ReturnType dc_motor_move_left(const dc_motor_t *dc_motor );
Std_ReturnType dc_motor_stop(const dc_motor_t *dc_motor );



#endif	/* ECU_DC_MOTOR_H */

