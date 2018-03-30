/*
    Copyright (C) 2018 ER2C
    Politektik Elektronika Negeri Surabaya
    Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#include "flowrtos_task.h"

// initialization function for creation of 
// number tasks starting from 0 and linklist node starting from empty
void management_task_init(void)
{
    count_task = 0;
    node_TCB_head = NULL;
    node_TCB_tail = NULL;
    
    // set priority and enabling interrupt for scheduling
    management_interrupt_init(scheduler_IRQ_NUM,1);

    PRINTF("#Initialization management task success\n\r");
}

// task creation and enter parameter value to TCB
void create_task(char *ID_name,  void (*jump_func)(void), uint32_t deadline)
{
    // new node TCB when task creation to allocate memory and input parameters
    struct node_TCB *node_TCB_new;  

    // read node TCB
    struct node_TCB *node_TCB_read; 
    
    // calculates the start time of a task creation
    time_task_creation_start = count_time_us;

    // counts the number of task creation with increment
    count_task++;
    // PRINTF("create_task %u - Start\n\r",count_task);

    // index of interrupt used obtained of decrement number of task
    index_int_FLoW = count_task - 1;
    // PRINTF("INT number %d\n\r",IRQ_FLoW[index_int_FLoW]);

    // set priority interrupt and enabling interrupt as task routine
    management_interrupt_init(IRQ_FLoW[index_int_FLoW], 4);

    // memory allocation for TCB as information of task routine using TSLF malloc
    node_TCB_new = (struct node_TCB *) malloc_TLSF(sizeof(struct node_TCB));     
    // PRINTF("alocation memory TCB %u success\n\r",count_task);
    // PRINTF("block memory %x \n\r", node_TCB_new); 

    // insert data parameter into node TBC
    node_TCB_new->ID_name      = ID_name;
    node_TCB_new->task_routine = jump_func;                   // pointer to task routine as handler interrupt
    node_TCB_new->period       = deadline;                    // initial declaration 0 because it has not been executed
    node_TCB_new->execTime     = 0;                           // deklarasi awal 0 digunakan pada handler INT
    node_TCB_new->deadline     = deadline;                    // deadline task
    node_TCB_new->wakeTime     = 0;                           // deklarasi awal 0 digunakan pada handler INT
    node_TCB_new->wcet         = 0;                           // wcet (kemungkinan waktu terburuk dari task)
    node_TCB_new->state        = 0;                           // status task
    node_TCB_new->IRQ_used     = IRQ_FLoW[index_int_FLoW];    // memetakan rutin handler ke interrupt berdasarkan index array IRQ_FLoW[]
    callback[index_int_FLoW]   = node_TCB_new->task_routine;  // memetakan rutin handler task ke array callback untuk dipaggil ketika handler dijalankan
    // TCB baru akan disisipkan maka pointer kosong
    node_TCB_new->prev = node_TCB_new->next = NULL;
    // PRINTF("Mapping task %u success\n\r",count_task);
    
    // menambah dan mengurutkan task berdasarkan periode terkecil
    // metode untuk menambah dan mengurutkan scr langsung double linked list yang paling efisien yaitu insertion sort
    // insertion sort dan merge sort lebih sedikit overhead dibandingkan dengan bubble atau selection sort
    // insertion sort performanya lebih bagus dibanding merge sort ketika sedikit node
    if (node_TCB_head == NULL){                                // if list is empty
        node_TCB_head = node_TCB_new;
    } else if (node_TCB_head->period >= node_TCB_new->period){  // if the node_TCB is to be inserted at the beginning
        node_TCB_new->next = node_TCB_head;
        node_TCB_new->next->prev = node_TCB_new;
        node_TCB_head = node_TCB_new;
    } else {
        node_TCB_read = node_TCB_head;

        // mencari node_TCB setelah node_TCB baru dimasukkan
        while(node_TCB_read->next != NULL && node_TCB_read->next->period < node_TCB_new->period)
            node_TCB_read = node_TCB_read->next;
        node_TCB_new->next = node_TCB_read->next;

        // jika node_TCB baru tidak dimasukkan di akhir daftar
        if (node_TCB_read->next != NULL)
            node_TCB_new->next->prev = node_TCB_new;
        node_TCB_read->next = node_TCB_new;
        node_TCB_new->prev = node_TCB_read;
    }
    // PRINTF("create_task %u - Finish\n\r",count_task);

    // menghitung waktu akhir sebuah task dibuat
    time_task_creation_finish = count_time_us;

    // menghitung waktu proses sebuah task dibuat
    time_task_creation = time_task_creation_finish - time_task_creation_start;
    PRINTF("#Create task %u success - ( INT number %d // time task creation %uus ) \n\r", count_task, IRQ_FLoW[index_int_FLoW], time_task_creation);
}

// membaca FIFO print from head to tail
void find_last_node(struct node_TCB *read_head)
{   
    while (read_head != NULL) 
    {
        // PRINTF("FIFO %u \n\r",read_head->period);
        
        // ketika node read berada diujung ditandai dengan node selanjutnya NULL 
        // maka node tersebut dijadikan tail
        if(read_head->next==NULL) node_TCB_tail=read_head;  

        read_head = read_head->next;
    }
}

// membaca LIFO print from tail to head
void find_first_node(struct node_TCB *read_tail)
{
    while (read_tail != NULL) 
    {
        // PRINTF("LIFO %u \n\r",read_tail->period);

        // ketika node read berada diujung ditandai dengan node sebelumnya NULL 
        // maka node tersebut dijadikan head
        if(read_tail->prev==NULL) node_TCB_head=read_tail;  

        read_tail = read_tail->prev;
    }
}

// pengurutan double linked list dengan metode algoritma merge sort
void mergeSort(struct node_TCB **head)
{
    struct node_TCB *list1;
    struct node_TCB *list2;
    /* Base case -- length 0 or 1 */
    if ((*head == NULL) || ((*head)->next == NULL))
    {
      return;
    }
 
    // Split list(head) into 'list1' and 'list2' sublists 
    splitLL(*head, &list1, &list2); 
 
    /* Recursively sort the sublists */
    mergeSort(&list1);
    mergeSort(&list2);
    //merge the two sorted lists together
    *head = mergeSortedLists(list1, list2);
}

