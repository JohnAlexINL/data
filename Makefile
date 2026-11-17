CC = tcc
CCFLAGS = -Os -Wextra -Wall -Werror
OUTPUT = data
CMAIN = src/main.c
$(OUTPUT): clean
	$(CC) $(CMAIN) $(CCFLAGS) $(LDFLAGS) -o $(OUTPUT)
clean:
	rm -rf $(OUTPUT)
install:
	cp $(OUTPUT) /bin/
remove:
	rm /bin/$(OUTPUT)
