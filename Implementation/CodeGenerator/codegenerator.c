
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include<ctype.h>
//cambiar
bool validOperator(char op){
	return (op=='+' || op=='-' || op=='*' || op=='/' || op=='%');
}
// de que tipo es la salida anterior 
// pueden 
//problema con el espacio
char *concat(char *s1,char *s2){
	int length = strlen(s1) + strlen(s2);
	char *result = (char *) malloc(sizeof(char)*(length + 2));
	int j = strlen(s1);
	int i;
	for(i = 0;i < j;i++){
		result[i] = s1[i];
	}
	result[j] = ' ';
	for(i=0;i<strlen(s2);i++){
		result[i + j + 1 ] = s2[i];
	} 
	result[length + 1] = '\0';
	return result;
}
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
	if(canbefloat) return 1;
	else if(canbeint) return 0;
	else return -1;
	
}
char *codeGenerator(char *i){
	char* buff = (char*) calloc(20, sizeof(char));
	int type = tokentype(i);
	if(type == 0){
			//Error solucionar gcvt pasar a char);
		//code = concat("LDI",gcvt(i,20,buff));
		strcpy(buff, "LDI ");
    strcat(buff, i);
	}
	if(type == 1){
	//	code = concat("LDF",gcvt(i,20,buff));
		strcpy(buff, "LDF ");
    strcat(buff, i);
	}
	else if(type == 3){
		//Solucionar me pide que sea un int
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
//poner en el main

int main()
{

//Hay que usar este
	FILE *archivo;
	FILE *output;
 	char caracteres[100];
 	//archivo = fopen("prueba.txt","r");
	//output = fopen("output.txt","w");
	archivo = stdin;
	output = stdout;
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
	      // Sï¿½lo en la primera pasamos la cadena; en las siguientes pasamos NULL
		    code  = codeGenerator(token);
	      //	writeFile(file,code);
        fprintf(output,"%s\n", code);
        free(code);
		    token = strtok(NULL, delimitador);
        }
    }
	    	
 	
 	    }
           
        }
        fclose(archivo);



    return 0;
}
char convert(int i){
	return i+'0';
}


//leer caracter 
char *readFile(char *fileName)
{
    FILE *file = fopen(fileName, "r");
    char *code;
    size_t n = 0;
    int c;

    if (file == NULL)
        return NULL; //could not open file

    code = malloc(1000);

    while ((c = fgetc(file)) != EOF)
    {
        code[n++] = (char) c;
    }

    // don't forget to terminate with the null character
    code[n] = '\0';        

    return code;
}
