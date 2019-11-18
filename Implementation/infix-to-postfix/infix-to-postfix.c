#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"
#include "token.h"

#define DELIMITER ':'
#define INTEGER_SPC "In:"
#define FLOATING_SPC "Fp:"
#define LEFTP_SPC "Lp:"
#define RIGHTP_SPC "Rp:"
#define UNARY_SPC "Un:"
#define OPERATOR_SPC "Op:"

/*
 * Pre: "t" is a valid pointer to a Token (not null)
 * 		let p(op) be the precedence of the operator stored in the value field of Token "t"
 * Post: p(+) = p(-) < p(unary+) = p(unary-) < p(*) = p(/) = p(%)
 */
int precedence(Token* t){
	char op = *(char*)getValue(t);
	if(getID(t)==UNARY_ID) return 3;
	else if(op=='+' || op=='-') return 2;
	else if(op=='*' || op=='/' || op=='%') return 4;
	else if(op=='(') return 0;
	else return -1;
}


/*
 * Pre: input is a pointer to a text file
 * Post: read a line of "input" without storing it
 */
void ignoreLine(FILE* input){
	char* ignore=NULL;
	size_t n = 0;
	getline(&ignore, &n, input);
	free(ignore);
}

/*
 * Pre: input is a valid pointer to a text file with the following format:
 * 			SPC1:X1
 * 			SPC2:X2
 * 		where SPCi are the specifier strings of the token types (defined above) and Xi are values
 * 		of such type, and ":" is the same delimiter as defined above.
 * 		"specifier" is an integer that defines what type of value is going to be read, as defined
 * 		in token.h
 * 		"format" is the string format that has to be read
 * 		"value" is able to store a value of the type that has to be read
 * 		"size" is the size in bytes of the type of "value"
 * Post: "t" is now a pointer to a token with the specified id, following the define statements in
 * 		 token.h
 * 		 "value" stores the value of the token
 * 		 If the input was invalid, t is a null pointer, the line has been ignored and the memory in the previous address of "t" has been freed.
 * 		 Otherwise, the line has been correctly read.
 */
void processValue(FILE* input, char* format, Token* t, void* value, size_t size){
	int nRead = fscanf(input, format, value); // stores in "value" the value read with format "format" from "input"
	if(nRead > 0 && nRead != EOF){ // if there were no errors
		setValue(t, value, size);	// store the read value in the token
	}
	else{ // if there were errors
		ignoreLine(input);
		free(t);
		t = NULL;
	}
}


/* 
 * Pre: input is a valid pointer to a text file with the following format:
 * 			SPC1:X1
 * 			SPC2:X2
 * 		where SPCi are the specifier strings of the token types (defined above) and Xi are values
 * 		of such type.
 * Post: returned a pointer to a Token which contains an integer which identifies the type of
 * 		 the data (as described in token.h) and the value of the token.
 * 		 If the input is invalid or unknown, the function returned a NULL pointer
 * 		 returned eof_token() if there was nothing to read
 */
Token* readToken(FILE* input){
	char* typeSpecifier = NULL;
	size_t bufsize = 0;
	Token* t;
	if(getdelim(&typeSpecifier, &bufsize, DELIMITER, input)>0){ // read specifier
		if(strcmp(typeSpecifier, INTEGER_SPC)==0){			//if it's an integer
			int value;
			t = createToken(INTEGER_ID);
			processValue(input, " %d\n", t, &value, sizeof(int));
		}
		else if(strcmp(typeSpecifier, FLOATING_SPC)==0){	//if it's a floating point number
			double value;
			t = createToken(DOUBLE_ID);
			processValue(input, " %lf\n", t, &value, sizeof(double));
		}
		else if(strcmp(typeSpecifier, LEFTP_SPC)==0){		//if it's a left parenthesis
			char value;
			t = createToken(LEFTP_ID);
			processValue(input, " %c\n", t, &value, sizeof(char));
		}
		else if(strcmp(typeSpecifier, RIGHTP_SPC)==0){		//if it's a right parenthesis
			char value;
			t = createToken(RIGHTP_ID);
			processValue(input, " %c\n", t, &value, sizeof(char));
		}
		else if(strcmp(typeSpecifier, UNARY_SPC)==0){		//if it's a unary operator
			char value;
			t = createToken(UNARY_ID);
			processValue(input, " %c\n", t, &value, sizeof(char));
		}
		else if(strcmp(typeSpecifier, OPERATOR_SPC)==0){	//if it's a binary operator
			char value;
			t = createToken(OPERATOR_ID);
			processValue(input, " %c\n", t, &value, sizeof(char));
		}
		else{	//invalid option (line is ignored)
			ignoreLine(input);
		}
	} 
	else{	//"t" is an EOF token if nothing was read
		t = eof_token();
	}
	return t;
}

