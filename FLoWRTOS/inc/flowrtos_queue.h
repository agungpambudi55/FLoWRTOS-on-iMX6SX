/*
	Copyright (C) 2018 ER2C
	Politektik Elektronika Negeri Surabaya
	Alvin syarifudin <alvinsyarifudin@ce.student.pens.ac.id>
	Agung Pambudi <agung.pambudi5595@gmail.com>
*/
#ifndef FLOWRTOS_QUEUE_H
#define FLOWRTOS_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "flowrtos.h"   

#define FIFO 1
#define LIFO 2

typedef struct queuedef
{
	void* head;
	void* tail;
	size_t length_queue;
	size_t size_queue;
	uint32_t time;
	uint32_t count;
	uint32_t mode;
	void* point;
	List_t TaskWaitQueue;
}Queue_Handler;

int queue_create(Queue_Handler* queue_id,size_t length,size_t itemsize,uint32_t mode) PRIVILEGED_FUNCTION;
int queue_send(Queue_Handler* queue_id,void *message,uint32_t timeout) PRIVILEGED_FUNCTION;
int queue_get(Queue_Handler* queue_id,void* buffer,uint32_t timeout) PRIVILEGED_FUNCTION;
int queue_destroy(Queue_Handler* queue_id)PRIVILEGED_FUNCTION;
int queue_getcount(Queue_Handler* queue_id)PRIVILEGED_FUNCTION;	

#ifdef __cplusplus
}
#endif
