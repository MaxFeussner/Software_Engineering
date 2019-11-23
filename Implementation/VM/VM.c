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

//constant vector of instructions available
const char* INSTRUCTION_STRING[INSTR] = {"LDI", "LDF", "ADD", "SUB", "MUL", "DIV", "MOD"};


/*
 * Pre: t and value are not NULL pointer
 * Post: if t had id "INTEGER_ID" or "DOUBLE_ID", assigned the value to value and returned 0
 * 	 otherwise, returned -1
 */
int transformToDouble(Token* t, double* value){
	if(getID(t)==INTEGER_ID){
		int aux = *(int*) getValue(t);
		*value = aux;
	}
	else if(getID(t)==DOUBLE_ID){
		*value = *(double*) getValue(t);
	}
	else return -1;
	return 0;
}


/*
 * Pre: ---
 * Post: if op was a valid operator and t1 and t2 were not NULL, returned a token with id "DOUBLE_ID"
 * 	 holding the value of making the operation v1 op v2, where v1 and v2 are the numerical values
 * 	 in tokens t1 and t2.
 *	 otherwise, it printed an error message and returned NULL
 */
Token* operateTokens(Token* t1, char op, Token* t2){

	if(!validOperator(op)){
		fprintf(stderr, "Unknown operand \'%c\' in function operateTokens\n", op);
		return NULL;	
	}
	if(t1 == NULL){
		fprintf(stderr, "Cannot operate a NULL token on pointer t1\n");
		return NULL;
	}
	if(t2 == NULL){
		fprintf(stderr, "Cannot operate a NULL token on pointer t2\n");
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
			setValue(resultToken, &res, sizeof(double));
			break;
		case '-':
			res = v1 - v2;
			setValue(resultToken, &res, sizeof(double));
			break;
		case '*':
			res = v1 * v2;
			setValue(resultToken, &res, sizeof(double));
			break;
		case '/':
			res = v1 / v2;
			setValue(resultToken, &res, sizeof(double));
			break;
		case '%':
			res = fmod(v1, v2);
			setValue(resultToken, &res, sizeof(double));
			break;
	}
	return resultToken;
}

/*
 * Pre: INSTRUCTION_STRING is a vector of INSTR strings containing the identifiers of all the operations
 *	the Virtual Machine accepts
 * Post: returned the index in INSTRUCTION_STRING of the instruction stored in buffer.
 *	 if it was not found in the vector, returned -1
 */
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
 * Pre: input file (if defined with the option -i, otherwise standard input) has a series of instructions from
 * 	the vector INSTRUCTION_STRING.
 * 	All instructions in INSTRUCTION_STRING must be of length INSTR_CHARS characters
 * Post: output file (if defined with the option -o, otherwise standard output) contains the result of performing
 * 	 such operations if notation was correct.
 *	 if an unknown operation was found, printed an error message on stderr
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

	char buffer[INSTR_CHARS + 1];	//buffer to read instructions
	char* aux = NULL;		//buffer to ignore lines
	size_t aux2 = 0;		//size_t variable (used to ignore lines)
	size_t line_size = INSTR_CHARS;	//number of characters for every instruction
	ssize_t readBytes = 0;		//variable where the number of read bytes will be stored after every read
	Stack* s = newStack();		//stack where all numbers will be pushed
	Token* t;
	readBytes = fread(buffer, sizeof(char), line_size, in_file);	//read first instruction
	while(readBytes > 0){	//if the instruction was valid

		int instr = instruction_index(buffer);	//get instruction index
		if(instr >= 0 && instr < INSTR){	//if it's within bounds
			if(instr == 0){	//LDI
				t = createToken(INTEGER_ID);
				int intNumber;
				fscanf(in_file, " %d", &intNumber);	//read integer
				setValue(t, &intNumber, sizeof(int));
			}
			else if(instr == 1){	//LDF
				t = createToken(DOUBLE_ID);
				double fpNumber;
				fscanf(in_file, " %lf", &fpNumber);	//read floating point number
				setValue(t, &fpNumber, sizeof(double));
			}
			else{
				Node* auxNode = popElement(s);
				Token* secondOperand = (Token*) getData(auxNode);	//get token from popped element
				free(auxNode);
				auxNode = popElement(s);
				Token* firstOperand = (Token*) getData(auxNode);	//get token from popped element
				free(auxNode);
				switch(instr){
					case 2:	//ADD
						t = operateTokens(firstOperand, '+', secondOperand);
						break;
					case 3: //SUB
						t = operateTokens(firstOperand, '-', secondOperand);
						break;
					case 4: //MUL
						t = operateTokens(firstOperand, '*', secondOperand);
						break;
					case 5: //DIV
						t = operateTokens(firstOperand, '/', secondOperand);
						break;
					case 6: //MOD
						t = operateTokens(firstOperand, '%', secondOperand);
						break;
				}
				free(firstOperand);
				free(secondOperand);
			}
			if(t != NULL) pushElement(s, t);	//push result
			else fprintf(stderr, "Error: t is NULL. Couldn't perform operation \"%s\"", buffer);
		}
		else fprintf(stderr, "Error: Unknown operation %s\n", buffer);

		//ignore the rest of the line
		getline(&aux, &aux2, in_file); 
		free(aux);
		aux = NULL;
		aux2 = 0;

		readBytes = fread(buffer, sizeof(char), line_size, in_file);	//read next instruction
	}
	Node* auxNode2 = popElement(s);	//pop last element where the result is stored
	Token* auxToken = getData(auxNode2);
	
	double finalResult = *(double*) getValue(auxToken);
	free(auxNode2);
	free(auxToken);
	if(!isEmpty(s)) fprintf(stderr, "Error: Stack is not empty!\n");	//something went wrong (probably missing operation)
	else fprintf(out_file, "%lf\n", finalResult);	//print result in out_file

	//free allocated memory
	fclose(in_file);
	fclose(out_file);
	destroyElements(s);
	free(s);
	return 0;
}
