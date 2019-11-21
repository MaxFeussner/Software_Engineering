#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "is_xy.h"
#include "get_the_buffer.h"
#include "iterate_over_buffer.h"

int main (int argc, char**argv) {
  int r = 1;
  FILE * in_file = NULL;
	FILE * out_file = NULL;
	char l = ')';
	
	//OPENING INPUT AND OUTPUT FILES
	for(r; r < argc; r++){
		if(strcmp(argv[r], "-i")==0){	//if input file is defined
			in_file = fopen(argv[++r],"r");
			if(in_file == NULL){	//if there was an error opening "in_file"
				fprintf(stderr, "Can't open input file %s\nUsing standard input instead...\n", argv[r]);
			}
		}
		else if(strcmp(argv[r], "-o")==0){ //if output file is defined
			out_file = fopen(argv[++r],"w");
			if(in_file == NULL){	//if there was an error opening "out_file"
				fprintf(stderr, "Can't write on file %s\nUsing standard output instead...\n", argv[r]);
			}
		}
	}
	if(in_file == NULL) in_file = stdin; //if input file wasn't defined or there were errors, use standard input
	if(out_file == NULL) out_file = stdout; //if output file wasn't defined or there were errors, use standard output
	char* buffer;
	buffer = (char*) malloc(100 * sizeof(char));
	iterate_over_buffer(get_buffer(in_file, buffer), out_file);
  return 0;
    }
