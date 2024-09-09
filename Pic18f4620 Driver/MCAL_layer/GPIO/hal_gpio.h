/* 
 * File:   hal_gpio.h
 * Author: Home?
 *
 * Created on July 28, 2023, 10:24 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H
/*section :  includes*/
#include "../mcal_std_types.h"
#include "../device_config.h"
/* section :macro  declaration   */
#include <xc.h>

#define BIT__MASK   (uint8)1
#define PORT_PIN_MAX_NUMBER 8
#define PORT_MAX_NUMBER 5

#define PORT_PIN_CONFIGURATION     CONFIG_ENABLE  
#define PORT_CONFIGURATION     CONFIG_ENABLE  



/*section : macro functions declaration */
#define HWREG8(_x)        (*((volatile uint8 *)(_x))) 


#define set_bit(REG,BIT_POSN)          (REG |=(1 <<BIT_POSN))
#define clear_bit(REG,BIT_POSN)         (REG &=~(BIT__MASK <<BIT_POSN))
#define toggle_bit(REG,BIT_POSN)         REG ^=(BIT__MASK <<BIT_POSN)
#define read_bit(REG,BIT_POSN)              ((REG>>BIT_POSN) & BIT__MASK )

/*section :data type declarations */
typedef enum{
    GPIO_low=0,
    GPIO_high
}logic_t;

typedef enum {
    GPIO_DIRECTION_output = 0,
    GPIO_DIRECTION_input
} direction_t;

typedef enum {
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
}pin_index_t;
typedef enum{
    PORTA_INDEX=0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
}port_index_t;
typedef struct{
    uint8 port :3 ;     /*@ref port_index_t*/    
    uint8 pin : 3 ;     /*@ref pin_index_t */
    uint8 direction :1; /*@ref direction_t*/
    uint8 logic :1;     /*@ref logic_t */
}pin_config_t;


/*section :function declarations */
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config);
Std_ReturnType gpio_Pin_get_direction_status(const pin_config_t *_pin_config,direction_t *direction_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config,logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config,logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config );


Std_ReturnType gpio_port_direction_intialize(port_index_t port,uint8 direction);
Std_ReturnType gpio_Port_get_direction_status(port_index_t port,uint8 *direction_status);
Std_ReturnType gpio_port_write_logic(port_index_t port,uint8 logic);
Std_ReturnType gpio_port_read_logic(port_index_t port,uint8 *logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);
    
#endif	/* HAL_GPIO_H */

