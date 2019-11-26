//AUTHOR: Juan Vercher
#include "codegenerator.h"

//calling the other function it writes in the output the instruccions
int main(int argc, char** argv)
{
	FILE * in_file = NULL;
	FILE * out_file = NULL;
 	char * token = NULL;
	openIOFiles(argc, argv, &in_file, &out_file);
	size_t bufsize = 0;

        while (feof(in_file) == 0)
	{
		getUntilDelim(&token, &bufsize, DELIMITER, in_file); // read first part
		char *code;

		if(token != NULL && strlen(token)>0){
			code  = codeGenerator(token);
			fprintf(out_file,"%s\n", code);
			free(code);
		}
		bufsize = 0;
		free(token);

	}
        fclose(in_file);
	fclose(out_file);
	free(token);
	return 0;
}
