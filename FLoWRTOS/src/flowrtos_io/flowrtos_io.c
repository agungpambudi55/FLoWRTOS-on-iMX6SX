/*
    Copyright (C) 2018 ER2C
    Politektik Elektronika Negeri Surabaya
    Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#include "flowrtos_io.h"

// Initialize clock base on board configuration
void BOARD_ClockInit(void){
    /* OSC/PLL is already initialized by Cortex-A9 (u-boot) */
    /* Disable WDOG3 */
    WDOG_DisablePowerdown(BOARD_WDOG_BASEADDR);

    /* Enable clock gate for IP bridge and IO mux */
    CCM_ControlGate(CCM, ccmCcgrGateIomuxIptClkIo, ccmClockNeededAll);  // iomuxc
    CCM_ControlGate(CCM, ccmCcgrGateIpmux1Clk, ccmClockNeededAll);      // ipmux 1
    CCM_ControlGate(CCM, ccmCcgrGateIpmux2Clk, ccmClockNeededAll);      // ipmux 2
    CCM_ControlGate(CCM, ccmCcgrGateIpmux3Clk, ccmClockNeededAll);      // ipmux 3
}

// Initialize debug console
void dbg_uart_init(void){
    /* Set debug uart for M4 core domain access only */
    RDC_SetPdapAccess(RDC, BOARD_DEBUG_UART_RDC_PDAP, 3 << (BOARD_DOMAIN_ID * 2), false, false);
    RDC_SetPdapAccess(RDC, BOARD_PLAN_UART_RDC_PDAP, 3 << (BOARD_DOMAIN_ID * 2), false, false);

    /* Select board debug clock derived from OSC clock(24M) */
    CCM_SetRootMux(CCM, ccmRootUartClkSel, ccmRootmuxUartClkOsc24m);
    /* Set relevant divider = 1. */
    CCM_SetRootDivider(CCM, ccmRootUartClkPodf, 0);
    /* Enable debug uart clock */
    CCM_ControlGate(CCM, ccmCcgrGateUartClk, ccmClockNeededAll);
    CCM_ControlGate(CCM, ccmCcgrGateUartSerialClk, ccmClockNeededAll);

    /* Configure the pin IOMUX */
    configure_uart_pins(BOARD_DEBUG_UART_BASEADDR);
    configure_uart_pins(BOARD_PLAN_UART_BASEADDR);

    DbgConsole_Init(BOARD_DEBUG_UART_BASEADDR, 24000000, 115200);
    DbgConsole_Init(BOARD_PLAN_UART_BASEADDR, 24000000, 115200);
}

// Initialize UART5 for TX to DXL and RX from IMU
// TX for dxl ax-18x
// RX for imu gy-521 
void uart_init_UART5(){
    // Setup UART init structure
    uart_init_config_t initConfig = {
        .baudRate   = 57600,
        .wordLength = uartWordLength8Bits,
        .stopBitNum = uartStopBitNumOne,
        .parity     = uartParityDisable,
        .direction  = uartDirectionTxRx
    };

    // Get current module clock frequency.
    initConfig.clockRate  = get_uart_clock_freq(BOARD_PLAN_UART_BASEADDR);

    /* Initialize UART baud rate, bit count, parity, stop bit and direction. */
    UART_Init(BOARD_PLAN_UART_BASEADDR, &initConfig);

    /* Set UART build-in hardware FIFO Watermark. */
    UART_SetTxFifoWatermark(BOARD_PLAN_UART_BASEADDR, 16);
    UART_SetRxFifoWatermark(BOARD_PLAN_UART_BASEADDR, 1);

    /* Finally, enable the UART module */
    UART_Enable(BOARD_PLAN_UART_BASEADDR);
}

// Initialize RDC
void BOARD_RdcInit(void){
    /* first move M4 core to RDC domain 1 */
    RDC_SetDomainID(RDC, rdcMdaM4, BOARD_DOMAIN_ID, false);
}

// Initialize I/O
void management_io(void){
    /* Board specific RDC settings */
    BOARD_RdcInit();

    /* Board specific clock settings */
    BOARD_ClockInit();

    /* Initialize debug uart */
    dbg_uart_init();

    /* Initialize UART 5*/
    uart_init_UART5();

    /* In this example, we need to grasp board EPIT exclusively */
    RDC_SetPdapAccess(RDC, BOARD_EPITA_RDC_PDAP, 3 << (BOARD_DOMAIN_ID * 2), false, false);

    /* Select EPIT clock derived from OSC 24M */
    CCM_SetRootMux(CCM, BOARD_EPIT_CCM_ROOT, ccmRootmuxPerclkClkOsc24m);
    /* Set relevant divider = 1. */
    CCM_SetRootDivider(CCM, BOARD_EPIT_CCM_DIV, 0);

    /* Enable clock used by EPITA */
    CCM_ControlGate(CCM, BOARD_EPITA_CCM_CCGR, ccmClockNeededAll);

    PRINTF("#Initialization management I/O success\n\r");
}