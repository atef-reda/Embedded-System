/*
 * File:   ecu_chr_lcd.c
 * Author: redaa
 *
 * Created on October 27, 2023, 7:32 AM
 */


#include "ecu_chr_lcd.h"
static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd,uint8 _data_command);
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd);
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd);
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd ,uint8 row ,uint8 column);
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd ,uint8 row ,uint8 column);


Std_ReturnType lcd_4bit_init(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret =E_NOK;
    uint8 l_data_pins_counter=0;
    if (lcd == NULL){
        ret = E_NOK;
    }else{
       ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret =gpio_pin_initialize(&(lcd->lcd_en));
        for(l_data_pins_counter=0;l_data_pins_counter<4;l_data_pins_counter++){
           ret = gpio_pin_initialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
        __delay_ms(20);
        ret =lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret =lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret =lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        ret =lcd_4bit_send_command(lcd,_LCD_CLEAR);
        ret =lcd_4bit_send_command(lcd,_LCD_RETURN_HOME);
        ret =lcd_4bit_send_command(lcd,_LCD_ENTRY_MODE);
        ret =lcd_4bit_send_command(lcd,_LCD_CURSOR_OFF_DISPLAY_ON);
        ret =lcd_4bit_send_command(lcd,_LCD_4BIT_MODE_2_LINE);
        ret =lcd_4bit_send_command(lcd,0x80);
        
    }
    return ret ;
}
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd,uint8 command){
    Std_ReturnType ret =E_NOK;
    if (lcd == NULL){
        ret = E_NOK;
    }else{
        /*write in RS 0 voltage */
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_low);
        /*send 4 high bits first */
        ret =lcd_send_4bits(lcd,command >>4);
        /*after any sending you have to set the enable*/
        ret =lcd_4bit_send_enable_signal(lcd);
                /*second send low bits */
         ret =lcd_send_4bits(lcd,command );
         /*after any sending you have to set the enable*/
        ret =lcd_4bit_send_enable_signal(lcd);
                
    }
    return ret ;
}
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd,uint8 data){
    Std_ReturnType ret =E_NOK;
    if (lcd == NULL){
        ret = E_NOK;
    }else{
        /*write in RS 5 voltage */
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_high);
        /*send 4 high bits first */
        ret =lcd_send_4bits(lcd,data >>4);
        /*after any sending you have to set the enable*/
        ret =lcd_4bit_send_enable_signal(lcd);
                /*second send low bits */
         ret =lcd_send_4bits(lcd,data );
         /*after any sending you have to set the enable*/
        ret =lcd_4bit_send_enable_signal(lcd);
    }
    return ret ;
}
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd,uint8 row ,uint8 column ,uint8 data){
    Std_ReturnType ret =E_NOK;
    if (lcd == NULL){
        ret = E_NOK;
    }else{
       ret = lcd_4bit_set_cursor(lcd,row,column);
       ret =lcd_4bit_send_char_data(lcd,data);
    }
    return ret ;
}
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd,uint8 *str){
    Std_ReturnType ret =E_NOK;
    if (lcd == NULL){
        ret = E_NOK;
    }else{
        while(*str){
            ret =lcd_4bit_send_char_data(lcd,*str++);
        }
    }
    return ret ;
}
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd,uint8 row ,uint8 column,uint8 *str){
    Std_ReturnType ret =E_NOK;
    if (lcd == NULL){
        ret = E_NOK;
    }else{
       ret = lcd_4bit_set_cursor(lcd,row,column);
         while(*str){
            ret =lcd_4bit_send_char_data(lcd,*str++);
        }
        
    }
    return ret ;
}
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,
                                          const uint8 _chr[],uint8 mem_pos){
    Std_ReturnType ret =E_NOK;
    uint8 L_counter=0;
    if (lcd == NULL){
        ret = E_NOK;
    }else{
        lcd_4bit_send_command(lcd,(_LCD_CGRAM_START +(mem_pos*8)));
        for(L_counter=0;L_counter<8;++L_counter){
            ret =lcd_4bit_send_char_data(lcd,_chr[L_counter]);
        }
        ret=lcd_4bit_send_char_data_pos(lcd,row,column,mem_pos);
        
    }
    return ret ;
    
}


