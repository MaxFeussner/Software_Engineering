//AUTHOR: Andrés Otero García
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../common/common.h"
#include "../stack/stack.h"
#include "../token/token.h"

#define DELIMITER ':'
#define INTEGER_SPC "In"
#define FLOATING_SPC "Fp"
#define LEFTP_SPC "Lp"
#define RIGHTP_SPC "Rp"
#define UNARY_SPC "Un"
#define OPERATOR_SPC "Op"

//testing purposes
#define TYPES 6


int precedence(Token* t);
void processValue(FILE* input, char* format, Token* t, void* value, size_t size);
Token* readToken(FILE* input);
void processOperator(Stack* s, Token* t, FILE* output);
int infix_to_postfix(FILE* in_file, FILE* out_file, Stack* s);


