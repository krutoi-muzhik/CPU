ass: assm/main_ass.c assm/assembler.c stack/stack.c
	gcc assm/main_ass.c assm/assembler.c stack/stack.c -lm -o ass
cpu: proc/main_cpu.c proc/cpu.c stack/stack.c
	gcc proc/main_cpu.c proc/cpu.c stack/stack.c -lm -o cpu