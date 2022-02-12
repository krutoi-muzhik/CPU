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
	mark_t *mark_tab = (mark_t *) calloc (MARK_TAB_SIZE, sizeof (mark_t));
	int tmp;
	int mark_num = 0;
	int count = 0;

	while (fscanf (input_file, "%s", command) != EOF) {
		count = 0;
		// printf ("%s   ", command);
		#define DEF_CMD(name, cmd_num, t, arg, performance)	{					\
			if (strcmp (command, #name) == 0) {									\
				if (t) {														\
					code[rip++] = cmd_num;										\
					fscanf (input_file, "%s", arg_s);							\
					if (tmp = MarkSeek (mark_tab, &mark_num, arg_s, rip)) {		\
						code[rip++] = tmp;										\
						continue;												\
					} else {													\
						code[rip++] = -1;										\
						continue;												\
					}															\
				}																\
				if (arg) {														\
					fscanf (input_file, "%s", arg_s);							\
					sscanf (arg_s, " [%d]%n", &value, &count);					\
					if (count) {												\
						code[rip++] = cmd_num | (RAM_NUM_M << MODE_SET);		\
						code[rip++] = value;									\
						continue;												\
					}															\
					sscanf (arg_s, "%d%n", &value, &count);						\
					if (count) {												\
						code[rip++] = cmd_num | (NUM_M << MODE_SET);			\
						code[rip++] = value;									\
						continue;												\
					}															\
					sscanf (arg_s, " [%cx]%n", &reg, &count);					\
					if (count) {												\
						value = (int) reg - 96;									\
						code[rip++] = cmd_num | (RAM_REG_M << MODE_SET);		\
						code[rip++] = value;									\
						continue;												\
					}															\
					sscanf (arg_s, "%cx%n", &reg, &count);						\
					if (count) {												\
						value = (int) reg - 96;									\
						code[rip++] = cmd_num | (REG_M << MODE_SET);			\
						code[rip++] = value;									\
						continue;												\
					}															\
					code[rip++] = cmd_num | (NUM_M << MODE_SET);				\
					printf ("default\n");										\
				} else {														\
					code[rip++] = cmd_num;										\
				}																\
			} else {															\
				if (command[strlen (command) - 1] == ':') {						\
					command[strlen (command) - 1] = '\0';						\
					mark_tab[mark_num].rip = rip;								\
					strcpy (mark_tab[mark_num].mark_name, command);				\
					mark_num++;													\
				}																\
			}																	\
		}

		#include "command.h"
		#undef DEF_CMD
	}

	fclose (input_file);


	for (int i = 0; i < mark_num; i++) {
		for (int j = 0; j < mark_tab[i].use_count; j++) {
			printf ("%s  %d\n", mark_tab[i].mark_name, mark_tab[i].rip);
			code[mark_tab[i].mark_usage[j]] = mark_tab[i].rip;
		}
	}

	FILE *object_file;
	if ((object_file = fopen (object_path, "wb")) == NULL)
		handle_error ("fopen (object_path)")

	fwrite (code, sizeof (int), rip, object_file);

	fclose (object_file);

	for (int i = 0; i < rip; i++) {
		printf ("code[%d] = %d\n", i, code[i]);
	}
}

int
MarkSeek (mark_t *mark_tab, int *tab_size, const char *name, int rip) {
	int i = 0;
	while (strcmp (mark_tab[i].mark_name, name) != 0) {
		if (i == *tab_size) {
			*tab_size++;
			strcpy (mark_tab[*tab_size].mark_name, name);
			mark_tab[*tab_size].rip = -1;
			mark_tab[*tab_size].mark_usage[0] = rip;
			mark_tab[*tab_size].use_count = 1;
			return 0;
		}
		i++;
	}

	return mark_tab[i].rip;
}
