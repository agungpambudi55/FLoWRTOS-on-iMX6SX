/*
    Copyright (C) 2018 ER2C
    Politektik Elektronika Negeri Surabaya
    Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#include "pin_mux.h"

void configure_uart_pins(UART_Type* base)
{
    switch((uint32_t)base)
    {
        case UART2_BASE:
            // UART2 iomux configuration
            IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO06 = IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO06_MUX_MODE(0);
            IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO07 = IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO07_MUX_MODE(0);
            IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO06 = IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO06_PKE_MASK |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO06_PUE_MASK |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO06_PUS(2)   |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO06_SPEED(2) |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO06_DSE(6)   |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO06_SRE_MASK |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO06_HYS_MASK;
            IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO07 = IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO07_PKE_MASK |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO07_PUE_MASK |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO07_PUS(2)   |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO07_SPEED(2) |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO07_DSE(6)   |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO07_SRE_MASK |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO07_HYS_MASK;
            IOMUXC_UART2_IPP_UART_RXD_MUX_SELECT_INPUT = IOMUXC_UART2_IPP_UART_RXD_MUX_SELECT_INPUT_DAISY(1);
            break;
        case UART5_BASE:

            /* UART5 pin mux configuration */
            IOMUXC_SW_MUX_CTL_PAD_SD4_DATA4 =  IOMUXC_SW_MUX_CTL_PAD_SD4_DATA4_MUX_MODE(2);
            IOMUXC_SW_MUX_CTL_PAD_SD4_DATA5 =  IOMUXC_SW_MUX_CTL_PAD_SD4_DATA5_MUX_MODE(2);
            IOMUXC_SW_PAD_CTL_PAD_SD4_DATA4 =  IOMUXC_SW_PAD_CTL_PAD_SD4_DATA4_PKE_MASK |
                                               IOMUXC_SW_PAD_CTL_PAD_SD4_DATA4_PUE_MASK |
                                               IOMUXC_SW_PAD_CTL_PAD_SD4_DATA4_PUS(2)   |
                                               IOMUXC_SW_PAD_CTL_PAD_SD4_DATA4_SPEED(2) |
                                               IOMUXC_SW_PAD_CTL_PAD_SD4_DATA4_DSE(6)   |
                                               IOMUXC_SW_PAD_CTL_PAD_SD4_DATA4_SRE_MASK |
                                               IOMUXC_SW_PAD_CTL_PAD_SD4_DATA4_HYS_MASK;
            IOMUXC_SW_PAD_CTL_PAD_SD4_DATA5 =  IOMUXC_SW_PAD_CTL_PAD_SD4_DATA5_PKE_MASK |
                                               IOMUXC_SW_PAD_CTL_PAD_SD4_DATA5_PUE_MASK |
                                               IOMUXC_SW_PAD_CTL_PAD_SD4_DATA5_PUS(2)   |
                                               IOMUXC_SW_PAD_CTL_PAD_SD4_DATA5_SPEED(2) |
                                               IOMUXC_SW_PAD_CTL_PAD_SD4_DATA5_DSE(6)   |
                                               IOMUXC_SW_PAD_CTL_PAD_SD4_DATA5_SRE_MASK |
                                               IOMUXC_SW_PAD_CTL_PAD_SD4_DATA5_HYS_MASK;
            IOMUXC_UART5_IPP_UART_RXD_MUX_SELECT_INPUT = IOMUXC_UART5_IPP_UART_RXD_MUX_SELECT_INPUT_DAISY(0);
        default:
            break;
    }
}

