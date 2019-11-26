//AUTHOR: Andrés Otero García
#include <stdlib.h>
#include "node.h"
#include <stdio.h>

/*
 * Pre: ---
 * Post: allocated memory for a Node and returned a pointer to that memory. The field "data" of such Node is equal to "d"
 */
Node* createNode(void* d){
    Node* new = malloc (sizeof(Node));
    new->data = d;
    new->next = NULL;
    return new;
}

/*
 * Pre: let "next_n" be the "next" field of the Node pointed by "n"
 * Post: next_n=new
 */
void setNext(Node* n, Node* new){
    n->next = new;
}

/*
 * Pre: ---
 * Post: returned the "data" field of the Node pointed by "n"
 */
void* getData(Node* n){
    return n->data;
}

/*
 * Pre: ---
 * Post: returned the "next" field of the Node pointed by "n"
 */
Node* getNext(Node* n){
    return n->next;
}

/*
 * Pre: let "next(i)" be a Node in a Node linked list where the "next" field of "next(i)" points to next(i+1)
 *      "n" points to "next(0)"
 *      "next(MAX)" is the only Node of the sequence where the "next" field is equal to NULL
 *      i is a natural number and 0 <= i <= MAX
 * Post: freed "next(i)" for all possible values of i
 */
void destroy(Node* n){
	//fprintf(stderr, "c1\n");
    if(n->next != NULL){
	//fprintf(stderr, "c2\n");
	destroy(n->next);
	//fprintf(stderr, "c3\n");
	n->next = NULL;
	//fprintf(stderr, "c4\n");
    }
	
    free(n);
	//fprintf(stderr, "c5\n");
    n = NULL;
	//fprintf(stderr, "c6\n");
}
