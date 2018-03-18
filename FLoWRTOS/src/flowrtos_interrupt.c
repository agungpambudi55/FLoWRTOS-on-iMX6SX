/*
    Copyright (C) 2018 ER2C
    Politektik Elektronika Negeri Surabaya
    Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#include "flowrtos_interrupt.h"

// #define STRINGIFY(x) #x
// #define TOSTRING(x) STRINGIFY(x)
// // reads the register reg to the variable var
// #define READ_REGISTER(var,reg) __asm volatile("mov %[result], " TOSTRING(reg) "\n\t" : [result] "=r" (var))

// mengeset prioritas interrupt dan menenable interrupt
void management_interrupt_init(IRQn_Type IRQn, uint32_t priority){
    // mengeset prioritas interrupt yang dipilih ke prioritas paling kecil / rendah
    NVIC_SetPriority(IRQn, priority);
    // PRINTF("%u\n\r", NVIC_GetPriority(IRQn));

    // mengaktifkan interrupt yang dipilih sebagai thread 
    NVIC_EnableIRQ(IRQn);

    // PRINTF("#Initialization management interrupt success\n\r");
}

// fungsi ke task rutin yang berjalan dihandler INT
void interrupt_task_routine( void( *jump_func )( void ) )
{
    // PRINTF("ID(%s) IRQn(%u) pt(%u) dt(%u) wt(%u) et(%u) wcet(%u) t(%u)\n\r",
    //         node_TCB_head->ID_name,
    //         node_TCB_head->IRQ_used,
    //         node_TCB_head->period,
    //         node_TCB_head->wakeTime,
    //         node_TCB_head->deadline,
    //         node_TCB_head->execTime,
    //         node_TCB_head->wcet,
    //         count_time_us
    //     );

    node_TCB_head->state = 2;
    time_start_exec = count_time_us;
    
    if(flag_learning_scheduling == false){
        PRINTF("ID(%s) IRQn(%3u) pt(%u) st(%u) wt(%u) dt(%u) ",
                node_TCB_head->ID_name,
                node_TCB_head->IRQ_used,
                node_TCB_head->period,
                time_start_exec,
                node_TCB_head->wakeTime,
                node_TCB_head->deadline
            );
    }

    time_sort_list[index_run_task] = time_start_exec;
    index_run_task++;

    jump_func();                    // fungsi loncat ke task rutin / thread

    time_finish_exec = count_time_us + time_sort;

    if( time_start_exec <= node_TCB_head->deadline && time_finish_exec >= node_TCB_head->deadline )
    { node_TCB_head->wcet = time_finish_exec - node_TCB_head->deadline; }
    else
    { node_TCB_head->wcet = 0; }

    node_TCB_head->execTime = time_finish_exec - time_start_exec; 
    node_TCB_head->wakeTime += node_TCB_head->period;
    node_TCB_head->deadline += node_TCB_head->period;

    time_sort_list[index_run_task] = time_finish_exec;
    index_run_task++;

    if(flag_learning_scheduling == false){
        PRINTF("et(%u) wcet(%u)\n\rID(%s) IRQn(%3u) pt(%u) ft(%u) wt(%u) dt(%u) et(%u) wcet(%u)\n\r",
                node_TCB_head->execTime,
                node_TCB_head->wcet,
                node_TCB_head->ID_name,
                node_TCB_head->IRQ_used,
                node_TCB_head->period,
                time_finish_exec,
                node_TCB_head->wakeTime,
                node_TCB_head->deadline,
                node_TCB_head->execTime,
                node_TCB_head->wcet
            );
    }
    
    node_TCB_head->state = 1;
}

// INT_HANDLER :: mengambil alih fungsi interrupt handler sebagai task rutin / thread ============ START
// void ADC1_Handler(void)
// {
//     NVIC_ClearPendingIRQ(ADC1_IRQn);
//     interrupt_task_routine(callback[0]);
// }

void ADC2_Handler(void)
{
    NVIC_ClearPendingIRQ(ADC2_IRQn);
    interrupt_task_routine(callback[0]);
}

void PWM1_PWM5_Handler(void)
{
    NVIC_ClearPendingIRQ(PWM1_PWM5_IRQn);
    interrupt_task_routine(callback[1]);
}

void PWM2_PWM6_Handler(void)
{
    NVIC_ClearPendingIRQ(PWM2_PWM6_IRQn);
    interrupt_task_routine(callback[2]);
}

void PWM3_PWM7_Handler(void)
{
    NVIC_ClearPendingIRQ(PWM3_PWM7_IRQn);
    interrupt_task_routine(callback[3]);
}

void PWM4_PWM8_Handler(void)
{
    NVIC_ClearPendingIRQ(PWM4_PWM8_IRQn);
    interrupt_task_routine(callback[4]);
}

void FLEXCAN1_Handler(void)
{
    NVIC_ClearPendingIRQ(FLEXCAN1_IRQn);
    interrupt_task_routine(callback[5]);
}

void FLEXCAN2_Handler(void)
{
    NVIC_ClearPendingIRQ(FLEXCAN2_IRQn);
    interrupt_task_routine(callback[6]);
}

void PCIe1_Handler(void)
{
    NVIC_ClearPendingIRQ(PCIe1_IRQn);
    interrupt_task_routine(callback[7]);
}

void PCIe2_Handler(void)
{
    NVIC_ClearPendingIRQ(PCIe2_IRQn);
    interrupt_task_routine(callback[8]);
}

void PCIe3_Handler(void)
{
    NVIC_ClearPendingIRQ(PCIe3_IRQn);
    interrupt_task_routine(callback[9]);
}

void PCIe4_Handler(void)
{
    NVIC_ClearPendingIRQ(PCIe4_IRQn);
    interrupt_task_routine(callback[10]);
}

void eCSPI1_Handler(void)
{
    NVIC_ClearPendingIRQ(eCSPI1_IRQn);
    interrupt_task_routine(callback[11]);
}

void eCSPI2_Handler(void)
{
    NVIC_ClearPendingIRQ(eCSPI2_IRQn);
    interrupt_task_routine(callback[12]);
}

void eCSPI3_Handler(void)
{
    NVIC_ClearPendingIRQ(eCSPI3_IRQn);
    interrupt_task_routine(callback[13]);
}

void eCSPI4_Handler(void)
{
    NVIC_ClearPendingIRQ(eCSPI4_IRQn);
    interrupt_task_routine(callback[14]);
}

void UART3_Handler(void)
{
    NVIC_ClearPendingIRQ(UART3_IRQn);
    interrupt_task_routine(callback[15]);
}

void UART4_Handler(void)
{
    NVIC_ClearPendingIRQ(UART4_IRQn);
    interrupt_task_routine(callback[16]);
}

void UART6_Handler(void)
{
    NVIC_ClearPendingIRQ(UART6_IRQn);
    interrupt_task_routine(callback[17]);
}
// INT_HANDLER :: mengambil alih fungsi interrupt handler sebagai task rutin / thread ============ END
