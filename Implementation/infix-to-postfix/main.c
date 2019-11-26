//AUTHOR: Andrés Otero García
#include "../common/common.h"
#include "../stack/stack.h"
#include "../token/token.h"
#include "infix-to-postfix.h"

int main(int argc, char** argv){

	FILE* in_file = NULL;
	FILE* out_file = NULL;
	openIOFiles(argc, argv, &in_file, &out_file);
	Stack* s = newStack(); //allocate space for the top of the stack. This stack will be formed with Nodes pointing to Tokens.

	infix_to_postfix(in_file, out_file, s);

	fclose(in_file);
	fclose(out_file);
	destroyElements(s);
	free(s);

	return 0;
}
