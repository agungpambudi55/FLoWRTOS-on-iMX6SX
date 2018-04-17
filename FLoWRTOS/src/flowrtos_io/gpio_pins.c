/*
    Copyright (C) 2018 ER2C
    Politektik Elektronika Negeri Surabaya
    Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#include <assert.h>
#include "gpio_pins.h"

gpio_config_t gpioLed = {
    "DEBUG_LED",                                    /* name */
    &IOMUXC_SW_MUX_CTL_PAD_CSI_PIXCLK,              /* muxReg */
    5,                                              /* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_CSI_PIXCLK,              /* padReg */
    IOMUXC_SW_PAD_CTL_PAD_CSI_DATA05_DSE(6)|        /* padConfig */
	IOMUXC_SW_PAD_CTL_PAD_CSI_DATA05_SPEED(2)|
	IOMUXC_SW_PAD_CTL_PAD_CSI_DATA05_PKE_MASK,
    GPIO1,                                          /* base */
    24                                              /* pin */
};

gpio_config_t gpioSensorAccInt = {
    "SensorAccInt",                                 /* name */
    &IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA23,             /* muxReg */
    5,                                              /* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA23,             /* padReg */
    IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA23_PUS(2) |      /* padConfig */
    IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA23_PUE_MASK |
    IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA23_PKE_MASK |
    IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA23_SPEED(2) |
    IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA23_DSE(6),
    GPIO3,                                          /* base */
    24                                              /* pin */
};

gpio_config_t gpioSensorMagAlsInt = {
    "SensorMagAlsInt",                              /* name */
    &IOMUXC_SW_MUX_CTL_PAD_SD2_CLK,                 /* muxReg */
    5,                                              /* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_SD2_CLK,                 /* padReg */
    IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_PUS(2) |          /* padConfig */
    IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_PUE_MASK |
    IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_PKE_MASK |
    IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_SPEED(2) |
    IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_DSE(6),
    GPIO6,                                          /* base */
    6                                               /* pin */
};

void configure_gpio_pin(gpio_config_t *config)
{
    assert(config);

    *(config->muxReg) = config->muxConfig;
    *(config->padReg) = config->padConfig;
}