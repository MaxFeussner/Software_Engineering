#include <stdbool.h>
#define INTEGER_ID 0
#define DOUBLE_ID 1
#define LEFTP_ID 2
#define RIGHTP_ID 3
#define UNARY_ID 4
#define OPERATOR_ID 5
#define MAX_TOKEN_ID 6
#define Token struct __token

#ifndef TOKEN_INFIX_POSTFIX
#define TOKEN_INFIX_POSTFIX

struct __token{
	short int id;
	void* value;
};

Token* createToken(short int new);
void setValue(Token* t, void* value, size_t size);
Token* eof_token();
bool isEOF(Token* t);
int getID(Token* t);
void* getValue(Token* t);



#endif
