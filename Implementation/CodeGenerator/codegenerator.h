
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "../common/common.h"

#define DELIMITER ' '


//it checks if the input is a int float or char
int tokentype(char *t);

//it returns the instruccion for each input
char *codeGenerator(char *i);
