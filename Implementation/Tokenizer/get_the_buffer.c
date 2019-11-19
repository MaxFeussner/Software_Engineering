#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* The input of the function is a file and the output an array of chars.*/

char * get_buffer(FILE * in_file, char* buffer)
{
int counter = 0;
char c = fgetc(in_file);
while(!feof(in_file)) // fills every single char from the inputfile into a buffer.
{
  buffer[counter] = c;
  c = fgetc(in_file);
  counter ++;
}
buffer[counter+1] = '\0'; // ends the string
return buffer;
}
