//AUTHOR: Andrés Otero García
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "token.h"

/*
 * Pre:
 * Post: if "new" is a valid type ID (as defined in token.h), returned a token which allocates
 * 		 the memory size of 1 element of the specified type by "new"
 * 		 otherwise, returns a null pointer
 */
Token* createToken(short int new){
	Token* t = malloc (sizeof(Token));
	if(new>=0 && new<MAX_TOKEN_ID){
		t->id = new;
		switch(new){
			case INTEGER_ID:
				t->value = (int*) malloc (sizeof(int));
				break;
			
			case DOUBLE_ID:
				t->value = (double*) malloc (sizeof(double));
				break;

			case LEFTP_ID:
				t->value = (char*) malloc (sizeof(char));
				break;

			case RIGHTP_ID:
				t->value = (char*) malloc (sizeof(char));
				break;
			
			case UNARY_ID:
				t->value = (char*) malloc (sizeof(char));
				break;

			case OPERATOR_ID:
				t->value = (char*) malloc (sizeof(char));
				break;
		}
	}
	else exit(1);
	return t;
}

/*
 * Pre: ---
 * Post: t.value = new
 */
void setValue(Token* t, void* new, size_t size){
	memcpy(t->value, new, size);
}

/*
 * Pre: ---
 * Post: returned a pointer to a token with id=value=-1
 */
Token* eof_token(){
	Token* t = malloc (sizeof(Token));
	short int i = -1;
	t->id = i;
	t->value = &i;
	return t;
}

/*
 * Pre: "t1" and "t2" are not null pointers
 * Post: returns true if and only if the id's and values of "t1" and "t2" are the same
 */
bool isEqual(Token* t1, Token* t2){
	if(t1->id==t2->id){
		switch(t1->id){
			case INTEGER_ID:
				return *(int*)t1->value == *(int*)t2->value;
			case DOUBLE_ID:
				return *(double*)t1->value == *(double*)t2->value;
			case LEFTP_ID:
				return *(char*)t1->value == *(char*)t2->value;
			case RIGHTP_ID:
				return *(char*)t1->value == *(char*)t2->value;
			case OPERATOR_ID:
				return *(char*)t1->value == *(char*)t2->value;
			case UNARY_ID:
				return *(char*)t1->value == *(char*)t2->value;
			default:	//Parenthesis and EOF tokens are always equal
				return true;
		}
	}
	else return false;
}

/*
 * Pre: ---
 * Post: returns true if and only if the t = value = -1
 */
bool isEOF(Token* t){
	if(t==NULL) return false;
	else return (t->id == -1 && *(short int*)t->value == -1);
}
/*
 * Pre: "t" is not a null pointer
 * Post: returned t->id
 */
int getID(Token* t){
	return t->id;
}

/*
 * Pre: "t" is a valid pointer to a Token
 * Post: returned t->value
 */
void* getValue(Token* t){
	return t->value;
}