/*
 * Pre: "t" is a valid UNARY operator or an OPERATOR as is defined in token.h.
 * 		"output" is a pointer to a valid, open and writeable file
 * 		let: "top" be the top of stack "s" and "n" be the number of elements in "s"
 * Post: if n==0 or the precedence of "t" greater than "top", "t" has been pushed to the top
 * 		 otherwise, the elements have been popped and printed until the precedence of all the elements in "s" is less or equal to "t"
 */
void processOperator(Stack* s, Token* t, FILE* output){
	if(isEmpty(s)){
		pushElement(s, t);	//if stack is empty, push
	}
	else{
		Token* top = getData(getTop(s));	//top is the token in the top node of "s" (without popping)
		char c = *(char*)getValue(top);		//c is the character of "top"
		if(precedence(top) <= precedence(t)){
			pushElement(s, t);	// if the new element has a greater precedence than the top, push
		}
		else{
			top = getData(popElement(s));	//the top of stack "s" is popped and top is the token in such node
			c = *(char*)getValue(top);
			while(!isEmpty(s) && precedence(top) > precedence(t)){	//pop and print until the precedence is the same
				fprintf(output, "%c ", c);
				top = getData(popElement(s));	//pop next element
				c = *(char*)getValue(top);
			}
			fprintf(output, "%c ", c);
			pushElement(s, t);		//precedence of the top element is equal to the precedence of "t". Therefore "t" is pushed on the stack "s"
		}
	}
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

	//OPENING INPUT AND OUTPUT FILES
	for(i; i < argc; i++){
		if(strcmp(argv[i], "-i")==0){	//if input file is defined
			in_file = fopen(argv[++i],"r");
			if(in_file == NULL){	//if there was an error opening "in_file"
				fprintf(stderr, "Can't open input file %s\nUsing standard input instead...\n", argv[i]);
			}
		}
		else if(strcmp(argv[i], "-o")==0){ //if output file is defined
			out_file = fopen(argv[++i],"w");
			if(in_file == NULL){	//if there was an error opening "out_file"
				fprintf(stderr, "Can't write on file %s\nUsing standard output instead...\n", argv[i]);
			}
		}
	}
	if(in_file == NULL) in_file = stdin; //if input file wasn't defined or there were errors, use standard input
	if(out_file == NULL) out_file = stdout; //if output file wasn't defined or there were errors, use standard output

	Token* t;
	Stack* s = newStack();	//allocate space for the top of the stack. This stack will be formed with Nodes pointing to Tokens.
	t = readToken(in_file);		//read first token
	char top;
	while(!isEOF(t)){	//while the end of file hasn't been read yet
		if(t != NULL){	//if the line was valid
			int type = getID(t);	//type is the ID of token "t" as listed in token.h
			switch(type){
				case INTEGER_ID:
					fprintf(out_file, "%d ", *(int*)getValue(t));	//print integer
					break;
				case DOUBLE_ID:
					fprintf(out_file, "%lf ", *(double*)getValue(t));	//print double
					break;
				case OPERATOR_ID:
					processOperator(s, t, out_file);
					break;
				case RIGHTP_ID:
					top = *(char*)getValue(getData(popElement(s)));
					/*
					 * top is the character in the token of the top node of stack "s":
					 *	the top of the stack "s" is popped (type Node). getData obtains the node's data (type Token).
					 *	getValue obtains the Token's value (type void* casted into char*). The unary '*' returns the value inside the char* (type char).
					 *	That value is assigned to top
					 */
					while(top != '('){		//pop and print until a left parenthesis is found
						fprintf(out_file, "%c ", top);
						if(!isEmpty(s)){
							top = *(char*)getValue(getData(popElement(s)));
						}
						else{	//if a left parenthesis has not been found, the input is invalid and the program is terminated and the memory is freed
							fprintf(stderr, "Error: Invalid input\n");
							fclose(in_file);
							fclose(out_file);
							free(t);
							destroyElements(s);
							free(s);
							exit(1); //abort if the input is invalid
						}
					}	// the left parenthesis is never printed
					break;
				case LEFTP_ID:
					pushElement(s, t);	//always push left parenthesis
					break;
				case UNARY_ID:
					fprintf(out_file, "0 ");	//transform expressions +x or -x into 0+x and 0-x respectively
					processOperator(s, t, out_file);
					break;
			}
		}
		t = readToken(in_file); //read next token
	}
	//once the input file has been read, the operators left in the stack have to be popped and printed
	while(!isEmpty(s)){
		top = *(char*)getValue(getData(popElement(s)));
		fprintf(out_file, "%c ", top);
	}
	//Terminate program successfully and free allocated memory
	fclose(in_file);
	fclose(out_file);
	free(t);
	destroyElements(s);
	free(s);
	return 0;
}
