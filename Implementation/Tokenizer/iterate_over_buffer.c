#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "is_xy.h"


int iterate_over_buffer(char* buffer1, FILE * out_file)
{
	int buff_length = strlen(buffer1);
	int buffer_counter = 0;
	char buffer[1000];
	int canBeDot = 1;
	for (int x = 0; x<buff_length; x++) //checks for wrong input and removes it.
	{
		if (isop(buffer1[x]) || isdigit(buffer1[x]) || (isdot(buffer1[x]) && canBeDot == 1))
		{
			if(isop(buffer1[x])){
				canBeDot = 1;
			}
			else if(isdot(buffer1[x])){
				canBeDot = 0;
			}
			buffer[buffer_counter] = buffer1[x];
			buffer_counter++;
		}
		else
		{
			fprintf(stderr,"Error: The input %c at position %d is not a valid and will be ignored.\n", buffer1[x], x+1);
		}
	}
	buffer[buffer_counter]='\0';
	int buff_length1 = strlen(buffer);
	for (int i = 0; i<buff_length1; i++){ // iterates through the buffer and prints the tokens in a new file.
		if (isop(buffer[i])!=0){ // test if char is operator or unary.
			if(ispom(buffer[i])){
				if(i > 0){
					if(isop(buffer[i-1])==1){
						fprintf(out_file, "Un:%c\n", buffer[i]);
					}
					else{
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
		else if(int_checker == 1)
		{
			fprintf(out_file, "Fp:%s\n", print_buffer );
		}
		else{
			fprintf(stderr, "Error: Floating point number with more than one dot\n");
			exit(1);
		}
			i = counter1-1; // This makes sure that no char will be written two times as a token.
		}
	}
	int y=0;
	return y;
}
