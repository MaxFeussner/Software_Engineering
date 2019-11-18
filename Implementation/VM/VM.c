#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../stack/stack.h"
#include "../token/token.h"

#define INSTR 7 //number of instructions
#define INSTR_CHARS 3 //number of characters per instruction code

//constant vector of instructions available
const char* INSTRUCTION_STRING[INSTR] = {"LDI", "LDF", "ADD", "SUB", "MUL", "DIV", "MOD"};

bool validOperator(char op){
	return (op=='+' || op=='-' || op=='*' || op=='/' || op=='%');
}

int transformToDouble(Token* t, double* value){
	if(getID(t)==INTEGER_ID){
		int aux = *(int*) getValue(t);
		*value = aux;
		//printf("double = %lf\n", *value);
	}
	else if(getID(t)==DOUBLE_ID){
		*value = *(double*) getValue(t);
		//printf("double = %lf\n", *value);
	}
	else return -1;
	return 0;
}


/*
 * Pre: "t" is a valid UNARY operator or an OPERATOR as is defined in token.h.
 * 		"output" is a pointer to a valid, open and writeable file
 * 		let: "top" be the top of stack "s" and "n" be the number of elements in "s"
 * Post: if n==0 or the precedence of "t" greater than "top", "t" has been pushed to the top
 * 		 otherwise, the elements have been popped and printed until the precedence of all the elements in "s" is less or equal to "t"
 */
Token* operateTokens(Token* t1, char op, Token* t2){

	if(!validOperator(op)){
		fprintf(stderr, "Unknown operand \'%c\' in function operateTokens\n", op);
		return NULL;	
	}


	Token* resultToken = createToken(DOUBLE_ID);
	double v1, v2, res;

	if(transformToDouble(t1, &v1) != 0){
		fprintf(stderr, "Operation not allowed with token t1 of type %d\n", getID(t1));
		return NULL;
	}
	if(transformToDouble(t2, &v2) != 0){
		fprintf(stderr, "Operation not allowed with token t2 of type %d\n", getID(t2));
		return NULL;
	}
	
	switch(op){
		case '+':
			res = v1 + v2;
			//printf("%lf+%lf=%lf\n", v1,v2,res);
			setValue(resultToken, &res, sizeof(double));
			break;
		case '-':
			res = v1 - v2;
			//printf("%lf-%lf=%lf\n", v1,v2,res);
			setValue(resultToken, &res, sizeof(double));
			break;
		case '*':
			res = v1 * v2;
			//printf("%lf*%lf=%lf\n", v1,v2,res);
			setValue(resultToken, &res, sizeof(double));
			break;
		case '/':
			res = v1 / v2;
			//printf("%lf/%lf=%lf\n", v1,v2,res);
			setValue(resultToken, &res, sizeof(double));
			break;
		case '%':
			res = fmod(v1, v2);
			//printf("%lfmod%lf=%lf\n", v1,v2,res);
			setValue(resultToken, &res, sizeof(double));
			break;
	}
	return resultToken;
}

int instruction_index(char* buffer){
	int result = -1;
	for(int i = 0; i < INSTR; i++){
		if(strcmp(buffer, INSTRUCTION_STRING[i])==0){
			result = i;
			break;
		}
	}
	return result;
}



/*
 * Pre: input file (if defined with the option -i, otherwise standard input) has the following format
 *			SPC1:X1
 * 			SPC2:X2
 * 		where SPCi are the specifier strings of the token types (defined above) and Xi are values
 * 		of such type.
 * Post: output file (if defined with the option -o, otherwise standard output) contains the operations from the input file in postfix notation
 */
int main(int argc, char** argv){
	int i = 1;
	FILE * in_file = NULL;
	FILE * out_file = NULL;
	for(i; i < argc; i++){
		if(strcmp(argv[i], "-i")==0){	//if input file is defined
			in_file = fopen(argv[++i],"r");
			if(in_file == NULL){
				fprintf(stderr, "Can't open input file %s\nUsing standard input instead...\n", argv[i]);
				
			}
		}
		else if(strcmp(argv[i], "-o")==0){ //if output file is defined
			out_file = fopen(argv[++i],"w");
			if(in_file == NULL){
				fprintf(stderr, "Can't write on file %s\nUsing standard output instead...\n", argv[i]);
			}
		}
	}
	if(in_file == NULL) in_file = stdin; //if input file wasn't defined or there were errors, use standard input
	if(out_file == NULL) out_file = stdout; //if output file wasn't defined or there were errors, use standard output

	char buffer[INSTR_CHARS + 1];
	char* aux = NULL;
	size_t aux2 = 0;
	size_t line_size = INSTR_CHARS;
	ssize_t readBytes = 0;
	Stack* s = newStack();
	Token* t;
	readBytes = fread(buffer, sizeof(char), line_size, in_file);
	while(readBytes > 0){	//if the line was valid

		int instr = instruction_index(buffer);
		if(instr >= 0 && instr < INSTR){
			if(instr == 0){
				t = createToken(INTEGER_ID);
				int intNumber;
				fscanf(in_file, " %d", &intNumber);
				setValue(t, &intNumber, sizeof(int));
			}
			else if(instr == 1){
				t = createToken(DOUBLE_ID);
				double fpNumber;
				fscanf(in_file, " %lf", &fpNumber);
				setValue(t, &fpNumber, sizeof(double));
			}
			else{
				Node* auxNode = popElement(s);
				Token* secondOperand = (Token*) getData(auxNode);
				free(auxNode);
				auxNode = popElement(s);
				Token* firstOperand = (Token*) getData(auxNode);
				free(auxNode);
				switch(instr){
					case 2:
						t = operateTokens(firstOperand, '+', secondOperand);
						break;
					case 3:
						t = operateTokens(firstOperand, '-', secondOperand);
						break;
					case 4:
						t = operateTokens(firstOperand, '*', secondOperand);
						break;
					case 5:
						t = operateTokens(firstOperand, '/', secondOperand);
						break;
					case 6:
						t = operateTokens(firstOperand, '%', secondOperand);
						break;
				}
				free(firstOperand);
				free(secondOperand);
			}
		pushElement(s, t);
		}
		else fprintf(stderr, "Error: Unknown operation %s\n", buffer);

		
		getline(&aux, &aux2, in_file);
		free(aux);
		aux = NULL;
		aux2 = 0;

		readBytes = fread(buffer, sizeof(char), line_size, in_file);//read next line
	}
	Node* auxNode2 = popElement(s);
	Token* auxToken = getData(auxNode2);
	
	double finalResult = *(double*) getValue(auxToken);
	free(auxNode2);
	free(auxToken);
	if(!isEmpty(s)) fprintf(stderr, "Error: Stack is not empty!\n");
	else fprintf(out_file, "%lf\n", finalResult);

	fclose(in_file);
	fclose(out_file);
	destroyElements(s);
	free(s);
	return 0;
}
