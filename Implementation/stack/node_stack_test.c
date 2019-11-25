#include "node.h"
#include "stack.h"
#include <time.h>
#include <stdlib.h>
#include "ctap.h"

#define N 10

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
	ok(storedValue == example[0], "Created node with correct value");
	ok(n_test->next == NULL, "Created node with NULL next");

	ok(n_test->data == getData(n_test), "getData returns expected value");
	ok(n_test->next == getNext(n_test), "getNext returns expected value");

	for(int i = 0; i < N-1; i++){
		setNext(n[i], n[i+1]);
		ok(n[i]->next == n[i+1], "setNext has changed the next field of n[%d] to the address of n[%d]", i, i+1);  
	}
	destroy(n[0]);

	for(int i = 0; i < N-1; i++){
		ok(n[i]->next == NULL, "Destroyed sequence of nodes correctly (step %d/%d)", i, N);
	}

	
	

}

