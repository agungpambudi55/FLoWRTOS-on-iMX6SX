/*
	Copyright (C) 2018 ER2C
	Politektik Elektronika Negeri Surabaya
    Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#ifndef FLOWRTOS_TIMER_H
#define FLOWRTOS_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "flowrtos.h"

// variable from timer counter up for rtos system or user with units of us and ms
uint32_t count_time_ms = 0, count_time_us = 0;

// generate timer counter for periodic time 1us | EPITA
void management_timer_init(void);

// handler interrupt for counter timer 1us used by system / user
void BOARD_EPITA_HANDLER(void);

// delay function used for rtos system or user
void delay_us(unsigned int delay_val);

// reset timer
void reset_timer(void);

#ifdef __cplusplus
}
#endif
#endif
