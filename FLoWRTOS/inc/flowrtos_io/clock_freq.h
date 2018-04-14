/*
    Copyright (C) 2018 ER2C
    Politektik Elektronika Negeri Surabaya
    Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#ifndef __CLOCK_FREQ_H__
#define __CLOCK_FREQ_H__

#include "device_imx.h"

#if defined(__cplusplus)
extern "C" {
#endif

uint32_t get_epit_clock_freq(EPIT_Type* base);	// clock frequency (in HZ)

uint32_t get_i2c_clock_freq(I2C_Type* base);	// clock frequency (in HZ)

uint32_t get_ecspi_clock_freq(ECSPI_Type* base);// clock frequency (in HZ)

uint32_t get_uart_clock_freq(UART_Type* base);	// clock frequency (in HZ)

#if defined(__cplusplus)
}
#endif

#endif