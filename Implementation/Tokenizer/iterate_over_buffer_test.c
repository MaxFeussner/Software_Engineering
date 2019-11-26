#include <stdlib.h>
#include <ctype.h>
#include "is_xy.h"
#include <ctap.h>
#include "get_the_buffer.h"

TESTS{
int iterate_over_buffer(char* buffer1, FILE * out_file)
{
int buff_length = strlen(buffer1);
int buffer_counter = 0;
char buffer[1000];
for (int x = 0; x<buff_length; x++) //checks for wrong input and removes it.
{
  if (isop(buffer1[x]) || isdigit(buffer1[x]) || isdot(buffer1[x]))
  {
    buffer[buffer_counter] = buffer1[x];
    buffer_counter++;
  }
  else
  {
    //fprintf(stderr,"The Input at the position %i is not a valid input and will be ignored.\n", x+1);
  }
}
buffer[buffer_counter]='\0';
int buff_length1 = strlen(buffer);
for (int i = 0; i<buff_length1; i++) // iterates through the buffer and prints the tokens in a new file.
{
  if (isop(buffer[i])!=0) // test if char is operator or unary.
  {
    if(ispom(buffer[i])){
	if(i > 0){
		if(isop(buffer[i-1])==1){
			fprintf(out_file, "Un:%c\n", buffer[i]);
		}
		else
		{
	      		fprintf(out_file, "Op:%c\n", buffer[i]);
	    	}
	}
	else{
		fprintf(out_file, "Un:%c\n", buffer[i]);
	}
    }
    else if(isop(buffer[i])==1)
    {
      fprintf(out_file, "Op:%c\n", buffer[i]);
    }
    else if(isop(buffer[i])==2)
    {
      fprintf(out_file, "Lp:%c\n", buffer[i]);
    }
    else if(isop(buffer[i])==3)
    {
      fprintf(out_file, "Rp:%c\n", buffer[i]);
    }
  }
  else if (isdigit(buffer[i])) // tests if char is a digit.
  {
    int counter = 0;
    int counter1 = i;
    int counter2 = i;
    int counter3 = 0;
    /* This filters out all digit and dots that are not interrupted by an operator
    and puts them in a new array of chars (buffer) */

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
    for(int q = 0; q<strlen(print_buffer);q++) // checks if number is Int or floating point.
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
    i = counter1-1; // This makes sure that no char will be written two times as a token.
  }
}
int y=0;
return y;
}


FILE* test_output = fopen("test_output_iterate_over_buffer.txt","w");

char* buffer;
buffer = (char*) malloc(100*sizeof(char));
char test_input_buffer[]="-(-120.a34s)/4j05%aa4+5A6a*(-4+30+0)\n";
char test_result_buffer[]="Un:-\nLp:(\nOp:-\nFp:120.34\nRp:)\nOp:/\nIn:405\nOp:%\nIn:4\nOp:+\nIn:56\nOp:*\nLp:(\nOp:-\nIn:4\nOp:+\nIn:30\nOp:+\nIn:0\nRp:)\n";


ok(iterate_over_buffer(test_input_buffer, test_output)==0,"Iterate_over_buffer was succesfully run.");
fclose(test_output);
FILE* test_result = fopen("test_output_iterate_over_buffer.txt","r");
is(get_buffer(test_result,buffer),test_result_buffer,"The input was correctly split into tokens.");

}
