#ifndef _SCHED_H
#define _SCHED_H

#include <stdint.h>

#define NBREG 13

enum PROCESS_STATUS
{
	WAITING,
	RUNNING,
	TERMINATED,
	BLOCKED
};

typedef int (func_t) (void);

struct pcb_s
{
	uint32_t registers[NBREG];
	uint32_t lr_svc;
	uint32_t lr_user;
	uint32_t* sp_user;
	uint32_t sp_end;
	uint32_t cpsr_user;
	
	func_t* entry;
	
	int status;
	int priority;
	int return_code;
	
	struct pcb_s* next;
	struct pcb_s* previous;
	
	struct pcb_s* next_waiting_sem;
	
	uint32_t** page_table;
};

void sched_init();
void sched_start();
void create_process(func_t* entry);
void create_process_with_fix_priority(func_t* entry, int priority);
void free_process(struct pcb_s* process);

#endif // _SCHED_H
