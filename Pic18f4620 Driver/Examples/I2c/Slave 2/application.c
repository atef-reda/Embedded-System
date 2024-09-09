/*
 * File:   application.c
 * Author: Home?
 *
 * Created on July 28, 2023, 10:13 PM
 */



#include "application.h"

void application_initialize(void);
//void Adc_Default_Interrupt_Handler(void);
//void TMR0_Default_Interrupt_Handler(void);
//void timer1_timer_init();
//void timer1_counter_init();
led_t led1 = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN0,
    .led_status = GPIO_low
};
led_t led2 = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN1,
    .led_status = GPIO_low
};
//led_t led4 ={
//    .port =PORTC_INDEX,
//    .pin=GPIO_PIN3,
//    .led_status=GPIO_low
//};
/*
void int0_app_isr(void) {
    led_turn_toggle(&led1);
    __delay_ms(500);
}
void int1_app_isr(void) {
    led_turn_toggle(&led2);
        __delay_ms(500);

}
void int2_app_isr(void) {
    led_turn_toggle(&led3);
        __delay_ms(500);

}
interrupt_INTX_t int0_obj ={
    .EXT_InterruptHandler = int0_app_isr,
    .edge = interrupt_rising_edge,
    .source = interrupt_External_INT0,
    .priority = Interrupt_high_priority,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN0,
    .mcu_pin.direction = GPIO_DIRECTION_input,
    .mcu_pin.logic = GPIO_low
};
interrupt_INTX_t int1_obj ={
    .EXT_InterruptHandler = int1_app_isr,
    .edge = interrupt_rising_edge,
    .source = interrupt_External_INT1,
    .priority = interrupt_low_priority,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN1,
    .mcu_pin.direction = GPIO_DIRECTION_input,
    .mcu_pin.logic = GPIO_low
};
interrupt_INTX_t int2_obj ={
    .EXT_InterruptHandler = int2_app_isr,
    .edge = interrupt_rising_edge,
    .source = interrupt_External_INT2,
    .priority = Interrupt_high_priority,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN2,
    .mcu_pin.direction = GPIO_DIRECTION_input,
    .mcu_pin.logic = GPIO_low
};

 */


//void RB4_high_int_app_ISR(void){
//     led_turn_on(&led1);
//}
//void RB4_low_int_app_ISR(void){
//  led_turn_on(&led2);
//}
//void RB5_high_int_app_ISR(void){
//     led_turn_off(&led1);
//}
//void RB5_low_int_app_ISR(void){
//  led_turn_off(&led2);
//}
//void RB6_high_int_app_ISR(void){
//     led_turn_on(&led3);
//}
//void RB6_low_int_app_ISR(void){
//  led_turn_on(&led4);
//}
//void RB7_high_int_app_ISR(void){
//     led_turn_off(&led3);
//}
//void RB7_low_int_app_ISR(void){
//  led_turn_off(&led4);
//}

//interrupt_RBx_t rb4_int_obj ={
//    .EXT_InterruptHandler_high =RB4_high_int_app_ISR,
//    .EXT_InterruptHandler_low =RB4_low_int_app_ISR,
//    .mcu_pin.pin =GPIO_PIN4,
//    .mcu_pin.port =PORTB_INDEX,
//    .mcu_pin.direction=GPIO_DIRECTION_input,
//    .priority =Interrupt_high_priority
//};
//interrupt_RBx_t rb5_int_obj ={
//    .EXT_InterruptHandler_high =RB5_high_int_app_ISR,
//    .EXT_InterruptHandler_low =RB5_low_int_app_ISR,
//    .mcu_pin.pin =GPIO_PIN5,
//    .mcu_pin.port =PORTB_INDEX,
//    .mcu_pin.direction=GPIO_DIRECTION_input,
//    .priority =Interrupt_high_priority
//};
//interrupt_RBx_t rb6_int_obj ={
//    .EXT_InterruptHandler_high =RB6_high_int_app_ISR,
//    .EXT_InterruptHandler_low =RB6_low_int_app_ISR,
//    .mcu_pin.pin =GPIO_PIN6,
//    .mcu_pin.port =PORTB_INDEX,
//    .mcu_pin.direction=GPIO_DIRECTION_input,
//    .priority =Interrupt_high_priority
//};
//interrupt_RBx_t rb7_int_obj ={
//    .EXT_InterruptHandler_high =RB7_high_int_app_ISR,
//    .EXT_InterruptHandler_low =RB7_low_int_app_ISR,
//    .mcu_pin.pin =GPIO_PIN7,
//    .mcu_pin.port =PORTB_INDEX,
//    .mcu_pin.direction=GPIO_DIRECTION_input,
//    .priority =Interrupt_high_priority
//};

