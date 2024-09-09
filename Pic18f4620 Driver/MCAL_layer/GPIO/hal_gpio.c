/* 
 * File:   hal_gpio.c
 * Author: Home?
 *
 * Created on July 28, 2023, 10:13 PM
 */
#include "hal_gpio.h"
/*reference to the data direction control registers */
volatile uint8 *tris_registers[]={&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
/*reference to the port status  register*/
volatile uint8 *port_registers[]={&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};
/*reference to the data latch register (Read and Write to Data latch )*/
volatile uint8 *lat_registers[]={&LATA,&LATB,&LATC,&LATD,&LATE};

#if  PORT_PIN_CONFIGURATION  ==   CONFIG_ENABLE 
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config  && _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret=E_NOK; 
    }
    else{
         switch(_pin_config->direction){
        case  GPIO_DIRECTION_output :
            clear_bit(*(tris_registers[_pin_config->port]), _pin_config->pin);
            break;
        case GPIO_DIRECTION_input:
            set_bit(*(tris_registers[_pin_config->port]),_pin_config->pin);
            break;
        default:
            ret=E_NOK;
    }
    }
      return ret;
    
}
#endif 

#if  PORT_PIN_CONFIGURATION  ==   CONFIG_ENABLE 
Std_ReturnType gpio_Pin_get_direction_status(const pin_config_t *_pin_config,direction_t *direction_status){    Std_ReturnType ret =E_OK;
    if(NULL== _pin_config && NULL == direction_status && _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
                

    }else{
        *direction_status  = read_bit(*tris_registers[_pin_config->port],_pin_config->pin);
    }
    return ret;
}
#endif

#if  PORT_PIN_CONFIGURATION  ==   CONFIG_ENABLE 
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config,logic_t logic){
    Std_ReturnType ret =E_OK;
    if(NULL== _pin_config && _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret=E_NOK;
    }else{
                switch(logic){
                    case  GPIO_low :
                        clear_bit(*lat_registers[_pin_config->port],_pin_config->pin);
                        break;
                    case GPIO_high :
                        set_bit(*lat_registers[_pin_config->port],_pin_config->pin);
                        break;
                    default:
                ret = E_NOK;              
        }
    }
    return ret;
}
#endif
#if PORT_PIN_CONFIGURATION ==CONFIG_ENABLE 
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config,logic_t *logic){
        Std_ReturnType ret =E_OK;
        if(NULL == _pin_config && NULL == logic && _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret=E_NOK; 
    }
    else{
            *logic=read_bit(*port_registers[_pin_config->port],_pin_config->pin);

    }
        return ret;

}
#endif
#if  PORT_PIN_CONFIGURATION  ==   CONFIG_ENABLE 
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config){
      Std_ReturnType ret =E_OK;
        if(NULL == _pin_config && _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret=E_NOK; 
    }
    else{
           toggle_bit(*lat_registers[_pin_config->port],_pin_config->pin);
    }   
        return ret;
}

#endif
#if  PORT_PIN_CONFIGURATION  ==   CONFIG_ENABLE
Std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config ){
     Std_ReturnType ret =E_OK;
        if(NULL == _pin_config && _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret=E_NOK; 
    }
    else{
          ret = gpio_pin_direction_intialize(_pin_config);
           ret =gpio_pin_write_logic(_pin_config,_pin_config->logic);
    }   
        return ret;
}

#endif

#if PORT_CONFIGURATION  ==   CONFIG_ENABLE 
Std_ReturnType gpio_port_direction_intialize(port_index_t port,uint8 direction){
      Std_ReturnType ret =E_OK;
      if(port>PORT_MAX_NUMBER-1){
          ret = E_NOK;
      }
      else{
          *tris_registers[port]=direction;
      }
        return ret;
}
#endif


#if PORT_CONFIGURATION  ==   CONFIG_ENABLE 
Std_ReturnType gpio_Port_get_direction_status(port_index_t port,uint8 *direction_status){
      Std_ReturnType ret =E_OK;
        if((NULL == direction_status )&&(port>PORT_MAX_NUMBER-1)){
        ret=E_NOK; 
    }
    else{
            *direction_status=*tris_registers[port];
            
    }
        return ret;
}
#endif

#if PORT_CONFIGURATION   ==  CONFIG_ENABLE 
Std_ReturnType gpio_port_write_logic(port_index_t port,uint8 logic){
      Std_ReturnType ret =E_OK;
       if(port>PORT_MAX_NUMBER-1){
          ret = E_NOK;
      }
      else{
           *lat_registers[port]=logic;
         
      }
        
    
        return ret;
}
#endif

#if PORT_CONFIGURATION  ==   CONFIG_ENABLE 
Std_ReturnType gpio_port_read_logic(port_index_t port,uint8 *logic){
      
    Std_ReturnType ret =E_OK;
        if((NULL ==logic )&& (port>PORT_MAX_NUMBER-1 )){
        ret=E_NOK; 
    }
    else{
            *logic = *lat_registers[port];
    }
        return ret;
}
#endif
#if PORT_CONFIGURATION   ==  CONFIG_ENABLE 
Std_ReturnType gpio_port_toggle_logic(port_index_t port){
      Std_ReturnType ret =E_OK;
       if(port>PORT_MAX_NUMBER-1){
          ret = E_NOK;
      }
      else{
           *lat_registers[port] ^= 0xFF;
         
      }
        
      
      
        return ret;
    
}
#endif
