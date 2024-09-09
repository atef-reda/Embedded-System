/*
 * File:   application.c
 * Author: Home?
 *
 * Created on July 28, 2023, 10:13 PM
 */



#include <stdlib.h>
#include "ECU_layer/LCD/ecu_chr_lcd.h"
#include "ECU_layer/keypad/ecu_keypad.h"
void application_initialize(void);
chr_lcd_4bit_t lcd_object=
{
  .lcd_rs.direction=  GPIO_DIRECTION_output,
  .lcd_rs.logic=GPIO_low,
  .lcd_rs.port=PORTD_INDEX,
  .lcd_rs.pin=GPIO_PIN0,
  
  .lcd_en.direction=  GPIO_DIRECTION_output,
  .lcd_en.logic=GPIO_low,
  .lcd_en.port=PORTD_INDEX,
  .lcd_en.pin=GPIO_PIN1,
  
  .lcd_data[0].direction=  GPIO_DIRECTION_output,
  .lcd_data[0].logic=GPIO_low,
  .lcd_data[0].port=PORTD_INDEX,
  .lcd_data[0].pin=GPIO_PIN2,
  
  .lcd_data[1].direction=  GPIO_DIRECTION_output,
  .lcd_data[1].logic=GPIO_low,
  .lcd_data[1].port=PORTD_INDEX,
  .lcd_data[1].pin=GPIO_PIN3,
  
  .lcd_data[2].direction=  GPIO_DIRECTION_output,
  .lcd_data[2].logic=GPIO_low,
  .lcd_data[2].port=PORTD_INDEX,
  .lcd_data[2].pin=GPIO_PIN4,
  
  .lcd_data[3].direction=  GPIO_DIRECTION_output,
  .lcd_data[3].logic=GPIO_low,
  .lcd_data[3].port=PORTD_INDEX,
  .lcd_data[3].pin=GPIO_PIN5,
};


uint8 * welcome_massage="atef reda";
int main(){
    application_initialize();
    lcd_4bit_send_command(&lcd_object,_LCD_CLEAR);
    __delay_ms(10);
    lcd_4bit_send_string(&lcd_object,welcome_massage);

    while(1)
    {
        
    }
    return 0;
}

void application_initialize(void) {
    Std_ReturnType ret = E_NOK;
    lcd_4bit_init(&lcd_object);
}
