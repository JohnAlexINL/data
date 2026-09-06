#include "../include/magic.h"
long b;
long mb;
long kb;
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
	if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
		printf("Usage: data [target]\n");
		printf("-h --help - Shows this message\n");
		return 0;
	}
	if (parse_magic(argv[1]) == 1) {
		return 1;
	}
	if (parse_size(argv[1]) == 1) {
		return 1;
	}
	printf("%s\n", type);
	if (kb >= 1024) {
		printf("%ld MB\n", mb);
	}
	else if (mb < 1024) {
		if (kb < 1024) {
			if (b >= 1024) {
				printf("%ld KB\n", kb);
			}
			else {
				printf("%ld B\n", b);
			}
		}
	}
	else {
		printf("%ld B\n", b);
	}
	return 0;
}