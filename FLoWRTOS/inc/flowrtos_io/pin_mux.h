/*
    Copyright (C) 2018 ER2C
    Politektik Elektronika Negeri Surabaya
    Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#ifndef pin_mux_H_
#define pin_mux_H_

#include "device_imx.h"

// UART_Type* base - UART base address 1..6
void configure_uart_pins(UART_Type* base);

// ECSPI_Type* base - ECSPI base address 1..5
void configure_ecspi_pins(ECSPI_Type* base);

// ECSPI_Type* base - ECSPI base address 1..5
void configure_ecspi_slave_pins(ECSPI_Type* base);

// I2C_Type* base - I2C base address 1..4
void configure_i2c_pins(I2C_Type* base);

// CAN_Type* base - CAN base address 1..2
void configure_flexcan_pins(CAN_Type* base);

#endif