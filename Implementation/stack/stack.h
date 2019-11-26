//AUTHOR: Andrés Otero García
#define Stack struct __stack
#ifndef STACK
#define STACK
#include <stdbool.h>
#include "node.h"



struct __stack{
        Node* top;
        unsigned int n;
};

Stack* newStack();
void pushElement(Stack* s, void* data);
Node* popElement(Stack* s);
Node* getTop(Stack* s);
bool isEmpty(Stack* s);
unsigned int elements(Stack* s);
void destroyElements(Stack* s);


#endif
