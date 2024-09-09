/* 
 * File:   hal_usart.h
 * Author: redaa
 *
 * Created on November 27, 2023, 10:28 AM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H


/*section: includes */
#include "xc.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "hal_usart_cfg.h"
/*----------------section : macro declarations---------------- */
/*Enable / Disable USART Module*/
#define EUSART_MODULE_ENABLE       1
#define EUSART_MODULE_DISABLE      0
/*Selecting USART Working Mode*/
#define EUSERT_SYNCHRONOUS_MODE         1
#define EUSERT_ASYNCHRONOUS_MODE        0
/*Baud Rate Generator Asynchronous Speed Mode*/
#define EUSERT_ASYNCHRONOUS_HIGH_SPEED  1
#define EUSERT_ASYNCHRONOUS_LOW_SPEED   0
/*Baud Rate Generator Register Size*/
#define EUSERT_16BIT_BAUDRATE_GEN       1
#define EUSERT_08BIT_BAUDRATE_GEN        0

/*EUSART Transmit Enable */
#define EUSERT_ASYNCHRONOUS_TX_ENABLE   1
#define EUSERT_ASYNCHRONOUS_TX_DISABLE  0
/*EUSART Transmit Interrupt Enable */
#define EUSERT_ASYNCHRONOUS_TX_INTERRUPT_ENABLE   1
#define EUSERT_ASYNCHRONOUS_TX_INTERRUPT_DISABLE  0
/*EUSART 9-Bit Transmit Enable */
#define EUSERT_ASYNCHRONOUS_9BIT_TX_ENABLE   1
#define EUSERT_ASYNCHRONOUS_9BIT_TX_DISABLE  0

/*EUSART Receiver Enable */
#define EUSERT_ASYNCHRONOUS_RX_ENABLE   1
#define EUSERT_ASYNCHRONOUS_RX_DISABLE  0
/*EUSART Receiver Interrupt Enable */
#define EUSERT_ASYNCHRONOUS_RX_INTERRUPT_ENABLE   1
#define EUSERT_ASYNCHRONOUS_RX_INTERRUPT_DISABLE  0
/*EUSART 9-Bit Receiver Enable */
#define EUSERT_ASYNCHRONOUS_9BIT_RX_ENABLE   1
#define EUSERT_ASYNCHRONOUS_9BIT_RX_DISABLE  0

/*EUSART Framing Error*/
#define EUSERT_FRAMING_ERROR_DETECTED     1
#define EUSERT_FRAMING_ERROR_CLEARED      0
/*EUSART Overrun Error*/
#define EUSERT_OVERRUN_ERROR_DETECTED     1
#define EUSERT_OVERRUN_ERROR_CLEARED      0

/*--------------------section: macro functions declarations-------------------- */

/*--------------------section: data types declarations-------------------*/
typedef enum
{
    BAUDRATE_ASYN_08BIT_LOW_SPEED,
    BAUDRATE_ASYN_08BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_LOW_SPEED,
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_08BIT,
    BAUDRATE_SYN_16BIT,
}baudrate_gen_t;

typedef struct {
    uint8 usart_tx_reserved : 5;
    uint8 usart_tx_enable : 1;
    uint8 usart_tx_interrupt_enable : 1;
    uint8 usart_tx_9bit_enable : 1;
} usart_tx_cfg_t;

typedef struct {
    uint8 usart_rx_reserved : 5;
    uint8 usart_rx_enable : 1;
    uint8 usart_rx_interrupt_enable : 1;
    uint8 usart_rx_9bit_enable : 1;
} usart_rx_cfg_t;

typedef union
{
    struct
    {
        uint8 usart_reserved : 6;
        uint8 usart_ferror : 1;
        uint8 usart_oerror : 1;
    };
    uint8 status;
}usart_error_status_t;

typedef struct
{
    uint32 baudrate;
    baudrate_gen_t baudrate_gen_config; 
    usart_tx_cfg_t usart_tx_cfg; 
    usart_rx_cfg_t usart_rx_cfg;
#if INTERRUPT_Priority_Levels_Enable==INTERRUPT_feature_ENABLE
    interrupt_priority_cfg usart_tx_int_priority;
    interrupt_priority_cfg usart_rx_int_priority;
#endif
    usart_error_status_t  usart_error_status;
    void (*EUSART_TXDefaultInterruptHandeler) (void);
    void (*EUSART_RXDefaultInterruptHandeler) (void);
    void (*EUSART_FramingErrorHandeler) (void);
    void (*EUSART_OverRunErrorHandeler) (void);
}usart_t;

/* ----------------------- section: function declarations ----------------------- */
Std_ReturnType EUSART_ASYNC_Init(const usart_t *usart);
Std_ReturnType EUSART_ASYNC_DeInit(const usart_t *usart);
Std_ReturnType EUSART_ASYNC_Read_Byte_Blocking(uint8 *data);
Std_ReturnType EUSART_ASYNC_Read_Byte_NonBlocking(uint8 *data);
Std_ReturnType EUSART_ASYNC_Write_Byte_Blocking(uint8 data);
Std_ReturnType EUSART_ASYNC_Write_String_Blocking(uint8 *data,uint16 str_len);
Std_ReturnType EUSART_ASYNC_RX_Restart(void);

Std_ReturnType EUSART_ASYNC_Write_Byte_NonBlocking(uint8 data);
Std_ReturnType EUSART_ASYNC_Write_String_NonBlocking(uint8 *data,uint16 str_len);

#endif	/* HAL_USART_H */

