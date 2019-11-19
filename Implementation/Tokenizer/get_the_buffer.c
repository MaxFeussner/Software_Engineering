#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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
buffer[counter+1] = '\0'; // ends the string
fprintf(stderr,"%s\n", buffer );
return buffer;
}
