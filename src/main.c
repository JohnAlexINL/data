#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "magic.h"
#include "magic.c"
#include "license.h"

#define AUTHOR			COPYRIGHT " " SOURCE
#define COPYRIGHT		"(C) 2026, Blood Rose Records"
#define SOURCE			"<https://bloodrose.org>"
#define USAGE			"Usage: data <filename>\n"
#define VERSION_MSG 	"data v " VERSION
#define VERSION	\
	STR(VERSION_MAJOR) "." \
	STR(VERSION_MINOR) "." \
	STR(VERSION_PATCH)
	#define STRX(x) #x
	#define STR(x) STRX(x)
#define VERSION_MAJOR	1
#define VERSION_MINOR	5
#define VERSION_PATCH	0
#define UNKNOWN "Unknown file type"

const char HELP [] = "" \
	VERSION_MSG "\n" \
	USAGE \
	"Prints information about file type, media type, and file size\n" \
	"    -h, --help     display this help message\n" \
	"    -v, --version  display the version information\n" \
	"    -l, --license  display the software license text in full";

filetype_t *type;
int main(int argc, char* argv[]) {
	if (argc != 2) { printf("%s\n", HELP); return 1; }
	if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
		{ printf("%s\n", HELP); return 0; }
	if (strcmp(argv[1], "--license") == 0 || strcmp(argv[1], "-l") == 0)
		{ printf("%s\n%s\n", AUTHOR, LICENSE); return 0; }
	if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0)
		{ printf("%s\n", VERSION_MSG); return 0; }
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
