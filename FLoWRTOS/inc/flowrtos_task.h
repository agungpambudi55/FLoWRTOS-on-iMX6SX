/*
	Copyright (C) 2018 ER2C
	Politektik Elektronika Negeri Surabaya
	Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#ifndef FLOWRTOS_TASK_H
#define FLOWRTOS_TASK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "flowrtos.h"

// flag learning scheduling
bool flag_learning_scheduling = false;

// menghitung jumlah task dilakukan pada fungsi create_task() setiap kali dibuat
uint32_t count_task = 0;

// index interrupt yang dipilih dan dipakai rtos
uint32_t index_int_FLoW = 0;

// waktu total create task | time_start create task mulai | time_finish create task selesai
uint32_t time_task_creation, time_task_creation_start, time_task_creation_finish;

// waktu yang dibutuhkan sorting
uint32_t time_sort, time_sort_start, time_sort_finish;
uint32_t time_sort_list[100], index_run_task = 0;

// waktu untuk menghitung ekseksi task
uint32_t time_start_exec, time_finish_exec;

// flag sbg tanda scheduler berjalan atau belum
// bool flag_scheduler_start = false;

// guna callback task / thread di handler interrupt
typedef void (*task_function_t)( void );  

// callback untuk keperluan mapping interrupt ke task rutin / handler berdasarkan index array-nya
task_function_t callback[50];

//  node linkedlist sebagai informasi parameter task / thread pada task control block
struct node_TCB
{
	// data node linked list TCB
	char *ID_name;
	task_function_t task_routine;	// callback task rutin / thread 
	uint32_t period;		    	// set periode pada dari task 
	uint32_t deadline;        		// deadline relatif dari task
	uint32_t execTime;	     		// start time when task execution
	uint32_t wakeTime;				// waktu task dibangunkan 
	uint32_t wcet;		     		// worst case execution time
	uint32_t state; 				// status task | 0 idle | 1 ready | 2 running | 3 suspened | 4 blocked
	IRQn_Type IRQ_used;				// mapping interrupt yang dipakai

	// penghubung antar node linkedlist
    struct node_TCB *next;
    struct node_TCB *prev;
};

// pointer yang menunjuk TCB untuk keperluan informasi linked list (node baru dari TCB)
struct node_TCB *node_TCB_head;		// deretan TCB terdepan
struct node_TCB *node_TCB_tail;		// deretan TCB terbelakang

// node of state task
struct node_list
{
	struct node_TCB *node_TCB_list;

	// penghubung antar node linkedlist
    struct node_list *next;
    struct node_list *prev;
};

// state task type
struct node_TCB *node_list_idle;
struct node_TCB *node_list_running;
struct node_TCB *node_list_ready;
struct node_TCB *node_list_suspend;

// fungsi inisialisasi scheduler untuk pembuatan jumlah task dimulai dari 0 dan node linklist kosong
void management_task_init(void);

// fungsi pembuatan task dan memasukkan parameter value ke TCB
void create_task(char *ID_name, void (*jump_func)(void), uint32_t deadline);

// membaca LIFO print from tail to head
void find_first_node(struct node_TCB *read_tail);

// membaca FIFO print from head to tail
void find_last_node(struct node_TCB *read_head);

//sorting merge sort
void mergeSort(struct node_TCB **head);
void splitLL(struct node_TCB *head, struct node_TCB **list1, struct node_TCB **list2);
struct node_TCB *mergeSortedLists(struct node_TCB *list1, struct node_TCB *list2);
//sorting merge sort

// fungsi pengurutan task
void sorting_task();

uint32_t median(uint32_t n_data, uint32_t x_data[]);

// fungsi untuk switching task
void context_switch(void);

// fungsi pencarian waktu sorting
void learning(uint32_t time_learning);

// fungsi pengecekan task terhadap deadline dan dilakukan perpindhan task
void scheduler(void);

#ifdef __cplusplus
}
#endif
#endif
