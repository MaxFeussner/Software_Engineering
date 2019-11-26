#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include<ctype.h>
#include <ctap.h>
#include "codegenerator.h"

TESTS {

    //test for tokentype
    ok(tokentype("+") == 3,"It's a symbol");
    ok(tokentype("-") == 3,"It's a symbol");
    ok(tokentype("*") == 3,"It's a symbol");
    ok(tokentype("/") == 3,"It's a symbol");
    ok(tokentype("%") == 3,"It's a symbol");
    ok(tokentype("43") == 0,"It's an int");
    ok(tokentype("43.43") == 1,"It's an float");
    ok(tokentype("H") == -1,"It's an error");
    //test for codegenerator
    is(codeGenerator("+"),"ADD","It's ADD");
    is(codeGenerator("-"),"SUB","It's SUB");
    is(codeGenerator("/"),"DIV","It's DIV");
    is(codeGenerator("*"),"MUL","It's MUL");
    is(codeGenerator("%"),"MOD","It's MOD");
    is(codeGenerator("43"),"LDI 43","It's an int");
    is(codeGenerator("43.43"),"LDF 43.43","It's a float");
    is(codeGenerator("HJ"),"","It's not recognized");
    
    
    
}
