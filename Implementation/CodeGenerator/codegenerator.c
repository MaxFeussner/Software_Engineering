//AUTHOR: Juan Vercher

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "../common/common.h"

#define DELIMITER ' '


//it checks if the input is a int float or char
int tokentype(char *t){
	bool canbeint = true;
	bool canbefloat = false;
	bool dotfound = false;
	unsigned int len = strlen(t);
	if(len == 0) return -2;
	if(len == 1 && validOperator(t[0])){
		return 3;
	}
	for(int i = 0 ;i < strlen(t);i++){
		if(t[i]=='.'){
			if(!dotfound){
				dotfound = true;
				canbefloat = true;
				canbeint = false;
			}
			else{
				canbefloat = false;
				break;
			}
		}
		if(!isdigit(t[i])){
			canbeint = false;
		}
	}
	if(canbefloat) { return 1; }
	else if(canbeint) { return 0;}
	else return -1;
	
}

//it returns the instruccion for each input
char *codeGenerator(char *i){
	char* buff = (char*) calloc(20, sizeof(char));
	int type = tokentype(i);
	if(type == -2);
	else if(type == 0){	
		strcpy(buff, "LDI ");
    		strcat(buff, i);
	}
	else if(type == 1){
		strcpy(buff, "LDF ");
   		strcat(buff, i);
	}
	else if(type == 3){
		switch(i[0]){	//if it's an operator, we only need the first character
			case '+':
				strcpy(buff, "ADD");
				break;
			case '*':
				strcpy(buff, "MUL");
				break;
			case '-':
				strcpy(buff, "SUB");
				break;
			case '/':
				strcpy(buff, "DIV");
				break;
			case '%':
				strcpy(buff, "MOD");
				break;
			default:
				fprintf(stderr,"Error: Unkown operator %c", i[0]);
		}
	}
	return buff;

}
