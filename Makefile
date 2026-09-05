CC = gcc
CCFLAGS = -O3 -Wextra -Wall -Werror
LDFLAGS = 
OUTPUT = data
CFILES = src/*
$(OUTPUT):
	$(CC) $(CFILES) $(CCFLAGS) $(LDFLAGS) -o $(OUTPUT)
clean:
	rm -rf $(OUTPUT)
install:
	cp $(OUTPUT) /bin/
remove:
	rm /bin/$(OUTPUT)