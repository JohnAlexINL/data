#include "../include/magic.h"
int parse_magic(char *in) {
	unsigned char buffer[32];
	FILE *target = fopen(in, "rb");
	if (target == NULL) {
		perror("Error");
		return 1;
	}
	size_t bytes_read = fread(buffer, 1, sizeof(buffer), target);
	if (bytes_read == 0) {
		perror("Error");
		return 1;
	}
	// formats
	if (buffer[0] == 0x89 && buffer[1] == 0x50 && buffer[2] == 0x4E && buffer[3] == 0x47) {
		type = "PNG Image";
	}
	else if (buffer[0] == 0x23 && buffer[1] == 0x21) {
		type = "Script";
	}
	else if (buffer[0] == 0x49 && buffer[1] == 0x44 && buffer[2] == 0x33) {
		type = "MP3 Audio";
	}
	else if (buffer[4] == 0x66 && buffer[5] == 0x74 && buffer[6] == 0x79) {
		type = "MP4 Video";
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
	else if (buffer[0] == 0x25 && buffer[1] == 0x50 && buffer[2] == 0x44 && buffer[3] == 0x46) {
		type = "PDF Document";
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
		type = "Data";
	}
	fclose(target);
	return 0;
}
long get_size(FILE *f) {
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	rewind(f);
	return size;
}
int parse_size(char *in) {
	FILE *target = fopen(in, "rb");
	if (target == NULL) {
		return 1;
	}
	b = get_size(target);
	kb = b / 1024;
	mb = kb / 1024;
	fclose(target);
	return 0;
}