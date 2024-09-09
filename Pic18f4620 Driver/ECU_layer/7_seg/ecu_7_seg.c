/*
 * File:   ecu_7_seg.c
 * Author: redaa
 *
 * Created on September 16, 2023, 4:04 PM
 */


/**
 * 
 * @param seg
 * @return 
 */
#include "ecu_7_seg.h"
Std_ReturnType seven_segment_intialize(const segment_t *seg){
   Std_ReturnType ret =E_NOK;
   if(NULL == seg){
       ret =E_NOK;
   }else{
       ret =gpio_pin_initialize(&(seg->segment_pins[0]));
        ret =gpio_pin_initialize(&(seg->segment_pins[1]));
       ret =gpio_pin_initialize(&(seg->segment_pins[2]));
       ret =gpio_pin_initialize(&(seg->segment_pins[3]));

            
   }
   return ret;
}
Std_ReturnType seven_segment_write_number(const segment_t *seg,uint8 number){
    Std_ReturnType ret =E_NOK;
   if((NULL == seg)&&(number>9)){
       ret =E_NOK;
   }else{
      ret= gpio_pin_write_logic(&(seg->segment_pins[0]),number &0x01);
      ret= gpio_pin_write_logic(&(seg->segment_pins[1]),((number >>1)&0x01));
      ret= gpio_pin_write_logic(&(seg->segment_pins[2]),((number>>2)&0x01));
      ret= gpio_pin_write_logic(&(seg->segment_pins[3]),((number>>3)&0x01));

   }
   return ret;
}