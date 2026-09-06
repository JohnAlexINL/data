#include "../include/magic.h"
void parse_magic(char *in) {
	unsigned char buffer[32];
	FILE *target = fopen(in, "rb");
	if (target == NULL) {
		perror("File error");
		type = NULL;
		return;
	}
	if (fread(buffer, 1, sizeof(buffer), target) != 0) {
		perror("fread error");
		return;
	}
	if (buffer[0] == 0x89 && buffer[1] == 0x50 && buffer[2] == 0x4E && buffer[3] == 0x47) {
		type = "PNG Image";
	}
	else if (buffer[0] == 0x7F && buffer[1] == 0x45 && buffer[2] == 0x4C && buffer[3] == 0x46) {
		type = "ELF UNIX Binary";
	}
	else if (buffer[0] == 0x4D && buffer[1] == 0x5A) {
		type = "EXE Windows Binary";
	}
	else if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF) {
		type = "JPEG Image";
	}
	else if (buffer[0] == 0x47 && buffer[1] == 0x49 && buffer[2] == 0x46) {
		type = "GIF Image";
	}
	else if (buffer[0] == 0x42 && buffer[1] == 0x4D) {
		type = "BMP Image";
	}
	else if (buffer[0] == 0x50 && buffer[1] == 0x4B) {
		type = "ZIP Archive";
	}
	else if (buffer[0] == 0x1F && buffer[1] == 0x8B) {
		type = "GZIP Archive";
	}
	else if (buffer[0] == 0x52 && buffer[1] == 0x61 && buffer[2] == 0x72 && buffer[3] == 0x21) {
		type = "RAR Archive";
	}
	else if (buffer[0] == 0x37 && buffer[1] == 0x7A && buffer[2] == 0xBC && buffer[3] == 0xAF && buffer[4] == 0x27 && buffer[5] == 0x1C) {
		type = "7z Archive";
	} else {
		type = "Data (Unknown file)";
	}
	fclose(target);
}
