
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include<ctype.h>
//it checks if is valid the operator
bool validOperator(char op){
	return (op=='+' || op=='-' || op=='*' || op=='/' || op=='%');
}
//it checks if the input is a int float or char
int tokentype(char *t){
	bool canbeint = true;
	bool canbefloat = false;
	bool dotfound = false;
	unsigned int len = strlen(t);
	if(len == 1 && validOperator(t[0])){
		return 3;
	}
	for(int i = 0 ;i <strlen(t);i++){
		
		
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
	if(canbefloat) {printf("es float\n"); return 1; }
	else if(canbeint) {printf("es int\n"); return 0;}
	else return -1;
	
}
//it returns the instruccion for each input
char *codeGenerator(char *i){
	char* buff = (char*) calloc(20, sizeof(char));
	int type = tokentype(i);
	if(type == 0){
			
		strcpy(buff, "LDI ");
    strcat(buff, i);
	}
	if(type == 1){
	
		strcpy(buff, "LDF ");
    strcat(buff, i);
	}
	else if(type == 3){
	
		switch(i[0]){
		
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
				printf("Error there is no case");
		}
	}
		return buff;

}

//calling the other function it writes in the output the instruccions
int main()
{

	FILE *archivo;
	FILE *output;
 	char caracteres[100];
 	archivo = fopen("prueba.txt","r");
	output = fopen("output.txt","w");
 	if (archivo == NULL)
 		exit(1);
 	else
        {
 	       while (feof(archivo) == 0)
 	    {
 	    	fgets(caracteres,100,archivo);
      	char *delimitador = " ";
	      char *token = strtok(caracteres, delimitador);
        char *code;
	
	      if(token != NULL){
	      while(token != NULL){
	     
		    code  = codeGenerator(token);
        fprintf(output,"%s\n", code);
        free(code);
		    printf("Token: %s\n", token);
		    token = strtok(NULL, delimitador);
        }
    }
	    	
 	
 	    }
           
        }
        fclose(archivo);



    return 0;
}
