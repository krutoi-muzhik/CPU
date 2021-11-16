#define DO_PUSH(value) StackPush(cpu.stk, value)
#define DO_POP StackPop(cpu.stk)
#define DO_OPER(sign) DO_POP sign DO_POP
#define OPER(sign) sign
#define N_CMD(x) x
#define ARG(x) x 
#define TYPE(x) x
#define DO_CMP(comp) if (DO_POP comp DO_POP)
#define DO_JUMP {									\
	switch (cmd_mode) {								\
		case NUM_M:									\
			rip = value;							\
			break;									\
		case REG_M:									\
			rip = cpu.regs[value];					\
			break;									\
		case RAM_NUM_M:								\
			rip =  cpu.ram[value];					\
			break;									\
		case RAM_REG_M:								\
			rip = cpu.ram[cpu.regs[value]];			\
			break;									\
		default:									\
			printf ("ERROR unknown mode JMP\n");	\
	}												\
}

#include "cpu.h"

DEF_CMD (PUSH, N_CMD(1), TYPE(0), ARG(1), {
	// rip++;
	switch (cmd_mode) {
		case NUM_M:
			DO_PUSH(value);
			break;
		case REG_M:
			DO_PUSH(cpu.regs[value]);
			break;
		case RAM_NUM_M:
			DO_PUSH(cpu.ram[value]);
			break;
		case RAM_REG_M:
			DO_PUSH(cpu.ram[cpu.regs[value]]);
			break;
		default:
			printf ("ERROR unknown mode PUSH\n");
	}
})

DEF_CMD (POP, N_CMD(2), TYPE(0), ARG(1), {
	// rip++;
	switch (cmd_mode) {
		case NUM_M:
			DO_POP;
			break;
		case REG_M:
			cpu.regs[value] = DO_POP;
			break;
		case RAM_NUM_M:
			cpu.ram[value] = DO_POP;
			break;
		case RAM_REG_M:
			cpu.ram[cpu.regs[value]] = DO_POP;
			break;
		default:
			printf ("ERROR unknown mode POP\n");
	}
})

DEF_CMD (HLT, N_CMD(0), TYPE(0), ARG(0), {
	printf ("u reached the end without errors\n");
})

DEF_CMD (IN, N_CMD(3), TYPE(0), ARG(0), {
	int value = 0;
	scanf ("%d", &value);
	DO_PUSH(value);
})

DEF_CMD (OUT, N_CMD(4), TYPE(0), ARG(0), {
	int value = 0;
	value = DO_POP;
	printf ("%d\n", value);
})

DEF_CMD (INC, N_CMD(5), TYPE(0), ARG(0), {
	DO_PUSH (DO_POP + 1);
})

DEF_CMD (DEC, N_CMD(6), TYPE(0), ARG(0), {
	DO_PUSH (DO_POP - 1);
})

DEF_CMD (NEG, N_CMD(7), TYPE(0), ARG(0), {
	DO_PUSH ((-1) * DO_POP);
})

DEF_CMD (ADD, N_CMD(8), TYPE(0), ARG(0), {
	DO_PUSH (DO_OPER(+));
})

DEF_CMD (SUB, N_CMD(9), TYPE(0), ARG(0), {
	DO_PUSH (DO_OPER(-));
})

DEF_CMD (MUL, N_CMD(10), TYPE(0), ARG(0), {
	DO_PUSH (DO_OPER(*));
})

DEF_CMD (DIV, N_CMD(11), TYPE(0), ARG(0), {
	DO_PUSH (DO_OPER(/));
})

DEF_CMD (SIN, N_CMD(12), TYPE(0), ARG(0), {
	DO_PUSH (sin (DO_POP));
})

DEF_CMD (COS, N_CMD(13), TYPE(0), ARG(0), {
	DO_PUSH (cos (DO_POP));
})

DEF_CMD (SQRT, N_CMD(14), TYPE(0), ARG(0), {
	DO_PUSH (sqrt (DO_POP));
})

DEF_CMD (JMP, N_CMD(15), TYPE(1), ARG(1), {
	DO_JUMP
})

DEF_CMD (JE, N_CMD(16), TYPE(1), ARG(1), {
	DO_CMP (==) DO_JUMP
})

DEF_CMD (JA, N_CMD(17), TYPE(1), ARG(1), {
	DO_CMP (>) DO_JUMP
})

DEF_CMD (JB, N_CMD(18), TYPE(1), ARG(1), {
	DO_CMP (<) DO_JUMP
})

DEF_CMD (JAE, N_CMD(19), TYPE(1), ARG(1), {
	DO_CMP (>=) DO_JUMP
})

DEF_CMD (JBE, N_CMD(20), TYPE(1), ARG(1), {
	DO_CMP (<=) DO_JUMP
})

// DEF_CMD (CALL, N_CMD(9), TYPE(0), ARG(0), {
	
// })

// DEF_CMD (RET, N_CMD(9), TYPE(0), ARG(0), {
	
// })

#undef DO_PUSH
#undef DO_POP
#undef DO_OPER
#undef OPER
#undef N_CMD
#undef ARG 
#undef TYPE
#undef DO_CMP
#undef DO_JUMP
