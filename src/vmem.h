#ifndef _VMEM_H
#define _VMEM_H

#include <stdint.h>
#include "sched.h"

#define PAGE_SIZE 4096

#define FIRST_LVL_TT_COUN 4096 // Number of table 1 entries
#define FIRST_LVL_TT_SIZE 16384
#define FIRST_LVL_TT_ALIG 14 // Alignment

#define SECON_LVL_TT_COUN 256 // Number of table 2 entries
#define SECON_LVL_TT_SIZE 1024
#define SECON_LVL_TT_ALIG 10 // Alignment

void vmem_init();
unsigned int init_kern_translation_table(void);

void configure_mmu_C();
void start_mmu_C();
uint32_t vmem_translate(uint32_t va, struct pcb_s* process);

#endif // _VMEM_H