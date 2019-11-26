#include "common.h"

void openIOFiles(int argc, char** argv, FILE ** in_file, FILE ** out_file){
	int i = 1;
	*in_file = NULL;
	*out_file = NULL;

	//OPENING INPUT AND OUTPUT FILES
	for(i = 1; i < argc; i++){
		if(strcmp(argv[i], "-i")==0){	//if input file is defined
			*in_file = fopen(argv[++i],"r");
			if(*in_file == NULL){	//if there was an error opening "in_file"
				fprintf(stderr, "Can't open input file %s\nUsing standard input instead...\n", argv[i]);
			}
		}
		else if(strcmp(argv[i], "-o")==0){ //if output file is defined
			*out_file = fopen(argv[++i],"w");
			if(*in_file == NULL){	//if there was an error opening "out_file"
				fprintf(stderr, "Can't write on file %s\nUsing standard output instead...\n", argv[i]);
			}
		}
	}
	if(*in_file == NULL) *in_file = stdin; //if input file wasn't defined or there were errors, use standard input
	if(*out_file == NULL) *out_file = stdout; //if output file wasn't defined or there were errors, use standard output
}

/*
 * Pre: input is a pointer to a text file
 * Post: read a line of "input" without storing it
 */
void ignoreLine(FILE* input){
	char* ignore=NULL;
	size_t n = 0;
	getline(&ignore, &n, input);
	free(ignore);
}

/*
 * Pre: ---
 * Post: returned true if and only if op was a '+', '-', '*', '/' or '%'
 */
bool validOperator(char op){
	return (op=='+' || op=='-' || op=='*' || op=='/' || op=='%');
}

/*
 * Pre: stream is a pointer to a valid text file
 * Post: if *line_ptr was set to NULL and *n to 0, the function allocated and changed the integer depending on the amount of data from stream
 *	 otherwise, *line_ptr stored *n characters from stream until a character delim was found, which was read but NOT stored in *line_ptr
 */
ssize_t getUntilDelim(char **lineptr, size_t *n, int delim, FILE *stream){
	ssize_t temp = getdelim(lineptr, n, delim, stream) -1;
	if(temp >= 0) (*lineptr)[temp] = '\0'; //get rid of the delimiter
	return temp;
}
