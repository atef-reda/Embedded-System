/*
 * File:   ecu_chr_lcd.h
 * Author: Home?
 *
 * Created on October 1, 2023, 9:00 PM
 */

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H
/*...................include.......*/
#include "ecu_chr_lcd_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "string.h"
#include "../../MCAL_layer/mcal_std_types.h"
/*...........macro declaration.............*/
#define _LCD_CLEAR                   0X01/*This command will remove data displaying on the screen of LCD*/
#define _LCD_RETURN_HOME             0X02/*It used to move return home*/
#define _LCD_ENTRY_MODE               0X06/* It is used to change the cursor location to the right side*/

#define _LCD_CURSOR_OFF_DISPLAY_ON   0X0C/* It is used to turn OFF the cursor & turn ON the display*/
#define _LCD_CURSOR_OFF_DISPLAY_OFF  0X08/* It is used to turn off the display & the cursor will be turned off*/
#define _LCD_CURSOR_ON_BLINK_ON      0X0F/*It is used to turn ON display & blink the cursor*/
#define _LCD_CURSOR_ON_BLINK_ON      0X0E/* It is used to turn ON the display & blink the cursor*/

#define _LCD_DISPLAY_SHIFT_RIGHT       0X1C /* It changes the display location to the left side*/   
/*It changes the display location to the right side*/
#define _LCD_DISPLAY_SHIFT_LEFT        0X18

#define _LCD_8BIT_MODE_2_LINE        0X38/*lines & 5?7 matrix*/
#define _LCD_4BIT_MODE_2_LINE        0X28/**/
#define _LCD_CGRAM_START             0X40/**/
#define _LCD_DDRAM_START             0X80/*It is used to shift the cursor to the primary line*/

#define ROW1    1
#define ROW2    2
#define ROW3    3
#define ROW4    4




/*............macro function declaration............*/

/*................data type declaration..........*/

typedef struct {
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}chr_lcd_4bit_t;

typedef struct {
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}chr_lcd_8bit_t;

/*........software interface declaration.......*/
Std_ReturnType lcd_4bit_init(const chr_lcd_4bit_t *lcd);
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd,uint8 command);
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd,uint8 data);
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd,uint8 row ,uint8 column ,uint8 data);
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd,uint8 *str);
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd,uint8 row ,uint8 column,uint8 *str);
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,
                                          const uint8 _chr[],uint8 mem_pos);


Std_ReturnType lcd_8bit_init(const chr_lcd_8bit_t *lcd);
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd,uint8 command);
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd,uint8 data);
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd,uint8 row ,uint8 column ,uint8 data);
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd,uint8 *str);
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd,uint8 row ,uint8 column,uint8 *str);
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd,uint8 row ,uint8 column,
                                                   const uint8 _chr[],uint8 mem_pos);

Std_ReturnType convert_byte_to_string(uint8 value ,uint8 *str);
Std_ReturnType convert_short_to_string(uint16 value ,uint8 *str);
Std_ReturnType convert_int_to_string(uint32 value ,uint8 *str);
#endif	/* ECU_CHR_LCD_H */

