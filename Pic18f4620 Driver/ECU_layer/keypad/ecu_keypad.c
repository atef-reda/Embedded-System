#include "ecu_keypad.h"
/**
 * 
 * @param keypad_object
 * @return 
 */
/*
 const uint8 btn_values[ecu_keypad_row][ecu_keypad_columns]={
    {'9','8','7','/'},
    {'6','5','4','*'},
    {'3','2','1','-'},
    {'#','0','=','+'}
};*/

const uint8 btn_values[ecu_keypad_row][ecu_keypad_columns]={
    
    {'7','8','9','/'},
    {'4','5','6','*'},
    {'1','2','3','-'},
    {'c','0','=','+'}

};

Std_ReturnType keypad_initialize( const keypad_t *keypad_object){
    Std_ReturnType ret =E_NOK;
    uint8 rows_counter=0,columns_counter=0;
    if(NULL == keypad_object){
        ret = E_NOK;
    }else{
        for(rows_counter=0;rows_counter<ecu_keypad_row ;rows_counter++){
           ret = gpio_pin_initialize(&(keypad_object->keypad_row_pins[rows_counter]));
        }
        
        for(columns_counter=0;columns_counter<ecu_keypad_columns;columns_counter++){
           ret= gpio_pin_direction_intialize(&(keypad_object->keypad_columns_pins[columns_counter]));
        }
    }
    return ret ;
}
/**
 * 
 * @param keypad_object
 * @param value
 * @return 
 */


Std_ReturnType keypad_get_value( const keypad_t *keypad_object,uint8 *value){
    Std_ReturnType ret =E_NOK;
    uint8 l_rows_counter=0 ,l_columns_counter=0,l_counter=0;
    logic_t column_logic =0;
    
    if((NULL == keypad_object)|| (NULL == value)){
        ret = E_NOK;
    }else{
        for(l_rows_counter=0;l_rows_counter<ecu_keypad_row ;l_rows_counter++){
            /** deactive all rows*/
            for(l_counter=0;l_counter<ecu_keypad_row;l_counter++){
               ret = gpio_pin_write_logic(&(keypad_object->keypad_row_pins[l_counter]),GPIO_low);
            }
            /** active one row */
            ret = gpio_pin_write_logic(&(keypad_object->keypad_row_pins[l_rows_counter]),GPIO_high);  
            /** check about all columns and return  with value of button */
            for(l_columns_counter=0;l_columns_counter<ecu_keypad_columns;l_columns_counter++){
                ret =gpio_pin_read_logic(&(keypad_object->keypad_columns_pins[l_columns_counter]),&column_logic);
                
                if(GPIO_high==column_logic){
                    *value=btn_values[l_rows_counter][l_columns_counter];
                    while(PORTBbits.RB0==1);
                    while(PORTBbits.RB1==1);
                    while(PORTBbits.RB2==1);
                    while(PORTBbits.RB7==1);
                 }
            }
        
    }
    }
    return ret ;
}