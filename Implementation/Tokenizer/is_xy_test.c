//AUTHOR: Maximilian Feußner
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <ctap.h>


TESTS{
//this function takes in a char and returns 0 if the char isnt a dot or 1 if it is a dot
int isdot(char test_char)
	{
    int c = 0;
		if (test_char == '.')
		{
			c++;
		}
		return c;
	}
/*this function takes in a char if the char is a plus and minus (this function
 is important for checking if a char is a unary or operator) the function returns 1 otherwise 0. */
  int ispom(char test_char)
  	{
      int c = 0;
  		if (test_char == '+' || test_char == '-' )
  		{
  			c++;
  		}
  		return c;
  	}
		/* this function takes in a char if the char is an operator (defined in the design)
		it returns 1. Otherwise, the function checks if the char is a left or right
		parenthesis and returns 2 (for left parenthesis) or 3 (for right parenthesis).
		If the char isnt a operator or a parenthesis it returns 0.
		*/
   int isop(char test_char)
  	{
      int c = 0;
  		if (test_char == '+' || test_char == '-' || test_char == '*' || test_char == '/' || test_char == '%')
  		{
  			c = 1;
  		}
		else if(test_char == '('){
			c = 2;
		}
		else if(test_char == ')'){
			c = 3;
		}
  		return c;
  	}

char dot = '.';
char plus = '+';
char number = '9';
char double_dot = ':';
char minus = '-';
char left_parenthesis = '(';
char right_parenthesis = ')';
char times = '*';
char division = '/';
char modulo = '%';


ok (isdot(dot), "the character dot is a dot");
ok (isdot(plus) == 0,"the character plus is not a dot");
ok (isdot(number) == 0,"the character number is not a dot");
ok (isdot(double_dot) == 0,"the character double_dot is not a dot");
ok (ispom(double_dot) == 0,"A double_dot is not an unary");
ok (ispom(number) == 0,"A number is not an unary");
ok (ispom(dot) == 0,"A dot is not an unary");
ok (ispom(plus),"The plus sign can be an unary");
ok (ispom(minus),"The minus sign can be an unary");
ok (isop(left_parenthesis)==2 ,"The left parenthesis is '('");
ok (isop(right_parenthesis)==3 ,"The left parenthesis is ')'");
ok (isop(times), "Times is an operator");
ok (isop(division), "The division sign is an operator");
ok (isop(modulo), "The modulo sign is an operator"); 
ok (isop(dot) == 0,"A dot is not an operator");
ok (isop(number) == 0,"A number is not an operator");

}
