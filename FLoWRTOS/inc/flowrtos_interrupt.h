/*
    Copyright (C) 2018 ER2C
    Politektik Elektronika Negeri Surabaya
    Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#ifndef FLOWRTOS_INTERRUPT_H
#define FLOWRTOS_INTERRUPT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "flowrtos.h"	

// INT yg dipakai sistem :
// - EPIT1_IRQn untuk manajemen waktu
// - UART1_IRQn untuk debug A9
// - UART2_IRQn untuk debug M4
//
// INT yg dipakai pengguna :
// - UART5_IRQn untuk debug hexa dan dynamixel

// Array untuk list software generated interrupt yang digunakan oleh FLoWRTOS
IRQn_Type IRQ_FLoW[] = 
{
    // ADC1_IRQn,
    ADC2_IRQn,
    PWM1_PWM5_IRQn,
    PWM2_PWM6_IRQn,
    PWM3_PWM7_IRQn,
    PWM4_PWM8_IRQn,
    FLEXCAN1_IRQn,
    FLEXCAN2_IRQn,
    PCIe1_IRQn,
    PCIe2_IRQn,
    PCIe3_IRQn,
    PCIe4_IRQn,
    eCSPI1_IRQn,
    eCSPI2_IRQn,
    eCSPI3_IRQn,
    eCSPI4_IRQn,
    UART3_IRQn,
    UART4_IRQn,
    UART6_IRQn
};

// mengeset prioritas interrupt dan menenable interrupt
void management_interrupt_init(IRQn_Type IRQn, uint32_t priority);

// set nilai awal deadline dan waketime lalu loncat ke fungsi yang dijalankan sebagai IRQ
void interrupt_task_routine(void(*jump_func)(void));

#ifdef __cplusplus
}
#endif
#endif
