/*
    Copyright (C) 2018 ER2C
    Politektik Elektronika Negeri Surabaya
    Alvin syarifudin <alvinsyarifudin@ce.student.pens.ac.id>
    Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#ifndef FLOWRTOS_MALLOC_TSLF_H
#define FLOWRTOS_MALLOC_TSLF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "flowrtos.h"   

#define BYTE_ALIGNMENT      8
#define BYTE_ALIGNMENT_MASK ((uint32_t)( 0x0007U ))
#define Heap_Size           ((size_t)( 16 * 1024 ))

#define TLSF_SL             3
#define SLI                 (1<<TLSF_SL)
#define TLSF_MAXSIZE        15
#define NONE                TLSF_MAXSIZE+1
#define TLSF_Offset         4
#define REAL_first_level    TLSF_MAXSIZE-TLSF_Offset
#define REAL_second_level   (1<<SLI)
#define head_size           (sizeof (freeptr_t))
#define Overhead            (sizeof (struct_head))

uint8_t ucHeap[Heap_Size];
#define TLSF_Heap (((uint32_t)&ucHeap[BYTE_ALIGNMENT]) & (~(BYTE_ALIGNMENT_MASK)))

typedef struct header_struct {
    struct header_struct *prev_hdr;
    size_t size;
    struct header_struct *prev;
    struct header_struct *next;
} struct_head;

typedef struct TLSF_struct {
    uint32_t first_level_bitmap;
    uint32_t second_level_bitmap[REAL_first_level+2];
    struct_head *matrix[REAL_first_level+2][SLI];
} struct_tlsf;

void management_memory_init(void);
void TLSF_init(void);
void insert_block(struct_head *block,struct_tlsf *tlsf,uint32_t* first_level,uint32_t* second_level);
struct_head* find_suitable_block(struct_tlsf* tlsf,uint32_t* first_level,uint32_t* second_level);
void mapping_search(size_t r,uint32_t* first_level,uint32_t* second_level);
void mapping_insert(size_t r,uint32_t* first_level,uint32_t* second_level);
void unlink_block(struct_head* block,struct_tlsf* tlsf,uint32_t *first_level,uint32_t *second_level);
int most_bit(int i);
int least_bit(int i);
void* malloc_TLSF(size_t size);
int free_TLSF(void* point);

#ifdef __cplusplus
}
#endif
#endif
