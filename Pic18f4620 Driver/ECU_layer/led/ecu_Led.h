/*
 * File:   ecu_Led.h
 * Author: Home?
 *
 * Created on July 28, 2023, 11:43 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H
/*section : includes */
#include "../../MCAL_layer/mcal_std_types.h"
#include "ecu_led_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
/*section :macro declarations */

/*section : macro functions declarations*/
/*section : data types declarations */
typedef enum {
    LED_OFF,
   LED_ON
}led_status;

typedef struct{
    uint8 port :4;
    uint8 pin:  3;
    uint8 led_status:1;

}led_t;
/*section : function declarations */
Std_ReturnType led_initilaize(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_turn_toggle(const led_t *led );

#endif	/* ECU_LED_H */

