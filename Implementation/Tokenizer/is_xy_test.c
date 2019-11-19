#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <ctap.h>


TESTS{
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

   int isop(char test_char)
  	{
      int c = 0;
  		if (test_char == '+' || test_char == '-' || test_char == '*' || test_char == '/' || test_char == '%' || test_char == '(' ||test_char == ')')
  		{
  			c++;
  		}
  		return c;
  	}

char dot = '.';
char plus = '+';
char number = '9';
char double_dot = ':';
char minus = '-';
char left_parenthesis = '(';

ok (isdot(dot), "the character dot is a dot");
ok (isdot(plus) == 0,"the character plus is not a dot");
ok (isdot(number) == 0,"the character number is not a dot");
ok (isdot(double_dot) == 0,"the character double_dot is not a dot");
ok (ispom(double_dot) == 0,"A double_dot is not an unary");
ok (ispom(number) == 0,"A number is not an unary");
ok (ispom(dot) == 0,"A dot is not an unary");
ok (ispom(plus),"The plus sign can be an unary");
ok (ispom(minus),"The minus sign can be an unary");
ok (ispom(left_parenthesis)==0,"The left parenthesis is not an unary");


}
