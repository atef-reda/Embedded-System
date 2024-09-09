/* 
 * File:   ecu_7_seg.h
 * Author: redaa
 *
 * Created on September 16, 2023, 4:06 PM
 */

#ifndef ECU_7SEG_H
#define	ECU_7SEG_H
/*__ _ _ __  __ _ __ _ __includes _ _ _ _ _ __ _ _ _ _ _ _*/
#include "ecu_7_seg_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
/*__ _ _ __  __ _ __ _ __macro declaration _ _ _ _ _ __ _ _ _ _ _ _*/

/*__ _ _ __  __ _ __ _ __ _ data type declaration_ _ _ _ __ _ _ _ _ _ _*/
typedef enum{
    segment_common_anode,
    segment_common_cathode
}segment_type_t;
typedef struct{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;
/*__ _ _ __  __ _ __ _ __ _ software interfaces declarations  _ _ _ __ _ _ _ _ _ _*/
Std_ReturnType seven_segment_intialize(const segment_t *seg);
Std_ReturnType seven_segment_write_number(const segment_t *seg,uint8 number);

#endif	/* ECU_7_SEG_H */

