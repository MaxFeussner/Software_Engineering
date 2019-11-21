#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "is_xy.h"
#include "get_the_buffer.h"
#include "iterate_over_buffer.h"
#include <ctap.h>

TESTS{

int tokenizer(){
  FILE * in_file = fopen("test_input_tokenizer","r");
  FILE * out_file = fopen("test_output_tokenizer", "a");
  char* buffer;
  buffer = (char*) malloc(100 * sizeof(char));
  //get_buffer(in_file, buffer);
  //iterate_over_buffer(buffer, out_file);
  //fclose(in_file);
  return 0;
}

char* buffer1;
buffer1 = (char*) malloc(100*sizeof(char));
FILE * out_file1 = fopen("test_output1", "r");
char test_buffer1[]="Un:-\nUn:-\nIn:2\nOp:+\nUn:-\nLp:(\nIn:4\nOp:+\nUn:-\nUn:+\nIn:3\nRp:)\nOp:-\nUn:-\nUn:-\nFp:2.5\nOp:/\nIn:3";
is(get_buffer(out_file1,buffer1),test_buffer1,"The input was correctly split into tokens.");
ok(tokenizer()==0,"HEZ");

}
