extern filetype_t * type;
extern filetype_t magic_table [];

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

	type = NULL;
	int i; for (i=0; i<(int)magic_table_size; i++) {
		filetype_t * test = &magic_table[i];
		int max = test->len;
		char * magic = ( test->magic );
		char * reference = (char *)( buffer + test->off );
		int status = strncmp(reference, magic, max);
		if ( status == 0 ) { type = test; break; }
	}

	fclose(target);
	return 0;
}

long parse_size(char *in) {
	FILE *target = fopen(in, "rb");
	if (target == NULL) { perror("Error"); return 0; }
	long yield = get_size(target);
	fclose(target);
	return yield;
}

long get_size(FILE *f) {
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	rewind(f);
	return size;
}

int parse_scale(long in) {
	int i=0;
	while(in >= 1024) { in >>= 10; i++; }
	return i;
}