/*
 typedef struct{
    void (* EXT_InterruptHandler)(void);
        pin_config_t mcu_pin;
        interrupt_INTX_edge edge;
        interrupt_INTX_scr source  ;
        interrupt_priority_cfg priority ;
}interrupt_INTX_t;
 */

//adc_conf_t adc_obj ={
//    .ADC_Iterrupt_Handler = Adc_Default_Interrupt_Handler,
//    .acquisition_time = ADC_12_TAD,
//    .chanel_select = ADC_CHANAL_AN0,
//    .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
//    .result_format = ADC_RESULT_RIGHT,
//    .voltage_referance = ADC_VOLTAGE_REFERANCE_DISABLED
//};
//chr_lcd_4bit_t lcd_obj=
//{
//    .lcd_rs.port=PORTC_INDEX,
//    .lcd_rs.pin=GPIO_PIN0,
//    .lcd_rs.direction=GPIO_DIRECTION_output,
//    .lcd_rs.logic=GPIO_low,
//
//    .lcd_en.port = PORTC_INDEX,
//    .lcd_en.pin = GPIO_PIN1,
//    .lcd_en.direction = GPIO_DIRECTION_output,
//    .lcd_en.logic = GPIO_low,
//    
//    .lcd_data[0].port = PORTC_INDEX,
//    .lcd_data[0].pin = GPIO_PIN2,
//    .lcd_data[0].direction = GPIO_DIRECTION_output,
//    .lcd_data[0].logic = GPIO_low,
//    
//    .lcd_data[1].port = PORTC_INDEX,
//    .lcd_data[1].pin = GPIO_PIN3,
//    .lcd_data[1].direction = GPIO_DIRECTION_output,
//    .lcd_data[1].logic = GPIO_low,
//    
//    .lcd_data[2].port = PORTC_INDEX,
//    .lcd_data[2].pin = GPIO_PIN4,
//    .lcd_data[2].direction = GPIO_DIRECTION_output,
//    .lcd_data[2].logic = GPIO_low,
//    
//    .lcd_data[3].port = PORTC_INDEX,
//    .lcd_data[3].pin = GPIO_PIN5,
//    .lcd_data[3].direction = GPIO_DIRECTION_output,
//    .lcd_data[3].logic = GPIO_low,
//            
//};
//volatile uint16 res1,res2,res3,res4;
//
//timer0_t tmr0_timer_obj ={
//    .ADC_Iterrupt_Handler = TMR0_Default_Interrupt_Handler,
//    .timer0_preload_value = 3036,
//    .timer0_prescaler_enable = TIMER0_PRESCALER_ENABLE_CFG,
//    .timer0_prescaler_value = TIMER0_PRESCALER_DIV_BY_4,
//    .timer0_register_size = TIMER0_REGISTER_16_BIT_ENABLE_CFG,
//    .timer0_source_mode = TIMER0_TIMER_MODE_ENABLE_CFG
//};
//timer0_t tmr0_counter_obj ={
//    .ADC_Iterrupt_Handler = TMR0_Default_Interrupt_Handler,
//    .timer0_preload_value = 0,
//    .timer0_prescaler_enable = TIMER0_PRESCALER_DISABLE_CFG,
//    .timer0_register_size = TIMER0_REGISTER_16_BIT_ENABLE_CFG,
//    .timer0_source_mode = TIMER0_COUNTER_MODE_ENABLE_CFG,
//    .timer0_counter_edge = TIMER0_COUNTER_RASING_EDGE_CFG
//};
//volatile uint32  Tmr2_flag;
//void TMR1_Default_Interrupt_Handler(void) {
//    Tmr2_flag++;
//    led_turn_toggle(&led1);
//}
//timer1_t timer1_counter_obj={
//    .TMR1_Iterrupt_Handler = TMR1_Default_Interrupt_Handler,
//    .timer1_source_mode = TIMER3_COUNTER_MODE_ENABLE_CFG,
//    .timer1_prescaler_value = TIMER1_PRESCALER_VALUE_DIV_1,
//    .timer1_preload_value = 0,
//    .timer1_regisetr_wr_mode = TIMER1_RW_16_BIT_REGISTER_ENABLE_CFG,
//    .timer1_counter_mode = TIMER1_SYNC_COUNTER_MODE_ENABLE_CFG,
//};
//
//
//timer1_t timer1_tmr_obj = {
//    .TMR1_Iterrupt_Handler = TMR1_Default_Interrupt_Handler,
//    .timer1_source_mode = TIMER1_TIMER_MODE_ENABLE_CFG,
//    .timer1_prescaler_value = TIMER1_PRESCALER_VALUE_DIV_4,
//    .timer1_preload_value = 15536,
//    .timer1_regisetr_wr_mode = TIMER1_RW_16_BIT_REGISTER_ENABLE_CFG,
//};
//volatile uint32  Tmr3_flag=ZERO_INIT;
//void TMR3_Default_Interrupt_Handler(void) {
//    Tmr3_flag++;
//    led_turn_toggle(&led1);
//}
//timer3_t timer3_counter_obj={
//    .TMR3_Iterrupt_Handler = NULL,
//    .timer3_source_mode = TIMER3_COUNTER_MODE_ENABLE_CFG,
//    .timer3_prescaler_value = TIMER3_PRESCALER_VALUE_DIV_1,
//    .timer3_preload_value = 0,
//    .timer3_regisetr_wr_mode = TIMER3_RW_16_BIT_REGISTER_ENABLE_CFG,
//    .timer3_counter_mode = TIMER3_SYNC_COUNTER_MODE_ENABLE_CFG,
//};
//
//
//timer3_t timer3_tmr_obj = {
//    .TMR3_Iterrupt_Handler = TMR3_Default_Interrupt_Handler,
//    .timer3_source_mode = TIMER3_TIMER_MODE_ENABLE_CFG,
//    .timer3_prescaler_value = TIMER3_PRESCALER_VALUE_DIV_4,
//    .timer3_preload_value = 15536,
//    .timer3_regisetr_wr_mode = TIMER3_RW_16_BIT_REGISTER_ENABLE_CFG,
//};
//Std_ReturnType ret = E_NOK;
//uint16 timer3_counter_val;

