#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <ctap.h>

TESTS {
char * get_buffer(FILE * in_file, char* buffer)
{
int counter = 0;
char c = fgetc(in_file);
while(!feof(in_file)) // fills everything in the inputfile into a buffer. 
{
  buffer[counter] = c;
  c = fgetc(in_file);
  counter ++;
}
buffer[counter] = '\0'; // ends the string
printf("%s\n", buffer );
return buffer;
}
char buffer[50];
FILE * test_file;
test_file = fopen("test_input.txt","r");
char test_buffer[50]="(-120.a34s)/4j05%aa4+5A6a*(-4+3)\n"; // just put in the test_buffer the string from the inputfile with "\n" at the end.
is(get_buffer(test_file,buffer),test_buffer,"The input was correctly put into a buffer");


}
