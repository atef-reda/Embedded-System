/*
 * File:   hal_usart.c
 * Author: redaa
 *
 * Created on November 27, 2023, 10:29 AM
 */


#include "hal_usart.h"

#if ESURT_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
static interrupt_handler_fun ESURT_TX_interrupt_handler = NULL;
#endif

#if ESURT_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
static interrupt_handler_fun ESURT_RX_interrupt_handler = NULL;
static interrupt_handler_fun EUSART_FramingError_interrupt_handler = NULL;
static interrupt_handler_fun EUSART_OverRunError_interrupt_handler = NULL;
#endif



static void Eusart_Baud_Rate_Calculation(const usart_t *usart); 
static void Eusart_Async_Tx_Init(const usart_t *usart);
static void Eusart_Async_Rx_Init(const usart_t *usart);

Std_ReturnType EUSART_ASYNC_Init(const usart_t *usart) {
    Std_ReturnType ret = E_OK;
    if (NULL == usart) {

        ret = E_NOK;
    } else {
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
        Eusart_Baud_Rate_Calculation(usart);
        TRISCbits.RC7=1;
        TRISCbits.RC6=1;
        Eusart_Async_Tx_Init(usart);
        Eusart_Async_Rx_Init(usart);
        RCSTAbits.SPEN = EUSART_MODULE_ENABLE;
    }
    return ret;
}
Std_ReturnType EUSART_ASYNC_DeInit(const usart_t *usart){
    Std_ReturnType ret = E_OK;
    if (NULL == usart) {

        ret = E_NOK;
    } else {
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
    }
    return ret;
}
Std_ReturnType EUSART_ASYNC_Read_Byte_Blocking(uint8 *data){
    Std_ReturnType ret = E_OK;
    if (NULL == data) {
        
        ret = E_NOK;
    } else {
        while(!PIR1bits.RCIF);
        *data=RCREG;
    }
    return ret;
}
Std_ReturnType EUSART_ASYNC_Read_Byte_NonBlocking(uint8 *data)
{
    Std_ReturnType ret = E_OK;
    if (NULL == data) {
        ret = E_NOK;
    } else {
        if (PIR1bits.RCIF) {
            *data = RCREG;
        } else {
            ret = E_NOK;
        }
    }
    return ret;
}

Std_ReturnType EUSART_ASYNC_Write_Byte_Blocking(uint8 data) {
    Std_ReturnType ret = E_OK;
    while (!TXSTAbits.TRMT);
#if ESURT_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
    ESURT_TX_interruptEnable();
#endif
    TXREG = data;
    return ret;
}
Std_ReturnType EUSART_ASYNC_Write_String_Blocking(uint8 *data,uint16 str_len)
{
    Std_ReturnType ret = E_OK;
    uint16 char_counter=ZERO_INIT;
    if (NULL == data) {
        
        ret = E_NOK;
    } else {
        for(char_counter=ZERO_INIT;char_counter<str_len;char_counter++)
        {
            EUSART_ASYNC_Write_Byte_Blocking(data[char_counter]);
        }
    }
    return ret;
}

Std_ReturnType EUSART_ASYNC_RX_Restart(void)
{
        Std_ReturnType ret = E_OK;
        RCSTAbits.CREN=0;
        RCSTAbits.CREN=1;
    return ret;

}
/*  ------------------- Helper Functions -------------------  */

static void Eusart_Baud_Rate_Calculation(const usart_t *usart)
{
    float Baud_Rate_Temp=0;
    switch(usart->baudrate_gen_config) {
        case BAUDRATE_ASYN_08BIT_LOW_SPEED:
            TXSTAbits.SYNC = EUSERT_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSERT_ASYNCHRONOUS_LOW_SPEED;
            BAUDCTLbits.BRG16 = EUSERT_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp=(((_XTAL_FREQ/(float)usart->baudrate)/64)-1);
            break;
        case BAUDRATE_ASYN_08BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSERT_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSERT_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCTLbits.BRG16 = EUSERT_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp=(((_XTAL_FREQ/(float)usart->baudrate)/16)-1);
            break;
        case BAUDRATE_ASYN_16BIT_LOW_SPEED:
            TXSTAbits.SYNC = EUSERT_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSERT_ASYNCHRONOUS_LOW_SPEED;
            BAUDCTLbits.BRG16 = EUSERT_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp=(((_XTAL_FREQ/(float)usart->baudrate)/16)-1);
            break;
        case BAUDRATE_ASYN_16BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSERT_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSERT_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCTLbits.BRG16 = EUSERT_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp=(((_XTAL_FREQ/(float)usart->baudrate)/4)-1);
            break;
        case BAUDRATE_SYN_08BIT:
            TXSTAbits.SYNC = EUSERT_SYNCHRONOUS_MODE;
            BAUDCTLbits.BRG16 = EUSERT_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp=(((_XTAL_FREQ/(float)usart->baudrate)/4)-1);
            break;
        case BAUDRATE_SYN_16BIT:
            TXSTAbits.SYNC = EUSERT_SYNCHRONOUS_MODE;
            BAUDCTLbits.BRG16 = EUSERT_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp=(((_XTAL_FREQ/(float)usart->baudrate)/4)-1);
            break;
        default:
            /*Nothing*/
            break;
    }
    SPBRG=(uint8)((uint32)Baud_Rate_Temp);
    SPBRGH = (uint8) (((uint32) Baud_Rate_Temp) >> 8);
}

