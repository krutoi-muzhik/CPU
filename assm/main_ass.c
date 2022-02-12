#include "assembler.h"

int
main () {
	const char *input_path = "input.txt";
	const char *object_path = "object.txt";

	Assembling (input_path, object_path);

	return 0;
}