void configure_ecspi_pins(ECSPI_Type* base)
{
    switch((uint32_t)base)
    {
        case ECSPI4_BASE:
            /* daisy chain selection */
            IOMUXC_ECSPI4_IPP_CSPI_CLK_IN_SELECT_INPUT = IOMUXC_ECSPI4_IPP_CSPI_CLK_IN_SELECT_INPUT_DAISY_MASK;
            IOMUXC_ECSPI4_IPP_IND_MISO_SELECT_INPUT = IOMUXC_ECSPI4_IPP_IND_MISO_SELECT_INPUT_DAISY_MASK;
            IOMUXC_ECSPI4_IPP_IND_MOSI_SELECT_INPUT = IOMUXC_ECSPI4_IPP_IND_MOSI_SELECT_INPUT_DAISY_MASK;

            /* iomux */
            IOMUXC_SW_MUX_CTL_PAD_SD2_CLK = IOMUXC_SW_MUX_CTL_PAD_SD2_CLK_MUX_MODE(3);    /* ECSPI SLK  */
            IOMUXC_SW_MUX_CTL_PAD_SD2_CMD = IOMUXC_SW_MUX_CTL_PAD_SD2_CMD_MUX_MODE(3);    /* ECSPI MOSI */
            IOMUXC_SW_MUX_CTL_PAD_SD2_DATA0 = IOMUXC_SW_MUX_CTL_PAD_SD2_DATA0_MUX_MODE(6);  /* ECSPI SS3  */
            IOMUXC_SW_MUX_CTL_PAD_SD2_DATA3 = IOMUXC_SW_MUX_CTL_PAD_SD2_DATA3_MUX_MODE(3);  /* ECSPI MISO */

            /* pad control */
            IOMUXC_SW_PAD_CTL_PAD_SD2_CLK = IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_PKE_MASK |
                                            IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_PUE_MASK |
                                            IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_PUS(0)   |
                                            IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_SPEED(2) |
                                            IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_DSE(6)   |
                                            IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_SRE_MASK |
                                            IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_HYS_MASK;
            IOMUXC_SW_PAD_CTL_PAD_SD2_CMD = IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_SPEED(2) |
                                            IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_DSE(6)   |
                                            IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_SRE_MASK |
                                            IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_HYS_MASK;
            IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0 = IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0_SPEED(2) |
                                              IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0_DSE(6)   |
                                              IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0_SRE_MASK |
                                              IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0_HYS_MASK;
            IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3 = IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_SPEED(2) |
                                              IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_DSE(6)   |
                                              IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_SRE_MASK |
                                              IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_HYS_MASK;
            break;
        default:
            break;
    }
}

void configure_ecspi_slave_pins(ECSPI_Type* base)
{
    switch((uint32_t)base)
    {
        case ECSPI4_BASE:
            /* daisy chain selection */
            IOMUXC_ECSPI4_IPP_CSPI_CLK_IN_SELECT_INPUT = IOMUXC_ECSPI4_IPP_CSPI_CLK_IN_SELECT_INPUT_DAISY_MASK;
            IOMUXC_ECSPI4_IPP_IND_MISO_SELECT_INPUT = IOMUXC_ECSPI4_IPP_IND_MISO_SELECT_INPUT_DAISY_MASK;
            IOMUXC_ECSPI4_IPP_IND_MOSI_SELECT_INPUT = IOMUXC_ECSPI4_IPP_IND_MOSI_SELECT_INPUT_DAISY_MASK;

            /* iomux */
            IOMUXC_SW_MUX_CTL_PAD_SD2_CLK = IOMUXC_SW_MUX_CTL_PAD_SD2_CLK_MUX_MODE(3);    /* ECSPI SLK  */
            IOMUXC_SW_MUX_CTL_PAD_SD2_CMD = IOMUXC_SW_MUX_CTL_PAD_SD2_CMD_MUX_MODE(3);    /* ECSPI MOSI */
            IOMUXC_SW_MUX_CTL_PAD_SD2_DATA0 = IOMUXC_SW_MUX_CTL_PAD_SD2_DATA0_MUX_MODE(6);  /* ECSPI SS3  */
            IOMUXC_SW_MUX_CTL_PAD_SD2_DATA3 = IOMUXC_SW_MUX_CTL_PAD_SD2_DATA3_MUX_MODE(3);  /* ECSPI MISO */

            /* pad control */
            IOMUXC_SW_PAD_CTL_PAD_SD2_CLK = IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_SPEED(2) |
                                            IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_DSE(6)   |
                                            IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_SRE_MASK |
                                            IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_HYS_MASK;
            IOMUXC_SW_PAD_CTL_PAD_SD2_CMD = IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_SPEED(2) |
                                            IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_DSE(6)   |
                                            IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_SRE_MASK |
                                            IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_HYS_MASK;
            IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0 = IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0_SPEED(2) |
                                              IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0_DSE(6)   |
                                              IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0_SRE_MASK |
                                              IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0_HYS_MASK;
            IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3 = IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_SPEED(2) |
                                              IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_DSE(6)   |
                                              IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_SRE_MASK |
                                              IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_HYS_MASK;
            break;
        default:
            break;
    }
}

