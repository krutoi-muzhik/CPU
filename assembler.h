#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

enum ASS_SIZES {
	BUF_SIZE = 1024,
	MARK_TAB_SIZE = 10,
	MARK_USE_NUM = 10,
	CMD_SIZE = 10,
	ARG_SIZE = 10
};

enum CHECK {
	MODE_CHECK = (1 << 7) | (1 << 6) | (1 << 5),
	CMD_CHECK = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4)
};

enum SET {
	MODE_SET = 5
};

enum MODES {
	NUM_M = 0,
	REG_M = 1,
	RAM_NUM_M = 2,
	RAM_REG_M = 3
};

typedef struct mark {
	int use_count;
	int mark_usage[MARK_USE_NUM];
	char mark_name[CMD_SIZE];
	int rip;
} mark_t;

void Assembling (const char *input_path, const char *output_path);
int MarkSeek (mark_t *mark_tab, int *tab_size, const char *name, int rip);
