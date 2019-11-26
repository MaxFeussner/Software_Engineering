//AUTHOR: Andrés Otero García
#include "node.h"
#include "stack.h"
#include <time.h>
#include <stdlib.h>
#include "ctap.h"

#define N 10
#define N_TESTS 5

TESTS{
	
	//node testing:
	int example[N] = {10, 100};
	Node* n[N];
	for(int i = 0; i < N; i++){
		n[i] = createNode(&example[1]);
		n[i]->data = &example[i];
		n[i]->next = NULL;
	}
	

	Node* n_test = createNode(&example[0]);
	int storedValue = *(int*)n_test->data;
	//createNode
	ok(storedValue == example[0], "Created node with correct value");
	ok(n_test->next == NULL, "Created node with NULL next");

	//getData
	ok(n_test->data == getData(n_test), "getData returns expected value");

	//getNext
	ok(n_test->next == getNext(n_test), "getNext returns expected value");

	//setNext
	for(int i = 0; i < N-1; i++){
		setNext(n[i], n[i+1]);
		ok(n[i]->next == n[i+1], "setNext has changed the next field of n[%d] to the address of n[%d]", i, i+1);  
	}
	
	destroy(n[0]);

	//destroy
	for(int i = 0; i < N-1; i++){
		ok(n[i]->next == NULL, "Destroyed sequence of nodes correctly (step %d/%d)", i, N);
	}

	free(n_test);

	
	//stack testing:
	Stack* s = newStack();
	ok(s != NULL, "newStack returns a valid pointer");
	ok(s->n == 0, "newStack returns a pointer to an empty stack");

	//pushElement
	pushElement(s, &example[0]);
	pushElement(s, &example[1]);

	ok(s->n == 2, "pushElement updated number of elements correctly");

	int temp_value1 = *(int*) getData(s->top);
	int temp_value2 = *(int*) getData(s->top->next);
	ok(temp_value1 == example[1], "First element was pushed correctly (%d == %d)", temp_value1, example[1]);
	ok(temp_value2 == example[0], "Second element was pushed correctly (%d == %d)", temp_value2, example[0]);

	//getTop
	Node* temp_node1 = getTop(s);
	temp_value1 = *(int*) getData(temp_node1);
	temp_value2 = *(int*) getData(s->top);
	ok(temp_value1 == temp_value2, "Values of getTop and the current top of the stack are equal (%d == %d)", temp_value1, temp_value2);

	//popElement
	Node* temp_node2 = popElement(s);
	//temp_value1 is value of previous stack top
	temp_value2 = *(int*) getData(temp_node2);
	//temp_value3 is value of new stack top
	int temp_value3 = *(int*) getData(s->top);
	

	ok(temp_value1 == temp_value2, "popElement returned top of the stack");
	ok(temp_value1 != temp_value3, "After running popElement, top of the stack is the next node");

	//isEmpty
	Stack * temp_s = newStack();
	ok(isEmpty(temp_s), "isEmpty returned true with an empty stack");
	ok(!isEmpty(s), "isEmpty returned false with a stack with 1 element");

	//elements

	ok(elements(s) == s->n, "elements returned the number of elements of the stack (1/2)");
	ok(elements(temp_s) == temp_s->n, "elements returned the number of elements of the stack (2/2)");

	//destroyElements

	int examples_int[N_TESTS];
	Node * node_vector[N_TESTS];
	Stack * s2 = newStack();
	for(int i = 0; i < N_TESTS; i++){
		examples_int[i] = rand();
		pushElement(s2, &examples_int[i]);
		node_vector[i] = getTop(s2);
	}
	destroyElements(s2);
	for(int i = 0; i < N_TESTS; i++){
		ok(node_vector[i]->next == NULL, "destroyElements has destroyed node (%d/%d)", i, N_TESTS-1);
	}
	
	free(s);
	free(s2);
	free(temp_s);
	free(temp_node1);
	//temp_node2 is equal to temp_node1, therefore doesn't have to be freed
	

}