void configure_i2c_pins(I2C_Type* base)
{
    switch((uint32_t)base)
    {
        case I2C1_BASE:
            // I2C1 iomux configuration
            IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO00 = IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO00_MUX_MODE(0) |
                                               IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO00_SION_MASK;
            IOMUXC_I2C1_IPP_SCL_IN_SELECT_INPUT = IOMUXC_UART1_IPP_UART_RXD_MUX_SELECT_INPUT_DAISY(1);
            IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO01 = IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO01_MUX_MODE(0) |
                                               IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO01_SION_MASK;
            IOMUXC_I2C1_IPP_SDA_IN_SELECT_INPUT = IOMUXC_I2C1_IPP_SDA_IN_SELECT_INPUT_DAISY_MASK;

            IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO00 = IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO00_PKE_MASK  |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO00_PUE_MASK  |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO00_PUS(2)    |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO00_SPEED(2)  |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO00_DSE(6)    |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO00_ODE_SHIFT |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO00_SRE_MASK  |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO00_HYS_MASK;

            IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO01 = IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO01_PKE_MASK  |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO01_PUE_MASK  |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO01_PUS(2)    |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO01_SPEED(2)  |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO01_DSE(6)    |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO01_ODE_SHIFT |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO01_SRE_MASK  |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO01_HYS_MASK;
            break;
        case I2C2_BASE:
            // I2C2 iomux configuration
            IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO02 = IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO02_MUX_MODE(0) |
                                               IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO02_SION_MASK;
            IOMUXC_I2C2_IPP_SCL_IN_SELECT_INPUT = IOMUXC_I2C2_IPP_SCL_IN_SELECT_INPUT_DAISY(1);
            IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 = IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03_MUX_MODE(0) |
                                               IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03_SION_MASK;
            IOMUXC_I2C2_IPP_SDA_IN_SELECT_INPUT = IOMUXC_I2C2_IPP_SDA_IN_SELECT_INPUT_DAISY(1);

            IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO02 = IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO02_PKE_MASK  |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO02_PUE_MASK  |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO02_PUS(2)    |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO02_SPEED(2)  |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO02_DSE(6)    |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO02_ODE_SHIFT |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO02_SRE_MASK  |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO02_HYS_MASK;

            IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 = IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03_PKE_MASK  |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03_PUE_MASK  |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03_PUS(2)    |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03_SPEED(2)  |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03_DSE(6)    |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03_ODE_SHIFT |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03_SRE_MASK  |
                                               IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03_HYS_MASK;
            break;
        case I2C3_BASE:
            // I2C3 iomux configuration
            IOMUXC_SW_MUX_CTL_PAD_KEY_COL4 = IOMUXC_SW_MUX_CTL_PAD_KEY_COL4_MUX_MODE(2) |
                                             IOMUXC_SW_MUX_CTL_PAD_KEY_COL4_SION_MASK;
            IOMUXC_I2C3_IPP_SCL_IN_SELECT_INPUT = IOMUXC_I2C3_IPP_SCL_IN_SELECT_INPUT_DAISY(2);
            IOMUXC_SW_MUX_CTL_PAD_KEY_ROW4 = IOMUXC_SW_MUX_CTL_PAD_KEY_ROW4_MUX_MODE(2) |
                                             IOMUXC_SW_MUX_CTL_PAD_KEY_ROW4_SION_MASK;
            IOMUXC_I2C3_IPP_SDA_IN_SELECT_INPUT = IOMUXC_I2C3_IPP_SDA_IN_SELECT_INPUT_DAISY(2);

            IOMUXC_SW_PAD_CTL_PAD_KEY_COL4 = IOMUXC_SW_PAD_CTL_PAD_KEY_COL4_PKE_MASK  |
                                             IOMUXC_SW_PAD_CTL_PAD_KEY_COL4_PUE_MASK  |
                                             IOMUXC_SW_PAD_CTL_PAD_KEY_COL4_PUS(2)    |
                                             IOMUXC_SW_PAD_CTL_PAD_KEY_COL4_SPEED(2)  |
                                             IOMUXC_SW_PAD_CTL_PAD_KEY_COL4_DSE(6)    |
                                             IOMUXC_SW_PAD_CTL_PAD_KEY_COL4_ODE_SHIFT |
                                             IOMUXC_SW_PAD_CTL_PAD_KEY_COL4_SRE_MASK  |
                                             IOMUXC_SW_PAD_CTL_PAD_KEY_COL4_HYS_MASK;

            IOMUXC_SW_PAD_CTL_PAD_KEY_ROW4 = IOMUXC_SW_PAD_CTL_PAD_KEY_ROW4_PKE_MASK  |
                                             IOMUXC_SW_PAD_CTL_PAD_KEY_ROW4_PUE_MASK  |
                                             IOMUXC_SW_PAD_CTL_PAD_KEY_ROW4_PUS(2)    |
                                             IOMUXC_SW_PAD_CTL_PAD_KEY_ROW4_SPEED(2)  |
                                             IOMUXC_SW_PAD_CTL_PAD_KEY_ROW4_DSE(6)    |
                                             IOMUXC_SW_PAD_CTL_PAD_KEY_ROW4_ODE_SHIFT |
                                             IOMUXC_SW_PAD_CTL_PAD_KEY_ROW4_SRE_MASK  |
                                             IOMUXC_SW_PAD_CTL_PAD_KEY_ROW4_HYS_MASK;
            break;
        case I2C4_BASE:
            // I2C4 iomux configuration
            IOMUXC_SW_MUX_CTL_PAD_CSI_DATA06 = IOMUXC_SW_MUX_CTL_PAD_CSI_DATA06_MUX_MODE(2) |
                                               IOMUXC_SW_MUX_CTL_PAD_CSI_DATA06_SION_MASK;
            IOMUXC_I2C4_IPP_SCL_IN_SELECT_INPUT = IOMUXC_I2C4_IPP_SCL_IN_SELECT_INPUT_DAISY(2);
            IOMUXC_SW_MUX_CTL_PAD_CSI_DATA07 = IOMUXC_SW_MUX_CTL_PAD_CSI_DATA07_MUX_MODE(2) |
                                               IOMUXC_SW_MUX_CTL_PAD_CSI_DATA07_SION_MASK;
            IOMUXC_I2C4_IPP_SDA_IN_SELECT_INPUT = IOMUXC_I2C4_IPP_SDA_IN_SELECT_INPUT_DAISY(2);

            IOMUXC_SW_PAD_CTL_PAD_CSI_DATA06 = IOMUXC_SW_PAD_CTL_PAD_CSI_DATA06_PKE_MASK  |
                                               IOMUXC_SW_PAD_CTL_PAD_CSI_DATA06_PUE_MASK  |
                                               IOMUXC_SW_PAD_CTL_PAD_CSI_DATA06_PUS(2)    |
                                               IOMUXC_SW_PAD_CTL_PAD_CSI_DATA06_SPEED(2)  |
                                               IOMUXC_SW_PAD_CTL_PAD_CSI_DATA06_DSE(6)    |
                                               IOMUXC_SW_PAD_CTL_PAD_CSI_DATA06_ODE_SHIFT |
                                               IOMUXC_SW_PAD_CTL_PAD_CSI_DATA06_SRE_MASK  |
                                               IOMUXC_SW_PAD_CTL_PAD_CSI_DATA06_HYS_MASK;

            IOMUXC_SW_PAD_CTL_PAD_CSI_DATA07 = IOMUXC_SW_PAD_CTL_PAD_CSI_DATA07_PKE_MASK  |
                                               IOMUXC_SW_PAD_CTL_PAD_CSI_DATA07_PUE_MASK  |
                                               IOMUXC_SW_PAD_CTL_PAD_CSI_DATA07_PUS(2)    |
                                               IOMUXC_SW_PAD_CTL_PAD_CSI_DATA07_SPEED(2)  |
                                               IOMUXC_SW_PAD_CTL_PAD_CSI_DATA07_DSE(6)    |
                                               IOMUXC_SW_PAD_CTL_PAD_CSI_DATA07_ODE_SHIFT |
                                               IOMUXC_SW_PAD_CTL_PAD_CSI_DATA07_SRE_MASK  |
                                               IOMUXC_SW_PAD_CTL_PAD_CSI_DATA07_HYS_MASK;
            break;
        default:
            break;
    }
}

