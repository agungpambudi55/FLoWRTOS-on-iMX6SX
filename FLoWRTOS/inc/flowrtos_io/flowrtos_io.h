/*
    Copyright (C) 2018 ER2C
    Politektik Elektronika Negeri Surabaya
    Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#if !defined(__FLOWRTOS_IO_H__)
#define __FLOWRTOS_IO__

#include "flowrtos.h"

/* The board name */
#define BOARD_NAME                            "IMX6SX_AI_M4"
#define BOARD_DOMAIN_ID                       (1)

/* ADC information for this board */
// #define BOARD_ADC_RDC_PDAP                    rdcPdapAdc1
// #define BOARD_ADC_BASEADDR                    ADC1
// #define BOARD_ADC_IRQ_NUM                     ADC1_IRQn
// #define BOARD_ADC_HANDLER                     ADC1_Handler
// #define BOARD_ADC_INPUT_CHANNEL               (3)

// deklarasi INT untuk scheduling
#define scheduler_IRQ_NUM					  ADC1_IRQn
#define scheduler                     		  ADC1_Handler

/* WDOG information for this board */
#define BOARD_WDOG_RDC_PDAP                   rdcPdapWdog3
#define BOARD_WDOG_BASEADDR                   WDOG3
#define BOARD_WDOG_IRQ_NUM                    WDOG3_IRQn
#define BOARD_WDOG_HANDLER                    WDOG3_Handler

/* SEMA4 information for this board */
#define BOARD_SEMA4_RDC_PDAP                  rdcPdapSema4
#define BOARD_SEMA4_BASEADDR                  SEMA4
#define BOARD_SEMA4_IRQ_NUM                   SEMA4_CP1_IRQn
#define BOARD_SEMA4_HANDLER                   SEMA4_CP1_Handler

/* SENSOR information for this board */
#define BOARD_SENSOR_MMA8451Q_INT             (0x1)
#define BOARD_AI_SENSOR_MAG3110               (1)

/* GPIO information for this board */
#define BOARD_GPIO_LED_RDC_PDAP               rdcPdapGpio1
#define BOARD_GPIO_LED_CONFIG                 (&gpioLed)

#define BOARD_GPIO_SENSOR_ACC_RDC_PDAP        rdcPdapGpio3
#define BOARD_GPIO_SENSOR_ACC_CONFIG          (&gpioSensorAccInt)
#define BOARD_GPIO_SENSOR_ACC_IRQ_NUM         GPIO3_INT31_16_IRQn
#define BOARD_GPIO_SENSOR_ACC_HANDLER         GPIO3_Combined_16_31_Handler

#define BOARD_GPIO_SENSOR_MAG_ALS_RDC_PDAP    rdcPdapGpio6
#define BOARD_GPIO_SENSOR_MAG_ALS_CONFIG      (&gpioSensorMagAlsInt)
#define BOARD_GPIO_SENSOR_MAG_ALS_IRQ_NUM     GPIO6_INT15_0_IRQn
#define BOARD_GPIO_SENSOR_MAG_ALS_HANDLER     GPIO6_Combined_0_15_Handler

/* Debug UART information for this board 2 */
#define BOARD_DEBUG_UART_RDC_PDAP             rdcPdapUart2
#define BOARD_DEBUG_UART_CCM_ROOT             ccmRootUartClkSel
#define BOARD_DEBUG_UART_CCM_DIV              ccmRootUartClkPodf
#define BOARD_DEBUG_UART_CCM_CCGR             ccmCcgrGateUartClk
#define BOARD_DEBUG_UART_CCM_CCGR_SERIAL      ccmCcgrGateUartSerialClk
#define BOARD_DEBUG_UART_BASEADDR             UART2
#define BOARD_DEBUG_UART_IRQ_NUM              UART2_IRQn
#define BOARD_DEBUG_UART_HANDLER              UART2_Handler

/* UART 5 information board dxl */
#define BOARD_PLAN_UART_RDC_PDAP         	  rdcPdapUart5
#define BOARD_PLAN_UART_CCM_ROOT              ccmRootUartClkSel
#define BOARD_PLAN_UART_CCM_DIV          	  ccmRootUartClkPodf
#define BOARD_PLAN_UART_CCM_CCGR         	  ccmCcgrGateUartClk
#define BOARD_PLAN_UART_CCM_CCGR_SERIAL  	  ccmCcgrGateUartSerialClk
#define BOARD_PLAN_UART_BASEADDR         	  UART5
#define BOARD_PLAN_UART_IRQ_NUM          	  UART5_IRQn
#define BOARD_PLAN_UART_HANDLER          	  UART5_Handler

