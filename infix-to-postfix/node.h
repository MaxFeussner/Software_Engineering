#define Node struct __node
#ifndef NODE
#define NODE

struct __node{
        void* data;
        Node* next;
};

Node* createNode(void* d);
void setNext(Node* n, Node* new);
void* getData(Node* n);
Node* getNext(Node* n);
void destroy(Node* n);

#endif