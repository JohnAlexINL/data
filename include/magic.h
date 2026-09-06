#ifndef MAGIC_H
#define MAGIC_H
#include <stdio.h>
#include <string.h>
extern char *type;
extern long b;
extern long kb;
extern long mb;
extern long gb;
int parse_magic(char *in);
int parse_size(char *in);
#endif