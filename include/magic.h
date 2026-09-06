#ifndef MAGIC_H
#define MAGIC_H
#include <stdio.h>
#include <string.h>
extern char *type;
extern long b;
extern long kb;
extern long mb;
void parse_magic(char *in);
void parse_size(char *in);
#endif