//
//void CCP_Default_Interrupt_handler(void) {
//  
//}
//
//void TMR3_Default_Interrupt_handler(void) {
//}

void usart_module_init()
{
    usart_t usart_obj;
    
    usart_obj.baudrate=9600;
    usart_obj.baudrate_gen_config=BAUDRATE_ASYN_08BIT_LOW_SPEED;
    
    usart_obj.usart_rx_cfg.usart_rx_enable=EUSERT_ASYNCHRONOUS_RX_ENABLE;
    usart_obj.usart_rx_cfg.usart_rx_9bit_enable=EUSERT_ASYNCHRONOUS_9BIT_RX_DISABLE;
    usart_obj.usart_rx_cfg.usart_rx_interrupt_enable=EUSERT_ASYNCHRONOUS_RX_INTERRUPT_DISABLE;
    
    usart_obj.usart_tx_cfg.usart_tx_enable=EUSERT_ASYNCHRONOUS_TX_ENABLE;
    usart_obj.usart_tx_cfg.usart_tx_9bit_enable=EUSERT_ASYNCHRONOUS_9BIT_TX_DISABLE;
    usart_obj.usart_tx_cfg.usart_tx_interrupt_enable=EUSERT_ASYNCHRONOUS_TX_INTERRUPT_DISABLE;
    
    usart_obj.EUSART_RXDefaultInterruptHandeler=NULL;
    usart_obj.EUSART_RXDefaultInterruptHandeler = NULL;
    usart_obj.EUSART_OverRunErrorHandeler = NULL;
    usart_obj.EUSART_FramingErrorHandeler = NULL;
    EUSART_ASYNC_Init(&usart_obj);
}
uint32 volatile counter_tx_interrupt;
uint32 volatile counter_rx_interrupt;

