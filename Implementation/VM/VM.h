//AUTHOR: Andrés Otero García
#ifndef VM_MODULE
#define VM_MODULE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../stack/stack.h"
#include "../token/token.h"
#include "../common/common.h"

#define INSTR 7 //number of instructions
#define INSTR_CHARS 3 //number of characters per instruction code

#define ZERO 0.00

int transformToDouble(Token* t, double* value);
Token* operateTokens(Token* t1, char op, Token* t2);
int instruction_index(char* buffer);
int VM(FILE * in_file, FILE * out_file, Stack* s);

#endif
