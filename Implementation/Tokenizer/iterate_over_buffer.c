#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "is_xy.h"


void iterate_over_buffer(char* buffer1, FILE * out_file)
{
int buff_length = strlen(buffer1); // gets the length of ther buffer
int buffer_counter = 0;
char buffer[1000];
printf("%i\n", buff_length );
for (int x = 0; x<buff_length; x++) //checks for wrong input and removes it.
{
  if (isop(buffer1[x]) || isdigit(buffer1[x]) || isdot(buffer1[x]))
  {
    buffer[buffer_counter] = buffer1[x];
    buffer_counter++;
  }
  else
  {
    printf("The Input at the position %i is not a valid input and will be ignored.\n", x+1);
  }
}
buffer[buffer_counter]='\0';
printf("%s\n", buffer );
int buff_length1 = strlen(buffer);
for (int i = 0; i<buff_length1; i++) // iterates through the buffer and prints the tokens in a new file.
{
  if (isop(buffer[i])) // test if char is number or punctuation
  {
    if (isop(buffer[i-1]) && ispom(buffer[i])) // test if char is operator or unary (if the char before is a Operator or an '(' it is a Unary)
    {
      fprintf(out_file, "Un:%c\n", buffer[i]);
    }
    else
    {
      fprintf(out_file, "Op:%c\n", buffer[i]);
    }

  }
  else if (isdigit(buffer[i]))
  {
    int counter = 0;
    int counter1 = i;
    int counter2 = i;
    int counter3 = 0;
    while (isdigit(buffer[counter1]) || isdot(buffer[counter1])) 
    {
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
      fprintf(out_file, "In:%s\n", print_buffer );
    }
    else
    {
      fprintf(out_file, "Fp:%s\n", print_buffer );
    }
    i = counter1-1;
  }
}
}
