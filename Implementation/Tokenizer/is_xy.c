#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>



int isdot(char test_char)//this function tests if a char is a dot or not
	{
    int c = 0;
		if (test_char == '.')
		{
			c++;
		}
		return c;
	}

  int ispom(char test_char)//this function tests if a char is a plus, minus or a parenthesis (this function is important for checking if a char is a unary or operator)
  	{
      int c = 0;
  		if (test_char == '+' || test_char == '-' )
  		{
  			c++;
  		}
  		return c;
  	}

   int isop(char test_char)// this function test if a char is an operator (defined in the design).
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
