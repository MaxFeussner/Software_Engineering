//AUTHOR: Maximilian Feußner
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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
