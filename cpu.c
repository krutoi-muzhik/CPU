#include "cpu.h"
#include "stack.h"

#define handle_error(comand) { 							\
	printf (comand); 									\
	printf (" !!! ERROR OCCURED CHECK LOGS !!!\n\n");   \
	exit (EXIT_FAILURE); 								\
}

void
Processing (const char *object_path) {
	FILE *object_file;
	if ((object_file = fopen (object_path, "r")) == NULL)
		handle_error ("fopen (input_path)")

	struct stat stat_buff;
	stat (object_path, &stat_buff);
	size_t object_size = stat_buff.st_size;
	size_t code_size = object_size / 4;

	int *code = (int *) calloc (code_size, sizeof (int));
	fread (code, sizeof (int), object_size, object_file);

	// typedef struct processor {
	// 	stack *stk;
	// 	stack *func_stk;
	// 	int *regs;
	// 	int *ram;
	// } cpu_t;

	stack stk1;
	stack stk2;
	StackConstruct (&stk1);
	StackConstruct (&stk2);

	cpu_t cpu;
	cpu.regs = (int *) calloc (4, sizeof (int));
	cpu.ram = (int *) calloc (RAM_SIZE, sizeof (int));
	cpu.stk = &stk1;
	cpu.func_stk = &stk2;

	int rip = 0;
	int cmd = 0;
	int cmd_number = 0;
	int cmd_mode = 0;
	int value = 0;
	while (rip < code_size) {
	// 	printf ("code[%d] = %d\n", rip, code[rip]);
		cmd = code[rip++];
		cmd_number = cmd & CMD_CHECK;
		cmd_mode = (cmd & MODE_CHECK) >> MODE_SET;
		printf ("num = %d mode = %d rip = %d \n", cmd_number, cmd_mode, rip);
		#define DEF_CMD(name, num, type, arg, performance) {	\
			if (cmd_number == num) {							\
				printf ("%s\n", #name);							\
				if (arg) {										\
					value = code[rip++];						\
				}												\
				performance										\
			}													\
		}
		#include "command.h"
		#undef DEF_CMD
	}
}
