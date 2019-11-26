//AUTHOR: Andrés Otero García
#include <ctap.h>
#include "common.h"
#include <stdio.h>

#define N 8
#define N_OPERATORS 5

TESTS{
	void testOpenIOFiles(){
		char* temp_argv[5] = {"common_test.t", "-i", "testInput.txt", "-o", "testOutput.txt"};
		FILE * in_file;
		FILE * out_file;
		openIOFiles(5, temp_argv, &in_file, &out_file);
		
		char* temp_buffer = NULL;
		size_t temp_int = 0;
		getline(&temp_buffer, &temp_int, in_file);
		is(temp_buffer, "Data has been read correctly.\n", "openIOFiles has opened the file correctly when provided an argument");

		fprintf(out_file, "%s", temp_buffer);
		fclose(in_file);
		fclose(out_file);
		FILE * readOutput = fopen("testOutput.txt", "r");

		free(temp_buffer);
		temp_buffer = NULL;
		temp_int = 0;
		getline(&temp_buffer, &temp_int, readOutput);
		is(temp_buffer, "Data has been read correctly.\n", "openIOFiles has opened the output file correctly when provided an argument");
		fclose(readOutput);

		openIOFiles(1, &temp_argv[0], &in_file, &out_file);
		ok(in_file != NULL, "in_file is initialized to stdin when no argument is given");
		ok(out_file != NULL, "out_file is initialized to stdout when no argument is given");
	}

	void testGetUntilDelim(FILE * in_file){
		char* line_ptr = NULL;
		size_t temp = 0;
		getUntilDelim(&line_ptr, &temp, '.', in_file);
		isnt(line_ptr, "Data has been read correctly.", "The delimiter is not stored in the data when reading a whole line");
		is(line_ptr, "Data has been read correctly", "String has been read correctly when reading an undefined amount of characters");
		free(line_ptr); line_ptr = NULL;
		temp = 3;
		getUntilDelim(&line_ptr, &temp, '!', in_file);
		is(line_ptr, "\nNext line is going to be ignored", "Read whole next line");
		ok(temp >= strlen(line_ptr), "Length is updated (%d >= %d)", temp, strlen(line_ptr));
		free(line_ptr); line_ptr = NULL;
		temp = 0;
		getUntilDelim(&line_ptr, &temp, '!', in_file);
		is(line_ptr, " Oh no", "Correct consecutive readings");
		getline(&line_ptr, &temp, in_file); //align to next line for next tests
	}

	void testIgnoreLine(FILE * in_file){
		ignoreLine(in_file);
		char* line_ptr = NULL;
		size_t temp = 0;
		getline(&line_ptr, &temp, in_file);
		is(line_ptr, "Where did the third line go?\n", "Line has been ignored correctly");
	}

	void testValidOperator(){
		char test_vector[N] = {'+', '-', '*', '/', '%', 'a', '1', '('};
		for(int i = 0; i < N_OPERATORS; i++){
			ok(validOperator(test_vector[i]), "Returned true for operator \'%c\'", test_vector[i]);
		}
		for(int i = N_OPERATORS; i < N; i++){
			ok(!validOperator(test_vector[i]), "Returned false for \'%c\'", test_vector[i]);
		}
	}

	testOpenIOFiles();

	FILE * in_file = fopen("testInput.txt", "r");

	testGetUntilDelim(in_file);

	testIgnoreLine(in_file);

	testValidOperator();
}
