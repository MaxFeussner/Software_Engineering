//AUTHOR: Maximilian Feußner
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "is_xy.h"
#include "get_the_buffer.h"
#include "iterate_over_buffer.h"
#include "../common/common.h"


//This function gets a input file and returns a outputfile. The tokenizer reads in the string that needs to be calculated and retunrs a file with operators and numbers with their specifiers and values.
int main (int argc, char**argv) {
	int r = 1;
	FILE * in_file = NULL;
	FILE * out_file = NULL;

	//OPENING INPUT AND OUTPUT FILES
	openIOFiles(argc, argv, &in_file, &out_file);
	
	char* buffer;
	buffer = (char*) malloc(1000 * sizeof(char));
	iterate_over_buffer(get_buffer(in_file, buffer), out_file);
	return 0;
    }
