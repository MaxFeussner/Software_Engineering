#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int isdot(char test_char)
	{
		if (test_char == '.')
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

  int ispom(char test_char)
  	{
  		if (test_char == '+' || test_char == '-' || test_char == '(')
  		{
  			return 1;
  		}
  		else
  		{
  			return 0;
  		}
  	}

int main (int argc, char**argv) {
  int counter = 0;
  char buffer[1000];
  FILE *fp = fopen("input_number.txt", "r");
  char c = fgetc(fp);
  while(!feof(fp))
  {
  printf("%c\n",c);
  buffer[counter] = c;
  c = fgetc(fp);
  counter ++;
  }
  buffer[counter+1] = '\0';
  int buff_length = strlen(buffer);
  printf("%i\n", buff_length);

  FILE *p = fopen("file.txt", "a");

  for (int i = 0; i<buff_length-1; i++)
  {
    if (ispunct(buffer[i]))
    {
      if (ispunct(buffer[i-1]) && ispom(buffer[i]))
      {
        fprintf(p, "Un%c\n", buffer[i]);
      }
      else
      {
        fprintf(p, "Op:%c\n", buffer[i]);
      }

    }
    if (isdigit(buffer[i])==1)
    {
      int counter = 0;
      int counter1 = i;
      int counter2 = i;
      int counter3 = 0;
      while (isdigit(buffer[counter1]) || isdot(buffer[counter1])) {
        counter++;
        counter1++;
      }
      int array_length = 100;
      char print_buffer[array_length];
      for (counter2; counter2< (i+counter); counter2++)
      {
        print_buffer[counter3] = buffer[counter2];
        counter3++;
      }
      print_buffer[counter3] = '\0';
      int int_checker = 0;
      for(int q = 0; q<strlen(print_buffer);q++)
      {
        if (isdot(print_buffer[q]))
        {
          int_checker++;
        }
      }
      if (int_checker == 0)
      {
        fprintf(p, "In:%s\n", print_buffer );
      }
      else
      {
        fprintf(p, "Fp:%s\n", print_buffer );
      }
      i = counter1-1;
  }
  }
  return 0;
    }