//Merge the two sorted lists
struct node_TCB *mergeSortedLists(struct node_TCB *list1, struct node_TCB *list2)
{ 
  /* Base cases */
  if (list1 == NULL)
     return(list2);
  else if (list2==NULL)
     return(list1);
 
  /* Pick either list1 or list2, and recur */
  if (list1->deadline <= list2->deadline)
  {
    list1->next = mergeSortedLists(list1->next,list2);
    list1->next->prev = list1;
    list1->prev = NULL;
    return list1;
  }
  else
  {
    list2->next = mergeSortedLists(list1,list2->next);
    list2->next->prev = list2;
    list2->prev = NULL;
    return list2;
  }
}
 
//split the nodes into two halves 
void splitLL(struct node_TCB *head, struct node_TCB **list1, struct node_TCB **list2)
{
  struct node_TCB *fast;
  struct node_TCB *slow;
  if (head==NULL || head->next==NULL)
  {
    /* length < 2 cases */
    *list1 = head;
    *list2 = NULL;
  }
  else
  {
    slow = head;
    fast = head->next;
 
    // Move 'fast' two nodes, and move 'slow' one node //
    while (fast != NULL)
    {
      fast = fast->next;
      if (fast != NULL)
      {
        slow = slow->next;
        fast = fast->next;
      }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two at that point. */
    *list1 = head;
    *list2 = slow->next;
    slow->next = NULL;
  }
}

// fungsi pengurutan task
void sorting_task()
{
    mergeSort(&node_TCB_head);
}

// mencari nilai tengah dari deretan angka
uint32_t median(uint32_t n_data, uint32_t x_data[]) {
    uint32_t temp;
    uint32_t i, j;
    // the following two loops sort the array x in ascending order
    for(i=0; i<n_data-1; i++) {
        for(j=i+1; j<n_data; j++) {
            if(x_data[j] < x_data[i]) {
                // swap elements
                temp = x_data[i];
                x_data[i] = x_data[j];
                x_data[j] = temp;
            }
        }
    }
    if(n_data%2==0) {
        // if there is an even number of elements, return mean of the two elements in the middle
        return ((x_data[n_data/2] + x_data[n_data/2 - 1]) / 2.0);
    } else {
        // else return the element in the middle
        return x_data[n_data/2];
    }
}

// void test(){
//     __asm volatile
//     (
//     "   mov r0, #0                          \n"
//     "   msr basepri, r0                     \n"
//     "   ldmia sp!, {r3}                     \n"
//     "                                       \n"
//     "   ldr r1, [r3]                        \n" /* The first item in pxCurrentTCB is the task top of stack. */
//     "   ldr r0, [r1]                        \n"
//     "                                       \n"
//     "   ldmia r0!, {r4-r11, r14}            \n"  Pop the core registers. 
//     "                                       \n"
//     "   tst r14, #0x10                      \n" /* Is the task using the FPU context?  If so, pop the high vfp registers too. */
//     "   it eq                               \n"
//     "   vldmiaeq r0!, {s16-s31}             \n"
//     "                                       \n"
//     "   msr psp, r0                         \n"
//     "   isb                                 \n"
//     "                                       \n"
//     );
// }
// void xPortPendSVHandler( void )
// {
//     /* This is a naked function. */

//     __asm volatile
//     (
//     "   mrs r0, psp                         \n"
//     "   isb                                 \n"
//     "                                       \n"
//     "   ldr r3, pxCurrentTCBConst           \n" /* Get the location of the current TCB. */
//     "   ldr r2, [r3]                        \n"
//     "                                       \n"
//     "   tst r14, #0x10                      \n" /* Is the task using the FPU context?  If so, push high vfp registers. */
//     "   it eq                               \n"
//     "   vstmdbeq r0!, {s16-s31}             \n"
//     "                                       \n"
//     "   stmdb r0!, {r4-r11, r14}            \n" /* Save the core registers. */
//     "                                       \n"
//     "   str r0, [r2]                        \n" /* Save the new top of stack into the first member of the TCB. */
//     "                                       \n"
//     "   stmdb sp!, {r3}                     \n"
//     "   mov r0, %0                          \n"
//     "   msr basepri, r0                     \n"
   
//     #ifdef WORKAROUND_PMU_CM001 /* XMC4000 specific errata workaround. */
//         #if WORKAROUND_PMU_CM001 == 1
//     "           push { r14 }                \n"
//     "           pop { pc }                  \n"
//         #endif
//     #endif
//     "                                       \n"
//     "   bx r14                              \n"
//     "                                       \n"
//     "   .align 2                            \n"
//     "pxCurrentTCBConst: .word node_TCB_head  \n"
//     ::"i"(configMAX_SYSCALL_INTERRUPT_PRIORITY)
//     );
// }

// fungsi untuk switching task
void context_switch(void){
    // sorting jika task selesai dijalankan
    if( node_TCB_head->state == 0 || node_TCB_head->state == 1 )
    { 
        // sorting deadline terdekat
        sorting_task(); 

        // jika periodic count time sama / lebih besar waktu bangunnya task maka task tsb dijadikan ready dan berjalan
        if( count_time_us >= node_TCB_head->wakeTime )
        { NVIC_SetPendingIRQ( node_TCB_head->IRQ_used ); }
    }
    if( node_TCB_head->state == 2 ){
    }

}

// fungsi mengetahui waktu task disorting
void learning(uint32_t time_learning)
{
    flag_learning_scheduling = true;
    PRINTF("\n\r#Learning\n\r#Please wait ...\n\r");
    uint32_t index_list = 0;

    time_sort = 0;

    find_last_node(node_TCB_head);
    find_first_node(node_TCB_tail);

    // mengeset ulang counter timer
    reset_timer();

    while(true)
    {
        context_switch();

        // learning diberhentikan
        if( count_time_us >= time_learning ) 
        { break; }
    }

    // show time start finish task routine
    // for(uint32_t index=0; index<index_run_task; index++){
    //     PRINTF("%u\n\r",time_sort_list[index]);
    // }
    // PRINTF("\n\r");

    // mencari selisih finish start antar task
    for(uint32_t index=1; index<(index_run_task-1); index+=2){
        time_sort_list[index_list] = time_sort_list[index+1] - time_sort_list[index];
        // PRINTF("%u\n\r",time_sort_list[index_list]);
        index_list++;
    }

    time_sort = median(index_list,time_sort_list);

    PRINTF("\n\r#Waktu pengurutan %u us\n\r\n\r", time_sort);

    // mengeset semua TCB
    struct node_TCB *read_head = node_TCB_head;
    while (read_head != NULL) 
    {
        read_head->deadline = read_head->period;
        read_head->execTime = 0;
        read_head->wakeTime = 0;
        read_head->wcet     = 0;
        read_head->state    = 0;

        read_head = read_head->next;
    }

    sorting_task();
    flag_learning_scheduling = false;
}

// fungsi pengecekan task terhadap deadline dan dilakukan perpindhan task
void scheduler(void)
{
    PRINTF("\n\r#Scheduler will run in 2,5 seconds\n\r");
    delay_us(2500000);

    // mengeset ulang counter timer
    reset_timer();

    // scheduling task dijalankan yang sebenarnya
    while(true){
        context_switch();
    }
}