void configure_flexcan_pins(CAN_Type* base)
{
    volatile GPIO_MemMapPtr gpio2_pdir;
    void   *addr;

    switch((uint32_t)base)
    {
        case CAN1_BASE:
            // CAN1_2_STBY_B DRIVE LOW
            IOMUXC_SW_MUX_CTL_PAD_QSPI1B_DATA3 = IOMUXC_SW_MUX_CTL_PAD_QSPI1B_DATA3_MUX_MODE(5);
            IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DATA3 = IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DATA3_HYS_MASK|
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DATA3_DSE(6)  |
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DATA3_SPEED(2)|
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DATA3_PKE_MASK|
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DATA3_PUE_MASK|
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DATA3_PUS(2);
            IOMUXC_SW_MUX_CTL_PAD_KEY_ROW4 = IOMUXC_SW_MUX_CTL_PAD_KEY_ROW4_MUX_MODE(5);
            IOMUXC_SW_PAD_CTL_PAD_KEY_ROW4 = IOMUXC_SW_PAD_CTL_PAD_KEY_ROW4_HYS_MASK|
                                             IOMUXC_SW_PAD_CTL_PAD_KEY_ROW4_DSE(6)  |
                                             IOMUXC_SW_PAD_CTL_PAD_KEY_ROW4_SPEED(2)|
                                             IOMUXC_SW_PAD_CTL_PAD_KEY_ROW4_PKE_MASK|
                                             IOMUXC_SW_PAD_CTL_PAD_KEY_ROW4_PUE_MASK|
                                             IOMUXC_SW_PAD_CTL_PAD_KEY_ROW4_PUS(2);
            addr = (void *) GPIO2_BASE_PTR;
            gpio2_pdir = addr;
            gpio2_pdir->GDIR |= 0x08000000;
            gpio2_pdir->DR &= ~0x08000000;

            // CAN1_TX
            IOMUXC_SW_MUX_CTL_PAD_QSPI1B_DQS = IOMUXC_SW_MUX_CTL_PAD_QSPI1B_DQS_MUX_MODE(1);
            IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DQS = IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DQS_HYS_MASK |
                                               IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DQS_DSE(6)   |
                                               IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DQS_SPEED(2) |
                                               IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DQS_PKE_MASK |
                                               IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DQS_PUE_MASK |
                                               IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DQS_PUS(2);

            // CAN1_RX
            IOMUXC_SW_MUX_CTL_PAD_QSPI1A_SS1_B = IOMUXC_SW_MUX_CTL_PAD_QSPI1A_SS1_B_MUX_MODE(1);
            IOMUXC_CAN1_IPP_IND_CANRX_SELECT_INPUT = IOMUXC_CAN1_IPP_IND_CANRX_SELECT_INPUT_DAISY(2);
            IOMUXC_SW_PAD_CTL_PAD_QSPI1A_SS1_B = IOMUXC_SW_PAD_CTL_PAD_QSPI1A_SS1_B_HYS_MASK|
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1A_SS1_B_DSE(6)  |
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1A_SS1_B_SPEED(2)|
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1A_SS1_B_PKE_MASK|
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1A_SS1_B_PUE_MASK|
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1A_SS1_B_PUS(2);

            break;
        case CAN2_BASE:
            // CAN1_2_STBY_B DRIVE LOW
            IOMUXC_SW_MUX_CTL_PAD_QSPI1B_DATA3 = IOMUXC_SW_MUX_CTL_PAD_QSPI1B_DATA3_MUX_MODE(5);
            IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DATA3 = IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DATA3_HYS_MASK|
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DATA3_DSE(6)  |
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DATA3_SPEED(2)|
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DATA3_PKE_MASK|
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DATA3_PUE_MASK|
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DATA3_PUS(2);
            addr = (void *) GPIO2_BASE_PTR;
            gpio2_pdir = addr;
            gpio2_pdir->GDIR |= 0x08000000;
            gpio2_pdir->DR &= ~0x08000000;

            // CAN2_TX
            IOMUXC_SW_MUX_CTL_PAD_QSPI1A_DQS = IOMUXC_SW_MUX_CTL_PAD_QSPI1A_DQS_MUX_MODE(1);
            IOMUXC_SW_PAD_CTL_PAD_QSPI1A_DQS = IOMUXC_SW_PAD_CTL_PAD_QSPI1A_DQS_HYS_MASK|
                                               IOMUXC_SW_PAD_CTL_PAD_QSPI1A_DQS_DSE(6)  |
                                               IOMUXC_SW_PAD_CTL_PAD_QSPI1A_DQS_SPEED(2)|
                                               IOMUXC_SW_PAD_CTL_PAD_QSPI1A_DQS_PKE_MASK|
                                               IOMUXC_SW_PAD_CTL_PAD_QSPI1A_DQS_PUE_MASK|
                                               IOMUXC_SW_PAD_CTL_PAD_QSPI1A_DQS_PUS(2);

            // CAN2_RX
            IOMUXC_SW_MUX_CTL_PAD_QSPI1B_SS1_B = IOMUXC_SW_MUX_CTL_PAD_QSPI1B_SS1_B_MUX_MODE(1);
            IOMUXC_CAN2_IPP_IND_CANRX_SELECT_INPUT = IOMUXC_CAN2_IPP_IND_CANRX_SELECT_INPUT_DAISY(2);
            IOMUXC_SW_PAD_CTL_PAD_QSPI1B_SS1_B = IOMUXC_SW_PAD_CTL_PAD_QSPI1B_SS1_B_HYS_MASK|
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1B_SS1_B_DSE(6)  |
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1B_SS1_B_SPEED(2)|
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1B_SS1_B_PKE_MASK|
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1B_SS1_B_PUE_MASK|
                                                 IOMUXC_SW_PAD_CTL_PAD_QSPI1B_SS1_B_PUS(2);
            break;
    }
}