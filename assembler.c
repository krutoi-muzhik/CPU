#include "assembler.h"


#define handle_error(comand) { 							\
	printf (comand); 									\
	printf (" !!! ERROR OCCURED CHECK LOGS !!!\n\n");   \
	exit (EXIT_FAILURE); 								\
}

void
Assembling (const char *input_path, const char *object_path) {

	int *code = (int *) calloc (BUF_SIZE, sizeof (int));
	char *arg_s = (char *) calloc (ARG_SIZE, sizeof (char));

	FILE *input_file;
	if ((input_file = fopen (input_path, "r")) == NULL)
		handle_error ("fopen (input_path)")

	char command[10];
	int value = 0;
	char reg = 0;
	int rip = 0;
	int count = 0;

	while (fscanf (input_file, "%s", command) != EOF) {
		count = 0;
		// printf ("%s   ", command);
		#define DEF_CMD(name, cmd_num, t, arg, performance)					\
			if (strcmp (command, #name) == 0) {								\
				if (arg) {													\
					fscanf (input_file, "%s", arg_s);						\
					sscanf (arg_s, " [%d]%n", &value, &count);				\
					if (count) {											\
						code[rip++] = cmd_num | (RAM_NUM_M << MODE_SET);	\
						code[rip++] = value;								\
						continue;											\
					}														\
					sscanf (arg_s, "%d%n", &value, &count);					\
					if (count) {											\
						code[rip++] = cmd_num | (NUM_M << MODE_SET);		\
						code[rip++] = value;								\
						continue;											\
					}														\
					sscanf (arg_s, " [%cx]%n", &reg, &count);				\
					if (count) {											\
						value = (int) reg - 96;								\
						code[rip++] = cmd_num | (RAM_REG_M << MODE_SET);	\
						code[rip++] = value;								\
						continue;											\
					}														\
					sscanf (arg_s, "%cx%n", &reg, &count);					\
					if (count) {											\
						value = (int) reg - 96;								\
						code[rip++] = cmd_num | (REG_M << MODE_SET);		\
						code[rip++] = value;								\
						continue;											\
					}														\
					code[rip++] = cmd_num | (NUM_M << MODE_SET);			\
					printf ("default\n");									\
				} else {													\
					code[rip++] = cmd_num;									\
				}															\
			}

		#include "command.h"
		#undef DEF_CMD
	}
	fclose (input_file);

	FILE *object_file;
	if ((object_file = fopen (object_path, "wb")) == NULL)
		handle_error ("fopen (object_path)")

	fwrite (code, sizeof (int), rip, object_file);

	fclose (object_file);

	// for (int i = 0; i < rip; i++) {
	// 	// printf ("code[%d] = %d\n", i, code[i]);
	// 	fprintf (object_file, "%d ", code[i]);
	// }
}

void
TextClean (char *text) {

}