Std_ReturnType lcd_8bit_init(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret =E_NOK;
     uint8 l_data_pins_counter=0;
    if (lcd == NULL){
        ret = E_NOK;
    }else{
        ret =gpio_pin_initialize(&(lcd->lcd_rs));
        ret =gpio_pin_initialize(&(lcd->lcd_en));
        for(l_data_pins_counter=0;l_data_pins_counter<8;l_data_pins_counter++){
            ret =gpio_pin_initialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
        __delay_ms(20);
        ret =lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret =lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret =lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        ret =lcd_8bit_send_command(lcd,_LCD_CLEAR);
        ret =lcd_8bit_send_command(lcd,_LCD_RETURN_HOME);
        ret =lcd_8bit_send_command(lcd,_LCD_ENTRY_MODE);
        ret =lcd_8bit_send_command(lcd,_LCD_CURSOR_OFF_DISPLAY_ON);
        ret =lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        ret =lcd_8bit_send_command(lcd,0x80);

    }
    return ret ;
}
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd,uint8 command){
   Std_ReturnType ret =E_NOK;
   uint8 l_counter=0;
    if (lcd == NULL){
        ret = E_NOK;
    }else{
         /*write in RS 0 voltage */
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_low);
        
                for(l_counter=0;l_counter<8;++l_counter){
  ret =gpio_pin_write_logic(&(lcd->lcd_data[l_counter]),(command >>l_counter)& (uint8)0x01);

        }
         /*after any sending you have to set the enable*/
        ret =lcd_8bit_send_enable_signal(lcd);
        
    }
    return ret ;
}
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd,uint8 data){
    Std_ReturnType ret =E_NOK;
    uint8 l_counter=0;
    if (lcd == NULL){
        ret = E_NOK;
    }else{
         /*write in RS 5 voltage */
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_high);
        
        for(l_counter=0;l_counter<8;++l_counter){
  ret =gpio_pin_write_logic(&(lcd->lcd_data[l_counter]),(data >>l_counter)& (uint8)0x01);

        }
         /*after any sending you have to set the enable*/
        ret =lcd_8bit_send_enable_signal(lcd);
         
    }
    return ret ;
}
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd,uint8 row ,uint8 column ,uint8 data){
    Std_ReturnType ret =E_NOK;
    if (lcd == NULL){
        ret = E_NOK;
    }else{
        ret = lcd_8bit_set_cursor(lcd,row,column);
        ret =lcd_8bit_send_char_data(lcd,data);
    }
    return ret ;
}
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd,uint8 *str){
    Std_ReturnType ret =E_NOK;
    if (lcd == NULL){
        ret = E_NOK;
    }else{
        while(*str){
            ret =lcd_8bit_send_char_data(lcd,*str++);
        }
        
    }
    return ret ;
}
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd,uint8 row ,uint8 column,uint8 *str){
    Std_ReturnType ret =E_NOK;
    if (lcd == NULL){
        ret = E_NOK;
    }else{
        ret =lcd_8bit_set_cursor(lcd,row,column);
         while(*str){
            ret =lcd_8bit_send_char_data(lcd,*str++);
        }
        
    }
    return ret ;
}
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd,uint8 row ,uint8 column,
                                                   const uint8 _chr[],uint8 mem_pos){
    Std_ReturnType ret =E_NOK;
    uint8 L_counter=0;
    if (lcd == NULL){
        ret = E_NOK;
    }else{
        lcd_8bit_send_command(lcd,(_LCD_CGRAM_START +(mem_pos*8)));
        for(L_counter=0;L_counter<8;++L_counter){
            ret =lcd_8bit_send_char_data(lcd,_chr[L_counter]);
        }
        ret=lcd_8bit_send_char_data_pos(lcd,row,column,mem_pos);
    }
    return ret ;
}

Std_ReturnType convert_byte_to_string(uint8 value ,uint8 *str){
    Std_ReturnType ret =E_OK;
    if(NULL==str){
        ret =E_NOK;
    }else{
    memset(str,'\0',4);
    sprintf(str,"%i",value);
    }
    return ret;
    
}
Std_ReturnType convert_short_to_string(uint16 value ,uint8 *str){
     Std_ReturnType ret =E_OK;
     uint8 temp_string[6]={0};
     uint8 data_counter=0;
    if(NULL==str){
        ret =E_NOK;
    }else{
    memset(str,' ',5);
    sprintf((char *)temp_string,"%i",value);
    while(temp_string[data_counter]!='\0'){
        str[data_counter]=temp_string[data_counter];
        data_counter++;
    }
    }
    return ret;
}
    

Std_ReturnType convert_int_to_string(uint32 value ,uint8 *str){
     Std_ReturnType ret =E_OK;
    if(NULL==str){
        ret =E_NOK;
    }else{
    memset(str,'\0',11);
    sprintf(str,"%i",value);
    }
    return ret;
}


/*..................helper functions................. */
  static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd,uint8 _data_command){
    Std_ReturnType ret =E_OK;
    ret =gpio_pin_write_logic(&(lcd->lcd_data[0]),(_data_command >>0)& (uint8)0x01);
    ret =gpio_pin_write_logic(&(lcd->lcd_data[1]),(_data_command >>1)& (uint8)0x01);
    ret =gpio_pin_write_logic(&(lcd->lcd_data[2]),(_data_command >>2)& (uint8)0x01);
    ret =gpio_pin_write_logic(&(lcd->lcd_data[3]),(_data_command >>3)&(uint8)0x01);

    
    return ret ;
}
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret =E_OK;
    ret =gpio_pin_write_logic(&(lcd->lcd_en),GPIO_high);
    __delay_us(5);
     ret =gpio_pin_write_logic(&(lcd->lcd_en),GPIO_low);
    
    
    return ret ;
}
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret =E_NOK;
    ret =gpio_pin_write_logic(&(lcd->lcd_en),GPIO_high);
    __delay_us(5);
     ret =gpio_pin_write_logic(&(lcd->lcd_en),GPIO_low);
    
    
    return ret ;
}
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd ,uint8 row ,uint8 column){
    Std_ReturnType ret =E_OK;
    column--;
    switch(row){
         case ROW1: ret =lcd_4bit_send_command(lcd ,(0x80+column)); break;
         case ROW2: ret =lcd_4bit_send_command(lcd ,(0xc0+column)); break;
         case ROW3: ret =lcd_4bit_send_command(lcd ,(0x94+column)); break;
         case ROW4: ret =lcd_4bit_send_command(lcd ,(0xd4+column)); break;
    }
   
}
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd ,uint8 row ,uint8 column){
    Std_ReturnType ret =E_NOK;
    column--;
    switch(row){
         case ROW1: ret =lcd_8bit_send_command(lcd ,(0x80+column)); break;
         case ROW2: ret =lcd_8bit_send_command(lcd ,(0xc0+column)); break;
         case ROW3: ret =lcd_8bit_send_command(lcd ,(0x94+column)); break;
         case ROW4: ret =lcd_8bit_send_command(lcd ,(0xd4+column)); break;
    }
}