void EUSART_OverRunError_DefaultInterruptHandeler() {
    EUSART_ASYNC_RX_Restart();
}

void EUSART_FramingError_DefaultInterruptHandeler() {
    uint8 _data;
    EUSART_ASYNC_Read_Byte_Blocking(&_data);
}

void EUSART_TXDefaultInterruptHandeler() {
    counter_tx_interrupt++;
}
uint8 read_value;
uint8 volatile _data;
void EUSART_RXDefaultInterruptHandeler()
{
    Std_ReturnType ret = E_OK;
    EUSART_ASYNC_Read_Byte_Blocking(&_data);
    if('c' == _data){
        led_turn_on(&led1);
        ret = EUSART_ASYNC_Write_Byte_Blocking('b');
        __delay_ms(250);
    }
    if('d' == _data){
        led_turn_off(&led1);
        ret = EUSART_ASYNC_Write_Byte_Blocking('a');
        __delay_ms(250);
    }
}
void usart_module_interrupt_init()
{
    usart_t usart_obj;
    
    usart_obj.baudrate=9600;
    usart_obj.baudrate_gen_config=BAUDRATE_ASYN_08BIT_LOW_SPEED;
    
    usart_obj.usart_rx_cfg.usart_rx_enable=EUSERT_ASYNCHRONOUS_RX_ENABLE;
    usart_obj.usart_rx_cfg.usart_rx_9bit_enable=EUSERT_ASYNCHRONOUS_9BIT_RX_DISABLE;
    usart_obj.usart_rx_cfg.usart_rx_interrupt_enable=EUSERT_ASYNCHRONOUS_RX_INTERRUPT_ENABLE;
    
    usart_obj.usart_tx_cfg.usart_tx_enable=EUSERT_ASYNCHRONOUS_TX_ENABLE;
    usart_obj.usart_tx_cfg.usart_tx_9bit_enable=EUSERT_ASYNCHRONOUS_9BIT_TX_DISABLE;
    usart_obj.usart_tx_cfg.usart_tx_interrupt_enable=EUSERT_ASYNCHRONOUS_TX_INTERRUPT_ENABLE;
    
    usart_obj.EUSART_TXDefaultInterruptHandeler=NULL;
    usart_obj.EUSART_RXDefaultInterruptHandeler = EUSART_RXDefaultInterruptHandeler;
    usart_obj.EUSART_OverRunErrorHandeler = NULL;
    usart_obj.EUSART_FramingErrorHandeler = NULL;
    EUSART_ASYNC_Init(&usart_obj);
}
uint8 recived_data;
Std_ReturnType ret = E_NOK;

#define slave_1  0x60
#define slave_2  0x62
uint8 slave_ack;
volatile uint8 counter_slave2;
void MSSP_DefaultInterruptHandler()
{
    counter_slave2++;
}
mssp_i2c_t i2c_obj=
{
  .I2C_DefaultInterruptHandler=MSSP_DefaultInterruptHandler,
  .I2C_Report_Receive_Overflow=NULL,
  .I2C_Report_Write_Collision=NULL,
  .i2c_cfg.i2c_SMBus_control=I2C_SMBus_DISABLE,
  .i2c_cfg.i2c_mode=I2C_MSSP_SLAVE_MODE,
  .i2c_cfg.i2c_mode_cfg=I2C_SLAVE_MODE_7BIT_ADDRESS,
  .i2c_cfg.i2c_slew_rate=I2C_SLEW_RATE_DISABLE,
  .i2c_cfg.i2c_slave_address=slave_2,
  .i2c_cfg.i2c_general_call=I2C_GENERAL_CALL_DISABLE
};
//void MSSP_I2c_Send_1_Byte(uint8 slave_address,uint8 data)
//{
//    MSSP_I2C_Master_Send_Start(&i2c_obj);
//    MSSP_I2C_Master_Write_Blocking(&i2c_obj,slave_address,&slave_ack);
//    MSSP_I2C_Master_Write_Blocking(&i2c_obj,data,&slave_ack);
//    MSSP_I2C_Master_Send_Stop(&i2c_obj);
//}
int main() {
//    application_initialize();
    MSSP_I2C_Init(&i2c_obj);
//    MSSP_I2c_Send_1_Byte(slave_1,'a');
//    __delay_ms(1000);
//    MSSP_I2c_Send_1_Byte(slave_2,'b');
//    __delay_ms(1000);
    while (1) {
    }
    return (EXIT_SUCCESS);
}

