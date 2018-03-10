/*
	Copyright (C) 2018 ER2C
	Politektik Elektronika Negeri Surabaya
	Alvin syarifudin <alvinsyarifudin@ce.student.pens.ac.id>
	Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#include "flowrtos_malloc_TSLF.h"

static uint8_t *Heap_Begin; 
// fl = first level
// sl = second level
// dynamic allocation memory
// inisialisasi manajemen memori
void management_memory_init(void){
	TLSF_init();
    PRINTF("#Initialization management memory success\n\r"); 
}

// inisialisasi algoritma tslf untuk manajemen memori
void TLSF_init(void)
{
	//PRINTF("\n\r[ TLSF ] ------------------------------ init pool\n\r"); 
	int i = 0, j = 0, res = 45000; 
	uint32_t first_level = 0, second_level = 0; 
    struct_tlsf *tlsf; 
    struct_head *block, *lastblock; 
    size_t size; 

	Heap_Begin = (uint8_t*)TLSF_Heap; 
	tlsf = (struct_tlsf *) Heap_Begin; 

	//PRINTF("Alamat awal heap begin %p\n\r", Heap_Begin); 
	//PRINTF("Alamat awal tslf %p\n\r", tlsf); 
	//PRINTF("Besar tlsf %d block header %d\n\r", sizeof(struct_tlsf), sizeof(struct_head)); 

	block = ((struct_head *)((char *)(Heap_Begin)+(sizeof(struct_tlsf)))); 

	size = res-sizeof(struct_tlsf); 
	block->size = (size-2*Overhead); 
	//PRINTF("Block = %d alamat %x %x next = %x \n\r", block->size, &block->size, &block->prev, &block->next); 

	block->prev = NULL; 
	block->next = NULL; 

	lastblock = ((struct_head *)((char *)(&block->next)+(block->size&~3)+4)); 
	//PRINTF("Last block %x\n\r", lastblock); 

	lastblock->prev_hdr = block; 
	lastblock->size = 0x2; 

	//PRINTF("Alamat %x besar %d\n\r", block, block->size); 
	tlsf->first_level_bitmap = 0; 
	for(i = 0; i<REAL_first_level; i++)
	{
		for(j = 0; j<SLI; j++)
		{ tlsf->matrix[i][j] = 0; }
		tlsf->second_level_bitmap[i] = 0; 
	}
	mapping_insert(block->size, &first_level, &second_level); 
	insert_block(block, tlsf, &first_level, &second_level); 

    //PRINTF("#Initialization heapTSLF success\n\r"); 
}

void insert_block(struct_head *block, struct_tlsf *tlsf, uint32_t* first_level, uint32_t* second_level)
{
	//PRINTF("\n\r[ TLSF ] ------------------------------ insert block\n\r"); 
	block->prev = NULL; 
	//PRINTF("Alamat %x tlsf %x first_level %d second_level %d \n\r", block, tlsf, *first_level, *second_level); 
	//PRINTF("Block %x\n\r", tlsf->matrix[*first_level][*second_level]); 

	block->next = tlsf->matrix[*first_level][*second_level]; 
	
	if (tlsf->matrix [*first_level][*second_level])
	{
		//PRINTF("Check insert\n\r"); 
	 	tlsf-> matrix [*first_level][*second_level] ->prev  = block; 
	}
	tlsf->matrix[*first_level][*second_level] = block; 
	//PRINTF("Block %x\n\r", tlsf->matrix[*first_level][*second_level]); 
	//PRINTF("Bitmap second_level%d", tlsf->second_level_bitmap[*first_level]); 
	tlsf->second_level_bitmap[*first_level] |= (1<<*second_level); 
	tlsf->first_level_bitmap |= (1<<*first_level); 
	//PRINTF("Bitmap %d temp %d\n\r", tlsf->second_level_bitmap[*first_level], tlsf->first_level_bitmap); 
}

struct_head* find_suitable_block(struct_tlsf* tlsf, uint32_t* first_level, uint32_t* second_level)
{
	//PRINTF("[ TLSF ] ------------------------------ find suitablen\r"); 

	uint32_t temp; 
	//PRINTF("Pool %x\n\r", tlsf); 
	//PRINTF("first_level %d second_level %d\n\r", *first_level, *second_level); 
	temp = tlsf->second_level_bitmap[*first_level]& (~0 << *second_level); 
	//PRINTF("Bitmap %d temp %d\n\r", tlsf->second_level_bitmap[*first_level], temp); 
	struct_head *block = NULL; 
	if(temp)
	{
		*second_level = least_bit(temp); 
		block = tlsf->matrix[*first_level][*second_level]; 
		//PRINTF("block %x\n\r", &tlsf->matrix[*first_level][*second_level]); 
	}
	else
	{
		*first_level = least_bit((tlsf->first_level_bitmap&(~0<<(*first_level+1)))); 
		//PRINTF("first_level %d ", *first_level); 
		*second_level = least_bit(tlsf->second_level_bitmap[*first_level]); 
		//PRINTF("second_level %d\n\r", *second_level); 
		block = tlsf->matrix[*first_level][*second_level]; 
		//PRINTF("block %x\n\r", block); 
	}
	return block; 
}

// Most Significant Bit
// Mengambil bit terbesar
int most_bit(int i)
{
	int r = 31; 
	if(!i){	return 0; } 
	if(!(i&0xffff0000)) { i = i<<16; r -= 16; }
	if(!(i&0xff000000)) { i = i<<8; r -= 8; }
	if(!(i&0xf0000000)) { i = i<<4; r -= 4; }
	if(!(i&0xc0000000)) { i = (i<<2); r -= 2; }
	if(!(i&0x80000000)) { i = i<<1; r -= 1; }
	return r; 
}

// Least Significant Bit
// mengambil nilai bit terkecil
int least_bit(int i)
{
	int r = 0; 
	if(!i){ return 0; }
	if(!(i&0xffff)) { i >>= 16; r += 16; }
	if(!(i&0xff)) { i >>= 8; r += 8; }
	if(!(i&0xf)) { i >>= 4; r += 4; }
	if(!(i&3)) { i >>= 2; r += 2; }
	if(!(i&1)) { i >>= 1; r += 1; }
	return r; 
}

void mapping_search(size_t r, uint32_t* first_level, uint32_t* second_level)
{
	r = r+(1<<(most_bit(r)-TLSF_SL))-1; 
	*first_level = most_bit(r); 
	*second_level = (r>>(*first_level-TLSF_SL))-(SLI); 
	//*second_level = (r-(1<<*first_level))/(1<<(*first_level-TLSF_SL)); 
	*first_level -= TLSF_Offset; 
	//PRINTF("search second_level:%u first_level:%u\n\r", *second_level, *first_level); 
}

void mapping_insert(size_t r, uint32_t* first_level, uint32_t* second_level)
{
	*first_level = most_bit(r); 
	*second_level = (r>>(*first_level-TLSF_SL))-(SLI); 
	//*second_level = (r-(1<<*first_level))/(1<<(*first_level-TLSF_SL)); 
	*first_level -= TLSF_Offset; 
	//PRINTF("insert second_level:%u first_level:%u\n\r", *second_level, *first_level); 
}

void unlink_block(struct_head* block, struct_tlsf* tlsf, uint32_t *first_level, uint32_t *second_level)
{
	//PRINTF("\n\r[TSLF ] ------------------------------ unlink block\n\r"); 
	tlsf->matrix[*first_level][*second_level] = block->next; 
	//PRINTF("Matrix %d\n\r", tlsf->matrix[*first_level][*second_level]); 
	if(tlsf->matrix[*first_level][*second_level])
	{
		//PRINTF("Check unlink\n\r"); 
		tlsf->matrix[*first_level][*second_level]->prev = NULL; 
	}
	else
	{
		tlsf->second_level_bitmap[*first_level] = tlsf->second_level_bitmap[*first_level]&(~(1<<*second_level)); 
		if(tlsf->second_level_bitmap[*first_level] == 0)
		{ tlsf->first_level_bitmap &= (~(1<<*first_level)); }
		//PRINTF("Bitmap first_level %d second_level %d\n\r", tlsf->first_level_bitmap, tlsf->second_level_bitmap[*first_level]); 
	}
	block->prev = NULL; 
	block->next = NULL; 
}

void* malloc_TLSF(size_t size)
{
	//PRINTF("\n\r[ TSLF ] ------------------------------ malloc start\n\r"); 
	struct_tlsf *tlsf = (struct_tlsf*)Heap_Begin; 
	struct_head *free_block, *last_block, *next_block; 
	size_t temp; 
	uint32_t first_level = 0, second_level = 0; 
	//PRINTF("Alamat awal heap begin %p\n\r", Heap_Begin); 
	//PRINTF("Alamat awal tslf %p\n\r", tlsf); 
	
	if(size != 0)
	{
		size  = (size<16)?16:((size+3)&~3); 
		//PRINTF("Pool %x size %d besar void %d\n\r", tlsf, size, sizeof(void*)); 		
		free_block = find_suitable_block(tlsf, &first_level, &second_level); 
		//PRINTF("Freeblock %x %x\n\r", &free_block, free_block); 
		if(!free_block) { return NULL; }

		unlink_block(free_block, tlsf, &first_level, &second_level); 

		last_block = ((struct_head *)((char *)(&free_block->next)+(free_block->size&~3)+4)); 

		//PRINTF("Lastblock %x\n\r", last_block); 
		temp = (free_block->size&~3)-size; 
		//PRINTF("Besar sisa %d\n\r", temp); 
		if(temp >= sizeof(struct_head))
		{
			temp -= Overhead; 
			//PRINTF("Besar sisa 2 %d\n\r", temp); 
			next_block = ((struct_head *)((char *)(&free_block->next)+(size)+4)); 
			//PRINTF("Alamat blok selanjutnya %x\n\r", next_block); 
			next_block->size = (temp|1); 
			//PRINTF("Besar size block %d\n\r", next_block->size); 
			last_block->prev_hdr = next_block; 
			mapping_insert(temp, &first_level, &second_level); 
			insert_block(next_block, tlsf, &first_level, &second_level); 
			free_block->size = size|(free_block->size&2); 
			//PRINTF("Besar block yang digunakan %d\n\r", free_block->size); 
		}
		else
		{
			last_block->size &= (~2); 
			free_block->size &= (~3); 
		}
	}
	else
	{ return NULL; }	
	return ((void *)((char*) &free_block->next+4)); 
}

int free_TLSF(void* point)
{
	uint32_t first_level = 0, second_level = 0; 
	struct_tlsf *tlsf = (struct_tlsf*)Heap_Begin; 
	struct_head *block, *next_block; 
	if(!point) { return 0; } 
	//PRINTF("Alamat point free %x\n\r", point); 
	block = (struct_head *) ((char *) point-Overhead); 
	//PRINTF("Alamat header %x\n\r", block); 

	block->size |=  1; 
	block->prev = NULL; 
	block->next = NULL; 

	next_block = (struct_head *) ((char *) &block->next+(block->size&~3)+4); 
	//PRINTF("Next block %x\n\r", next_block); 

	if(next_block->size&1)
	{
		mapping_insert(next_block->size, &first_level, &second_level); 
		unlink_block(next_block, tlsf, &first_level, &second_level); 
		block->size += ((next_block->size&~3)+Overhead); 
		//PRINTF("Feeblock size %d\n\r", block->size); 
	}
	if(block->size&2)
	{
		next_block = block->prev_hdr; 
		mapping_insert(next_block->size, &first_level, &second_level); 
		unlink_block(next_block, tlsf, &first_level, &second_level); 
		//PRINTF("Besar block %d\n\r", next_block->size); 
		next_block->size += (block->size&~3)+Overhead; 
		//PRINTF("Prevfree size %d\n\r", next_block->size); 
		block = next_block; 
	}
	mapping_insert(block->size, &first_level, &second_level); 
	insert_block(block, tlsf, &first_level, &second_level); 
	next_block = (struct_head *) ((char *) &block->next+(block->size&~3)+4); 
	//PRINTF("Alamat next block %x\n\r", next_block); 
	next_block->size |= 2; 
	//PRINTF("Block free %d besar next block %d\n\r", block->size, next_block->size); 
	next_block->prev_hdr = block; 
	return 1; 
}