static void Eusart_Async_Tx_Init(const usart_t *usart) {
    if (EUSERT_ASYNCHRONOUS_TX_ENABLE == usart->usart_tx_cfg.usart_tx_enable) {
        TXSTAbits.TXEN = EUSERT_ASYNCHRONOUS_TX_ENABLE;
        
#if ESURT_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
        if (EUSERT_ASYNCHRONOUS_TX_INTERRUPT_ENABLE == usart->usart_tx_cfg.usart_tx_interrupt_enable) {
            ESURT_TX_interruptEnable();
            ESURT_TX_interrupt_handler=usart->EUSART_TXDefaultInterruptHandeler;
#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
            INTERRUPT_priorityLevelsEnable();
            if (Interrupt_high_priority == usart->usart_tx_int_priority) {
                INTERRUPT_GlobalInterruptHighEnable();
                ESURT_TX_highpriorityset();
            } else if (interrupt_low_priority == usart->usart_tx_int_priority) {
                INTERRUPT_GlobalInterruptlowEnable();
                ESURT_TX_lowpriorityset();
            } else {
                /*nothing*/
            }
#else 
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
        } else if (EUSERT_ASYNCHRONOUS_TX_INTERRUPT_DISABLE == usart->usart_tx_cfg.usart_tx_interrupt_enable) {
            ESURT_TX_interruptDisable();
        } else {
            /*Nothing*/
        }
#endif


        if (EUSERT_ASYNCHRONOUS_9BIT_TX_ENABLE == usart->usart_tx_cfg.usart_tx_9bit_enable) {
            TXSTAbits.TX9 = EUSERT_ASYNCHRONOUS_9BIT_TX_ENABLE;
        } else if (EUSERT_ASYNCHRONOUS_9BIT_TX_DISABLE == usart->usart_tx_cfg.usart_tx_9bit_enable) {
            TXSTAbits.TX9 = EUSERT_ASYNCHRONOUS_9BIT_TX_DISABLE;
        } else {
            /*Nothing*/
        }
    } else {
        /*Nothing*/
    }
}

static void Eusart_Async_Rx_Init(const usart_t *usart) {
    if (EUSERT_ASYNCHRONOUS_RX_ENABLE == usart->usart_rx_cfg.usart_rx_enable) {
        RCSTAbits.CREN = EUSERT_ASYNCHRONOUS_RX_ENABLE;
#if ESURT_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_feature_ENABLE
        if (EUSERT_ASYNCHRONOUS_RX_INTERRUPT_ENABLE == usart->usart_rx_cfg.usart_rx_interrupt_enable) {
            ESURT_RX_interrupt_handler = usart->EUSART_RXDefaultInterruptHandeler;
            EUSART_FramingError_interrupt_handler = usart->EUSART_FramingErrorHandeler;
            EUSART_OverRunError_interrupt_handler = usart->EUSART_OverRunErrorHandeler;
            ESURT_RX_interruptEnable();
#if INTERRUPT_Priority_Levels_Enable  ==INTERRUPT_feature_ENABLE 
            INTERRUPT_priorityLevelsEnable();
            if (Interrupt_high_priority == usart->usart_rx_int_priority) {
                INTERRUPT_GlobalInterruptHighEnable();
                ESURT_RX_highpriorityset();
            } else if (interrupt_low_priority == usart->usart_rx_int_priority) {
                INTERRUPT_GlobalInterruptlowEnable();
                ESURT_RX_lowpriorityset();
            } else {
                /*nothing*/
            }
#else 
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
        } else if (EUSERT_ASYNCHRONOUS_RX_INTERRUPT_DISABLE == usart->usart_rx_cfg.usart_rx_interrupt_enable) {
            ESURT_RX_interruptDisable();
        } else {
            /*Nothing*/
        }
#endif

        if (EUSERT_ASYNCHRONOUS_9BIT_RX_ENABLE == usart->usart_rx_cfg.usart_rx_9bit_enable) {
            RCSTAbits.RX9 = EUSERT_ASYNCHRONOUS_9BIT_RX_ENABLE;
        } else if (EUSERT_ASYNCHRONOUS_9BIT_RX_DISABLE == usart->usart_rx_cfg.usart_rx_9bit_enable) {
            RCSTAbits.RX9 = EUSERT_ASYNCHRONOUS_9BIT_RX_DISABLE;
        } else {
            /*Nothing*/
        }
    } else {
        /*Nothing*/
    }
}

 void ESURT_TX_ISR()
 {
     ESURT_TX_interruptDisable();
     if(ESURT_TX_interrupt_handler)
     {
         ESURT_TX_interrupt_handler();
     }else {
        /*Nothing*/
    }
 }

void ESURT_RX_ISR() {
    if (ESURT_RX_interrupt_handler) {
        ESURT_RX_interrupt_handler();
    } else {
        /*Nothing*/
    }
    if (EUSART_FramingError_interrupt_handler) {
        EUSART_FramingError_interrupt_handler();
    } else {
        /*Nothing*/
    }
    if (EUSART_OverRunError_interrupt_handler) {
        EUSART_OverRunError_interrupt_handler();
    } else {
        /*Nothing*/
    }
}