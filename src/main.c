#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "magic.h"
#include "magic.c"
#include "license.h"

#define UNKNOWN "Unknown file type"

filetype_t *type;
int main(int argc, char* argv[]) {
	if (argc > 2) { printf("Too many options\n"); return 1; }
	if (argc < 2) { printf("Too few options\n"); return 1; }
	if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
		printf("Usage: data [target]\n");
		printf("-h --help - Shows this message\n");
		return 0;
	}
	if (strcmp(argv[1], "--license") == 0 || strcmp(argv[1], "-l") == 0) {
		printf("License:\n%s\n", LICENSE);
		return 0;
	}
	if (parse_magic(argv[1]) == 1) { return 1; }
	if (parse_size(argv[1]) == 0) { return 1; }
	// Truncate the input filename if too long
	const long maxlen = 48;
	char * outname = argv[1];
	int arglen = strlen(argv[1]);
	if ( arglen > maxlen ) {
		outname = (char *)(argv[1] + arglen - maxlen );
		outname[0] = '.'; outname[1] = '.'; outname[2] = '.'; }
	// Combine all available information into printable format, then output
	char buffer[128] = { 0 };
		strncat(buffer, argv[0], sizeof(buffer));
		strncat(buffer, ": ", sizeof(buffer));
	if ( type == NULL )
		{ strncat(buffer, UNKNOWN, sizeof(buffer)); }
	else {
		strncat(buffer, type->name, sizeof(buffer));
		if ( type->info != NULL ) {
			strncat(buffer, ", ", sizeof(buffer));
			strncat(buffer, type->info, sizeof(buffer));
		}
		if ( type->mime != NULL ) {
			strncat(buffer, " (", sizeof(buffer));
			strncat(buffer, type->mime, sizeof(buffer));
			strncat(buffer, ")", sizeof(buffer));
		}
	}
	puts(buffer); // Puts automatically adds a newline character for us

	// Scale the filesize then print
	char prefix[] = " KMGTP";
	long size = parse_size(argv[1]);
	int scale = parse_scale(size); if (scale > 4) { scale = 4; }
	printf("Size: %ld %cB\n",
		size >> (scale * 10),
		prefix[scale]
	);
	return 0;
}
