/*
    Copyright (C) 2018 ER2C
    Politektik Elektronika Negeri Surabaya
    Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#include "flowrtos_timer.h"

// generate timer counter for periodic time 1us | EPITA
void management_timer_init(void)
{
    // initialize 0 counter
    count_time_us = count_time_ms = 0;    

    // configuration initialize EPIT
    uint32_t freqA;
    epit_init_config_t config = {
        .freeRun     = true,
        .waitEnable  = true,
        .stopEnable  = true,
        .dbgEnable   = true,
        .enableMode  = true
    };

    /* initialize EPIT module */
    EPIT_Init(BOARD_EPITA_BASEADDR, &config);

    /* set EPIT clock source */
    EPIT_SetClockSource(BOARD_EPITA_BASEADDR, epitClockSourcePeriph);

    /* divide EPITA clock source frequency by 2 inside EPIT module */
    EPIT_SetPrescaler(BOARD_EPITA_BASEADDR, 1);

    /* get EPITA clock frequency */
    freqA = get_epit_clock_freq(BOARD_EPITA_BASEADDR)/2; // 24000000/2       = 12000000 || 1s
    //    freqA = freqA/1000;                            // 12000000/1000    = 12000    || 1ms
    //    freqA = freqA/1000000;                         // 12000000/1000000 = 12       || 1us
    freqA = freqA/1000000;
    
    /* set both EPIT modules to 1 us duration */
    EPIT_SetCounterLoadValue(BOARD_EPITA_BASEADDR, freqA);

    /* the first interrupt occured at 0.5 us */
    EPIT_SetOutputCompareValue(BOARD_EPITA_BASEADDR, freqA/2);

    /* set EPIT interrupt priority to same value to avoid handler preemption */
    NVIC_SetPriority(BOARD_EPITA_IRQ_NUM, 0);

    /* enable NVIC interrupt */
    NVIC_EnableIRQ(BOARD_EPITA_IRQ_NUM);

    /* enable EPIT Output Compare interrupt */
    EPIT_SetIntCmd(BOARD_EPITA_BASEADDR, true);

    /* EPIT start */
    EPIT_Enable(BOARD_EPITA_BASEADDR);       

    PRINTF("#Initialization management timer success\n\r");
}

// handler interrupt for counter timer 1us used by system / user
void BOARD_EPITA_HANDLER(void)
{
    // clear flag interrupt handler from EPIT
    EPIT_ClearStatusFlag(BOARD_EPITA_BASEADDR);     

    // increment or counter up for time unit micro seconds
    count_time_us++;

    // every multiple (kelipatan) of 1000us then increment time unit milli seconds
    if((count_time_us%1000)==0) 
    { 
        count_time_ms++; 
    }   

    // print for the result of generating time
    // if((count_time_us%1000000)==0)
    // { 
    //     PRINTF("%u us || %u ms || %u s || every 1 second\n\r", count_time_us, count_time_ms, count_time_ms/1000); 
    // }
}

// delay function used for rtos system or user
void delay_us(unsigned int delay_val){
    uint32_t delay_start, delay_stop, delay_now;

    delay_start = count_time_us;            // comparator delay time starts
    delay_stop = delay_start + delay_val;   // comparator delay time stopped

    // if condition of comparator time is corresponding then out of iteration or looping
    if (delay_stop > delay_start){
        do{
            delay_now = count_time_us;
        }while(delay_now < delay_stop && delay_now >= delay_start);
    }else{
        do{
            delay_now = count_time_us;
        }while(delay_now < delay_stop || delay_now >= delay_start);
    }
}

// reset timer
void reset_timer(void){
    // 
    count_time_us = count_time_ms = 0;
}
