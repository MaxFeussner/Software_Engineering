#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"
#include "node.h"

/*
 * Pre: ---
 * Post: returns a stack with 0 elements
 */
Stack* newStack(){
    Stack* new = malloc(sizeof(Stack));
    new->n = 0;
    return new;
}

/*
 * Pre: "s" is not a null pointer
 * Post: the top of stack "s" is now a Node with pointer "data". incremented the number of elements by 1
 */
void pushElement(Stack* s, void* data){
    Node* aux = createNode(data);
    setNext(aux, s->top);
    s->top = aux;
    s->n++;
}

/*
 * Pre: "s" is not a null pointer. let s(i) be the elements of "s" (s(0) is the top)
 * Post: the top of stack "s" is now s(1). decremented the number of elements by 1
 *       returned s(0)
 */
Node* popElement(Stack* s){
    Node* aux = s->top;
    s->top = getNext(aux);
    s->n--;
    return aux;
}


/*
 * Pre: "s" is not a null pointer. let s(i) be the elements of "s" (s(0) is the top)
 * Post: returned s(0)
 */
Node* getTop(Stack* s){
    return s->top;
}

/*
 * Pre: "s" is not a null pointer.
 * Post: returned true if and only if "s" had 0 elements
 */
bool isEmpty(Stack* s){
    return s->n==0;
}

/*
 * Pre: "s" is not a null pointer.
 * Post: returned the amount of Nodes in "s"
 */
unsigned int elements(Stack* s){
    return s->n;
}

/*
 * Pre: ---
 * Post: freed the allocated memory for all the nodes in "s"
 */
void destroyElements(Stack* s){
    if(s->top != NULL) destroy(s->top);
}
