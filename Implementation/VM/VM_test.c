#include <ctap.h>
#include "VM.h"
#include <time.h>
#include <math.h>

#define N_TESTS 6
#define DECIMALS 100000.0
#define N_OPERATORS 5
#define INSTR 7

TESTS{
	void testTransformToDouble(Token* t[]){
		double temp_d;
		int example_int = 25;
		double example_double = 3.1416;
		t[0] = createToken(INTEGER_ID);
		t[1] = createToken(DOUBLE_ID);
		setValue(t[0], &example_int, sizeof(int));
		transformToDouble(t[0], &temp_d);
		ok(temp_d == example_int, "Integer token conversion to double was correct");
		setValue(t[1], &example_double, sizeof(double));
		transformToDouble(t[1], &temp_d);
		ok(temp_d == example_double, "Double token conversion to double was correct");
	}

	void testOperateTokens(Token* t[]){
		ok(operateTokens(t[0], '?', t[1]) == NULL, "operateTokens returns NULL if operator is invalid");
		ok(operateTokens(NULL, '+', t[1]) == NULL, "operateTokens returns NULL if first token is NULL");
		ok(operateTokens(t[0], '+', NULL) == NULL, "operateTokens returns NULL if second token is NULL");
		double zero = 0.0;
		t[2] = createToken(DOUBLE_ID);
		setValue(t[2], &zero, sizeof(double)); 
		srand(time(NULL));
		double random[N_TESTS-3];
		for(int i = 3; i < N_TESTS; i++){
			random[i-3] = rand() / DECIMALS;
			t[i] = createToken(DOUBLE_ID);
			setValue(t[i], &random[i-3], sizeof(double));
		}

		ok(operateTokens(t[0], '/', t[2]) == NULL, "operateTokens returns NULL if operation was a division and divisor was 0");

		char operators[N_OPERATORS] = {'+', '-', '*', '/', '%'};
		double expected[N_OPERATORS] = {random[0]+random[1], random[0]-random[1], random[0]*random[1], random[0]/random[1], fmod(random[0],random[1])};

		for(int i = 0; i < N_OPERATORS; i++){
			Token* temp_t = operateTokens(t[3], operators[i], t[4]);
			double temp_d = *(double*)getValue(temp_t);
			
			
			ok(temp_d == expected[i], "operateTokens performed correctly (%lf %c %lf = %lf) (expected %lf)", random[0], operators[i], random[1], temp_d, expected[i]);
		}
	}

	void testInstructionIndex(){
		//constant vector of instructions available
		char* INSTRUCTION_STRING[INSTR] = {"LDI", "LDF", "ADD", "SUB", "MUL", "DIV", "MOD"};

		for(int i = 0; i < INSTR; i++){
			ok(instruction_index(INSTRUCTION_STRING[i]) == i, "instruction_index returned correct index (%s -> %d)", INSTRUCTION_STRING[i], i);
		}
	}

	void testVM(){
		FILE * in_file = fopen("testInput.txt", "r");
		FILE * out_file = fopen("test_temp_out.txt", "w");
		Stack* s = newStack();

		VM(in_file, out_file, s);
		
		ok(isEmpty(s), "Stack is empty");

		fclose(in_file);
		fclose(out_file);

		in_file = fopen("test_temp_out.txt", "r");
		char* buffer = NULL;
		size_t size = 0;
		getline(&buffer, &size, in_file);

		is(buffer, "0.166667\n", "VM read through input test file and returned correct value");
		fclose(in_file);
		remove("test_temp_out.txt");
		
	}

	Token* t[N_TESTS];
	testTransformToDouble(t);

	testOperateTokens(t);

	testInstructionIndex();

	testVM();

	
}