void application_initialize(void) {
    Std_ReturnType ret = E_NOK;

    led_initilaize(&led1);
    led_initilaize(&led2);
}



//void timer1_timer_init() {
//   
//    Timer1_Init(&timer1_tmr_obj);
//}

//void timer1_counter_init()
//{
//    
//    Timer1_Init(&timer1_counter_obj);
//}


/* capture mode
ccp_t ccp1_obj;
timer3_t tmr3_obj;

volatile uint8 CCP1_Second_Copture_Flag = 0;
uint16 Second_Copture = 0;
volatile uint32 Timer3_OverFlow = 0;
uint32 Total_Period_MicroSecond = 0;
uint32 Freq = 0;

void CCP_Default_Interrupt_handler(void) {
    Std_ReturnType ret = E_NOK;
    static uint8 CCP1_Interrupt_Flag = 0;
    CCP1_Interrupt_Flag++;
    CCP1_Second_Copture_Flag++;
    if(CCP1_Interrupt_Flag == 1){
        ret = Timer3_Write_value(&tmr3_obj, 0);
    }
    else if(CCP1_Interrupt_Flag == 2){
        CCP1_Interrupt_Flag = 0;
        ret = CCP1_Capture_Mode_Read_Value(&Second_Copture);
                   Timer3_OverFlow = 0;
    }
}

void TMR3_Default_Interrupt_handler(void) {
    Timer3_OverFlow++;
}

int main() {
    ccp1_obj.CCP1_Iterrupt_Handler = CCP_Default_Interrupt_handler;
    ccp1_obj.ccp_capture_timer = CCP2_CCP1_TIMER3;
    ccp1_obj.ccp_inst = CCP1_INST;
    ccp1_obj.ccp_mode = CCP_CAPTURE_MODE_SELECTED;
    ccp1_obj.ccp_mode_variant = CCP_CAPTURE_MODE_1_RISING_EDGE;
    ccp1_obj.ccp_pin.port = PORTC_INDEX;
    ccp1_obj.ccp_pin.pin = GPIO_PIN2;
    ccp1_obj.ccp_pin.direction = GPIO_DIRECTION_input;
    CCP_Init(&ccp1_obj);

    tmr3_obj.TMR3_Iterrupt_Handler = TMR3_Default_Interrupt_handler;
    tmr3_obj.timer3_preload_value = 0;
    tmr3_obj.timer3_prescaler_value = TIMER3_PRESCALER_VALUE_DIV_1;
    tmr3_obj.timer3_regisetr_wr_mode = TIMER3_RW_8_BIT_REGISTER_ENABLE_CFG;
    tmr3_obj.timer3_source_mode = TIMER3_TIMER_MODE_ENABLE_CFG;
    Timer3_Init(&tmr3_obj);
    while (1) {
        if (CCP1_Second_Copture_Flag == 2) {
            Total_Period_MicroSecond = (Timer3_OverFlow * 65536) + Second_Copture;
            Freq = (uint32) (1 / (Total_Period_MicroSecond / 1000000.0));
            CCP1_Second_Copture_Flag = 0;
        }
    }
    return (EXIT_SUCCESS);
}

void application_initialize(void) {
    Std_ReturnType ret = E_NOK;

    led_initilaize(&led1);
}


 */