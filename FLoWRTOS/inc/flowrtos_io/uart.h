/*
    Copyright (C) 2018 ER2C
    Politektik Elektronika Negeri Surabaya
    Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#ifndef FLOWRTOS_UART_H
#define FLOWRTOS_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "flowrtos.h"

typedef struct _uart_state {
    const uint8_t*    txBuff;          /*!< The buffer of data being sent.*/
    uint8_t*          rxBuff;          /*!< The buffer of received data. */
    volatile uint32_t txSize;          /*!< The remaining number of bytes to be transmitted. */
    volatile uint32_t rxSize;          /*!< The remaining number of bytes to be received. */
    volatile bool     isTxBusy;        /*!< True if there is an active transmit. */
    volatile bool     isRxBusy;        /*!< True if there is an active receive. */
} uart_state_t;

const uint8_t buffStart[] = "\n\r++++++++++++++++ UART Send/Receive by INT +++++++++++++++++\n\r";
const uint8_t bufferData[] = "\n\rType characters from keyboard then echo them to terminal screen\n\r";

/* Uart runtime state structure */
static uart_state_t uartState;

static void test_uart(void);
static void UART_XFER_Config(uart_init_config_t* initConfig);
static bool UART_XFER_Write(uint8_t* txBuffer, uint32_t length);
static uint32_t UART_XFER_GetWriteStatus(void);
static bool UART_XFER_Read(uint8_t* rxBuffer, uint32_t length);
static uint32_t UART_XFER_GetReadStatus(void);

#ifdef __cplusplus
}
#endif
#endif
