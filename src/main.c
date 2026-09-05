#include "../include/magic.h"
char *type;
int main(int argc, char* argv[]) {
	if (argc > 2) {
		printf("Too many options\n");
		return 1;
	}
	if (argc < 2) {
		printf("Too few options\n");
		return 1;
	}
	parse_magic(argv[1]);
	if (type == NULL) {
		return 1;
	}
	printf("%s\n", type);
}