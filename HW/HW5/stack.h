#ifndef _STACK_H
#define _STACK_H

typedef struct Stack
{
        int capacity;
        int size;
        int top;
        //int rear;
        int *elements;
}Stack;

Stack * createStack(int maxElements);
void Push(Stack *S,int element);
int Pop(Stack *S);
#endif /*_STACK_H*/