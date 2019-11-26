//AUTHOR: Andrés Otero García
#include "VM.h"


int main(int argc, char** argv){
	FILE * in_file = NULL;
	FILE * out_file = NULL;
	openIOFiles(argc, argv, &in_file, &out_file);
	Stack * s = newStack();		//stack where all numbers will be pushed

	VM(in_file, out_file, s);

	//free allocated memory and close files
	fclose(in_file);
	fclose(out_file);
	destroyElements(s);
	free(s);
}
