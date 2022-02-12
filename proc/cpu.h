#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <math.h>
#include "../stack/stack.h"

enum CPU_SIZES {
	CODE_SIZE = 1024,
	RAM_SIZE = 1024
};

enum CHECK {
	MODE_CHECK = (1 << 7) | (1 << 6) | (1 << 5),
	CMD_CHECK = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4)
};

enum MODES {
	NUM_M = 0,
	REG_M = 1,
	RAM_NUM_M = 2,
	RAM_REG_M = 3
};

enum SET {
	MODE_SET = 5
};

typedef struct processor {
	stack *stk;
	stack *func_stk;
	int *regs;
	int *ram;
} cpu_t;

void Processing (const char *object);
