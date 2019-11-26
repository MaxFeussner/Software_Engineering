//AUTHOR: Andrés Otero García
#ifndef COMMON_CALC
#define COMMON_CALC

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void openIOFiles(int argc, char** argv, FILE ** in_file, FILE ** out_file);
void ignoreLine(FILE* input);
bool validOperator(char op);
ssize_t getUntilDelim(char **lineptr, size_t *n, int delim, FILE *stream);

#endif
