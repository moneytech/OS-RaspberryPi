#include "shell_commands.h"
#include "hw.h"
#include "process.h"
#include "sched.h"
#include "fb_cursor.h"
#include "syscall.h"
#include "pwm.h"
#include "command_parser.h"


extern struct pcb_s* current_process;

void do_echo(int argc, char** argv)
{
	int i;
	
	for (i = 0; i < argc; ++i)
	{
		fb_print_text(argv[i]);
		fb_print_char(' ');
	}
}


static void print_process(struct pcb_s* process)
{
	fb_print_int(process->pid);

	fb_print_text("      ");
	fb_print_int(process->ppid);

	fb_print_text("       ");
	fb_print_int(process->priority);

	fb_print_text("           ");
	fb_print_int(process->status);
	fb_print_text("\n");
}

void do_ps(int argc, char** argv)
{
	struct pcb_s* process = current_process;
	fb_print_text("pid:   ");
	fb_print_text("ppid:   ");
	fb_print_text("priority:   ");
	fb_print_text("status:   ");
	fb_print_text("\n");
	while(process != current_process->previous)
	{
		print_process(process);
		process = process->next;
	}
	print_process(process);
}

void do_fork(int argc, char** argv)
{
	int pid = sys_fork();
	if (pid == 0)
	{
		fb_print_text("child talking, my pid is ");
		fb_print_int(current_process->pid);
		fb_print_text(" and my ppid is ");
		fb_print_int(current_process->ppid);
		fb_print_char('\n');
		sys_exit(0);
	}
	else
	{
		int cmd_status;
		fb_print_text("parent talking, my pid is ");
		fb_print_int(current_process->pid);
		fb_print_char('\n');
		sys_waitpid(pid, &cmd_status);
	}

}


void do_music(int argc, char** argv)
{
	int sound_nb;
	int i = 0;
	while (i < argc)
	{
		sound_nb = str_to_int(argv[i++]);
	
		if (sound_nb < SOUND_IDX_BEGIN || sound_nb > SOUND_IDX_END)
		{
			fb_print_text("Invalid sound index. Select from ");
			fb_print_int(SOUND_IDX_BEGIN);
			fb_print_text(" to ");
			fb_print_int(SOUND_IDX_END);
			fb_print_char('\n');
			return;
		}

		fb_print_text("Playing ");
		fb_print_int(sound_nb);
		fb_print_text("...\n");
		playSound(sound_nb);
	}
}


void do_clear(int argc, char** argv)
{
	fb_clear();
}

void do_pitched_music(int argc, char** argv)
{
	if (argc < 3)
	{
		fb_print_text("Not enough arguments. Command line example :\n");
		fb_print_text("music_pitched music_nb sample_skip clock_div\n");
	}
	else
	{
		int music = str_to_int(argv[0]);
		int sample_skip = str_to_int(argv[1]);
		int clock_div = str_to_int(argv[2]);

		playPitchedSound(music, sample_skip, clock_div);
	}
}

void do_melody(int argc, char** argv)
{
	int* melody_array = (int*) gmalloc(sizeof(int) * argc);
	uint32_t i;
	for (i = 0; i < argc; ++i)
	{
		melody_array[i] = str_to_int(argv[i]);
	}

	fb_print_text("Playing your custom melody!\n");
	playMelody(melody_array, argc);
	gfree(melody_array);
}
