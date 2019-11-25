#include <ctap.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "infix-to-postfix.h"

#define N_OPERATORS 5
#define N_UNARY 2

#define N TYPES+N_OPERATORS+N_UNARY-2

#define RAND_OPERATOR rand() % N_OPERATORS

TESTS{

	void testPrecedence(Token* t[], char operators[]){
		int precedence_vector[N_OPERATORS + N_UNARY];

		for(int i = 0; i < N_OPERATORS + N_UNARY; i++){
			setValue(t[i], &operators[i%N_OPERATORS], sizeof(char));
			precedence_vector[i] = precedence(t[i]);
		}

		//testing that p(+) == p(-) < p(unary+) == p(unary-) < p(*) == p(/) == p(%)
		ok(precedence_vector[5] == precedence_vector[6], "precedence(unary+) == precedence(unary-)");
		ok(precedence_vector[0] == precedence_vector[1], "precedence(+) == precedence(-)");
		ok(precedence_vector[1] < precedence_vector[5], "precedence(-) < precedence(unary+)");
		ok(precedence_vector[6] < precedence_vector[2], "precedence(unary-) < precedence(*)");
		ok(precedence_vector[2] == precedence_vector[3], "precedence(*) < precedence(/)");
		ok(precedence_vector[3] == precedence_vector[4], "precedence(/) < precedence(%)");
	}



	void testProcessValue(Token* test_token[], FILE* test_file, int random_int, double random_d, char operators[]){
		for(int i = 0; i < N; i++){
			int test_int;
			double test_double;
			char test_char;
			char* line_ptr = NULL;
			size_t temp = 0;
			getUntilDelim(&line_ptr, &temp, DELIMITER, test_file); //ignore specifiers, will be later tested

			if(test_token[i] != NULL){
				test_token[i] = NULL;
			}

			/* for each case:
			 * 1: Create token in vector
			 * 2: call processValue
			 * 3: test that the token stored the same value as test_int
			 * 4: test that the read value is the correct one
			*/
			if(i == 0){	//integer case
				test_token[i] = createToken(INTEGER_ID);
				processValue(test_file, " %d\n", test_token[i], &test_int, sizeof(int));
				int storedValue = *(int*) (test_token[i]->value);
				ok(storedValue == test_int, "The value in argument \"value\" = %d is equal to the value stored in the token in argument \"t\" %d (%d/%d)", test_int, storedValue, i, N-1);
				ok(storedValue == random_int, "The integer value %d has been read correctly from the temporary file %d (%d/%d)", storedValue, random_int, i, N-1);
			}
			else if(i == 1){	//double case
				test_token[i] = createToken(DOUBLE_ID);
				processValue(test_file, " %lf\n", test_token[i], &test_double, sizeof(double));
				double storedValue = *(double*) test_token[i]->value;
				ok(storedValue == test_double, "The value in argument \"value\" = %lf is equal to the value stored in the token in argument \"t\" %lf (%d/%d)", test_double, storedValue, i, N-1);
				ok(storedValue == random_d, "The floating point value has been read correctly from the temporary file (%d/%d)", i, N-1);
			
			}
			else{	//operators cases
				char expectedChar;
				if(i == 2){
					test_token[i] = createToken(LEFTP_ID);
					expectedChar = '(';
				}
				else if(i == 3){
					test_token[i] = createToken(RIGHTP_ID);
					expectedChar = ')';
				}
				else if(i < N - 2){
					test_token[i] = createToken(OPERATOR_ID);
					expectedChar = operators[i - 4];
				}
				else{
					test_token[i] = createToken(UNARY_ID);
					expectedChar = operators[(i-4)%N_OPERATORS];
				}
				processValue(test_file, " %c\n", test_token[i], &test_char, sizeof(char));
				char storedValue = *(char*) test_token[i]->value;
				ok(storedValue == test_char, "The value in argument \"value\" = %c is equal to the value stored in the token in argument \"t\" %c (%d/%d)", test_char, storedValue, i, N-1);
				ok(storedValue == expectedChar, "The floating point value has been read correctly from the temporary file (%d/%d)", i, N-1);
			}
		}
	}

	void testReadToken(Token* test_token[], FILE* test_file){
		Token* read_token[N+2];
		//testing for the previous 11 cases plus invalid input and the EOF
		for(int i = 0; i < N + 2; i++){
			read_token[i] = readToken(test_file);
			if(i < N){
				ok(isEqual(read_token[i], test_token[i]), "readToken saved expected values (%d/%d)", i, N+1);
			}
		}
		ok(read_token[N] == NULL, "readToken ignored an invalid input");
		ok(isEOF(read_token[N+1]), "readToken returns EOF at the end of the file");
	}


	void testProcessOperator(Token* test_token[]){
		FILE * temp_output = fopen("temp_output.txt", "w");
		Token* top_token;
		ok(temp_output != NULL, "Permissions allowed creation of temp output file for processOperator");
		Stack* s = newStack();
		processOperator(s, test_token[4], temp_output); //processing binary '+'
		top_token = (Token*) getData(getTop(s));
		ok(isEqual(top_token, test_token[4]), "processOperator pushes token on stack if stack was empty");
		processOperator(s, test_token[6], temp_output); //processing '*'
		top_token = (Token*) getData(getTop(s));
		ok(isEqual(top_token, test_token[6]), "processOperator pushes token if the top has a smaller precedence");
		processOperator(s, test_token[9], temp_output); //processing unary '+'
		fclose(temp_output);
		FILE * temp_input = fopen("temp_output.txt", "r");
		char* expectedOutput = "* ";
		for(int i = 0; i < strlen(expectedOutput); i++){
			ok(fgetc(temp_input) == expectedOutput[i], "Output file matches expected output (%d/%d)", i, strlen(expectedOutput));
		}
		top_token = (Token*) getData(getTop(s));
		ok(isEqual(top_token, test_token[9]), "processOperator pushes token until precedence is the same or smaller");
		fclose(temp_output);
		remove("temp_output.txt");
	}

	void testOverallI2P(){
		char* temp_argv[5] = {"i2p_test.t", "-i", "testFile2.txt", "-o", "temp_output2.txt"};

		FILE * in_file = NULL;
		FILE * out_file = NULL;
		openIOFiles(5, temp_argv, &in_file, &out_file);
		Stack* s = newStack();

		infix_to_postfix(in_file, out_file, s);
		ok(isEmpty(s), "STack s is empty after execution");

		fclose(in_file);
		fclose(out_file);
		in_file = fopen("temp_output2.txt", "r");

		char* expectedResult = "0 0 2 - - 0 4 0 0 3 + - + - + 0 0 2.500000 3 / - - - ";
		for(int i = 0; i < strlen(expectedResult); i++){
			ok(fgetc(in_file) == expectedResult[i], "Infix to postfix algorithm returns expected result (%d/%d)", i, strlen(expectedResult));
		}
		remove("temp_output2.txt");
	}

	//setup
	FILE* test_file = fopen("testFile.txt", "r");
	ok(test_file != NULL, "testFile.txt has been found.");
	if(test_file == NULL) exit(1);

	char operators[N_OPERATORS] = {'+', '-', '*', '/', '%'};
	Token * t[N_OPERATORS + 2];

	srand(time(NULL));

	int random_int = 836740483;	 // has to be equal to the number in testFile.txt
	double random_d = 114062.804100; // has to be equal to the number in testFile.txt

	//initializing operator and binary tokens in vector t
	for(int i = 0; i < N_OPERATORS; i++){
		t[i] = createToken(OPERATOR_ID);
	}
	t[N_OPERATORS] = createToken(UNARY_ID);
	t[N_OPERATORS + 1] = createToken(UNARY_ID);
	
	//make all the tests for the tokens just created
	testPrecedence(t, operators);


	/*read 11 lines (there are 5 types, and the Unary and Operator types have N_UNARY and N_OPERATORS types respectively
	 * therefore (TYPES - 2)*1 + 1*(N_UNARY) + 1*(N_OPERATORS)
	 * TYPES -2 + N_UNARY + N_OPERATORS
	 */

	Token* test_token[N];

	//make all the tests for the values in the lines of testFile.txt
	testProcessValue(test_token, test_file, random_int, random_d, operators);
	
	//go back to the start of the file
	fseek(test_file, 0, SEEK_SET);

	testReadToken(test_token, test_file);

	testProcessOperator(test_token);

	testOverallI2P();
	
	
//ok(test_token->id == INTEGER_ID, "The test_token possesses expected id = %d (%d/%d)", INTEGER_ID, i, n);
	fclose(test_file);
	
	
}
