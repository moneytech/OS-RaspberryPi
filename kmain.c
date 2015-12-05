#include "sched.h"
#include "vmem.h"
#include "config.h"

void kmain()
{
	sched_init();
	
	 __asm("cps 0x10");

	vmem_translate(0, NULL);
	vmem_translate(1, NULL);
}
