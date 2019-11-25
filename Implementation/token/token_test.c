#include "ctap.h"
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include "token.h"

#define TYPES 6

TESTS{
	void testTokenCreation(int id, int size, void* value){
		Token* test_t;
		assert(id < TYPES && id >= -1);
		if(id == -1){
			test_t = eof_token();
		}
		else{
			test_t = createToken(id);
		}
		ok(test_t->id == id, "Token of id %d creation is correct", id);
		if(id != -1) setValue(test_t, value, size);
		if(id==INTEGER_ID){
			int temp_int = *(int*) test_t->value;
			ok(temp_int == *(int*) value, "Integer token created correctly");
		}
		else if(id==DOUBLE_ID){
			double temp_double = *(double*) test_t->value;
			ok(temp_double == *(double*) value, "Double token created correctly");
		}
		else{
			char temp_char = *(char*) test_t->value;
			ok(temp_char == *(char*) value, "Token of id %d created correctly", id);
		}
		free(test_t);
 	}


	void testTokenEqual(int id1, int id2, int size1, int size2, void* value1, void* value2, bool expected, char* message){
		assert(id1 < TYPES && id1 >= -1 && id2 < TYPES && id2 >= -1);
		Token* test1, *test2;
		if(id1 == -1){ test1 = eof_token(); }
		else{
			test1 = createToken(id1);
			setValue(test1, value1, size1);
		}
		if(id2 == -1){test2 = eof_token();}
		else{
			test2 = createToken(id2);
			setValue(test2, value2, size2);
		}

		ok((isEqual(test1, test2) == expected), message);
		free(test1);
		free(test2);
	}

	int type_vector[TYPES] = {INTEGER_ID, DOUBLE_ID, LEFTP_ID, RIGHTP_ID, UNARY_ID, OPERATOR_ID};
	int size_vector[TYPES] = {sizeof(int), sizeof(double), sizeof(char), sizeof(char), sizeof(char), sizeof(char)};

	int example_int[2] = {10, 100};
	double example_double[2] = {3.1416, 2.5};
	char example_char[2] = {'+', '-'};


	void* example_values1[TYPES] = {&example_int[0], &example_double[0], &example_char[0], &example_char[0], &example_char[0], &example_char[0]};
	void* example_values2[TYPES] = {&example_int[1], &example_double[1], &example_char[1], &example_char[1], &example_char[1], &example_char[1]};
	
	for(int i = 0; i < TYPES; i++){
		testTokenCreation(type_vector[i], size_vector[i], example_values1[i]);
		testTokenEqual(type_vector[i], type_vector[i], size_vector[i], size_vector[i], example_values1[i], example_values1[i], true, "comparing two equal tokens");	
	}
		testTokenEqual(type_vector[1], type_vector[2], size_vector[1], size_vector[2], example_values1[1], example_values2[2], false, "comparing a double token and an operator token");
		testTokenEqual(type_vector[2], type_vector[3], size_vector[2], size_vector[3], example_values1[2], example_values2[3], false, "comparing two tokens with the same value but different id");
		testTokenEqual(type_vector[5], type_vector[5], size_vector[5], size_vector[5], example_values1[5], example_values2[5], false, "comparing two operator tokens with different value");
		testTokenEqual(-1,-1, 0, 0, NULL, NULL, true, "comparing two EOF tokens");

		ok(isEOF(eof_token()), "testing isEOF() with the return pointer of eof_token().\nNote: if the EOF comparing token test failed, this one is likely to fail too, as both use function eof_token()");
		srand(time(NULL));
		int r = rand() % TYPES;
		Token t;
		t.id= r;
		ok(getID(&t)== r, "getID returns expected value (%d == %d)", getID(&t), r);

		t.value = &r;
		int storedValue = *(int*)getValue(&t);
		ok(storedValue == r, "getValue returns expected value", storedValue, r);
		

	
}
