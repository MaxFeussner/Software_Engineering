#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int isdot(char test_char)
	{
    int c = 0;
		if (test_char == '.')
		{
			c++;
		}
		return c;
	}

  int ispom(char test_char)
  	{
      int c = 0;
  		if (test_char == '+' || test_char == '-' || test_char == '(')
  		{
  			c++;
  		}
  		return c;
  	}

int main (int argc, char**argv) {
  int r = 1;
  FILE * in_file;
	FILE * out_file;

	//OPENING INPUT AND OUTPUT FILES
	for(r; r < argc; r++){
		if(strcmp(argv[r], "-i")==0){	//if input file is defined
			in_file = fopen(argv[++r],"r");
			if(in_file == NULL){	//if there was an error opening "in_file"
				fprintf(stderr, "Can't open input file %s\nUsing standard input instead...\n", argv[i]);
			}
		}
		else if(strcmp(argv[r], "-o")==0){ //if output file is defined
			out_file = fopen(argv[++r],"w");
			if(in_file == NULL){	//if there was an error opening "out_file"
				fprintf(stderr, "Can't write on file %s\nUsing standard output instead...\n", argv[i]);
			}
		}
	}
	if(in_file == NULL) in_file = stdin; //if input file wasn't defined or there were errors, use standard input
	if(out_file == NULL) out_file = stdout; //if output file wasn't defined or there were errors, use standard output


  int counter = 0;
  char buffer[1000];
  char c = fgetc(in_file);
  while(!feof(fp)) // fills everything in the inputfile into a buffer.
  {
    buffer[counter] = c;
    c = fgetc(fp);
    counter ++;
  }

  buffer[counter+1] = '\0'; // ends the string
  int buff_length = strlen(buffer); // gets the length of ther buffer

  for (int i = 0; i<buff_length-1; i++) // iterates through the buffer and prints the tokens in a new file.
  {
    if (ispunct(buffer[i])) // test if char is number or punctuation
    {
      if (ispunct(buffer[i-1]) && ispom(buffer[i])) // test if char is operator or unary (if the char before is a Operator or an '(' it is a Unary)
      {
        fprintf(p, "Un%c\n", buffer[i]);
      }
      else
      {
        fprintf(p, "Op:%c\n", buffer[i]);
      }

    }
    else if (isdigit(buffer[i])==1)
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
  else
  {
    printf("The input at the position: %i %s\n", i,"Is not a viable character");
  }
  }
  return 0;
    }