/* MU information for this board*/
#define BOARD_MU_HANDLER                      MU_M4_Handler
#define BOARD_MU_IRQ_NUM                      MU_M4_IRQn
#define BOARD_MU_BASE_ADDR                    MUB
#define BOARD_MU_RDC_PDAP                     rdcPdapMuB

/* ECSPI information for master mode */
#define BOARD_ECSPI_MASTER_RDC_PDAP           rdcPdapEcspi4
#define BOARD_ECSPI_MASTER_CCM_ROOT           ccmRootEcspiClkSel
#define BOARD_ECSPI_MASTER_CCM_DIV            ccmRootEcspiClkPodf
#define BOARD_ECSPI_MASTER_CCM_CCGR           ccmCcgrGateEcspi4Clk
#define BOARD_ECSPI_MASTER_BASEADDR           ECSPI4
#define BOARD_ECSPI_MASTER_CHANNEL            ecspiSelectChannel3
#define BOARD_ECSPI_MASTER_IRQ_NUM            eCSPI4_IRQn
#define BOARD_ECSPI_MASTER_HANDLER            eCSPI4_Handler

/* I2C information for this board */
#define BOARD_I2C_RDC_PDAP                    rdcPdapI2c3
#define BOARD_I2C_CCM_ROOT                    ccmRootPerclkClkSel
#define BOARD_I2C_CCM_DIV                     ccmRootPerclkPodf
#define BOARD_I2C_CCM_CCGR                    ccmCcgrGateI2c3Serialclk
#define BOARD_I2C_BASEADDR                    I2C3
#define BOARD_I2C_IRQ_NUM                     I2C3_IRQn
#define BOARD_I2C_HANDLER                     I2C3_Handler
#define BOARD_I2C_MMA8451Q_ADDR               (0x1C)
#define BOARD_I2C_MAG3110_ADDR                (0x0E)
#define BOARD_I2C_MAX7310_ADDR                (0x32)

/* EPIT common information for this board */
#define BOARD_EPIT_CCM_ROOT                   ccmRootPerclkClkSel
#define BOARD_EPIT_CCM_DIV                    ccmRootPerclkPodf
/* EPIT instance A information for this board */
#define BOARD_EPITA_RDC_PDAP                  rdcPdapEpit1
#define BOARD_EPITA_CCM_CCGR                  ccmCcgrGateEpit1Clk
#define BOARD_EPITA_BASEADDR                  EPIT1
#define BOARD_EPITA_IRQ_NUM                   EPIT1_IRQn
#define BOARD_EPITA_HANDLER                   EPIT1_Handler
/* EPIT instance B information for this board */
#define BOARD_EPITB_RDC_PDAP                  rdcPdapEpit2
#define BOARD_EPITB_CCM_CCGR                  ccmCcgrGateEpit2Clk
#define BOARD_EPITB_BASEADDR                  EPIT2
#define BOARD_EPITB_IRQ_NUM                   EPIT2_IRQn
#define BOARD_EPITB_HANDLER                   EPIT2_Handler

/* FlexCAN information for this board */
#define BOARD_FLEXCAN_CCM_ROOT                ccmRootCanClkSel
#define BOARD_FLEXCAN_CCM_CCGR                ccmCcgrGateCan1Clk
#define BOARD_FLEXCAN_CCM_CCGR_SERIAL         ccmCcgrGateCan1SerialClk
#define BOARD_FLEXCAN_CCM_DIV                 ccmRootCanClkPodf
#define BOARD_FLEXCAN_RDC_PDAP                rdcPdapCan1
#define BOARD_FLEXCAN_BASEADDR                CAN1
#define BOARD_FLEXCAN_IRQ_NUM                 FLEXCAN1_IRQn
#define BOARD_FLEXCAN_HANDLER                 FLEXCAN1_Handler

#if defined(__cplusplus)
extern "C" {
#endif

// Initialize I/O
void management_io(void);
void dbg_uart_init(void);
void uart_init_UART5();

/* Function to initialize clock base on board configuration. */
void BOARD_ClockInit(void);
void BOARD_RdcInit(void);

#if defined(__cplusplus)
}
#endif

#endif
