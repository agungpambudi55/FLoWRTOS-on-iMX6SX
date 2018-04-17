/*
    Copyright (C) 2018 ER2C
    Politektik Elektronika Negeri Surabaya
    Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#ifndef __GPIO_PINS_H__
#define __GPIO_PINS_H__

#include "device_imx.h"

/* i.MX GPIO initialize structure. */
typedef struct _gpio_config
{
    const char        *name;
    __IO  uint32_t    *muxReg;
    uint32_t           muxConfig;
    __IO  uint32_t    *padReg;
    uint32_t           padConfig;
    GPIO_Type         *base;
    uint32_t           pin;
} gpio_config_t;

#if defined(__cplusplus)
extern "C" {
#endif 

/* GPIO pin configuration */
extern gpio_config_t gpioLed;
extern gpio_config_t gpioSensorAccInt;
extern gpio_config_t gpioSensorMagAlsInt;

/* Configure specific GPIO pin */
void configure_gpio_pin(gpio_config_t *config);

#endif