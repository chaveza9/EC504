#ifndef _DFS_H
#define _DFS_H

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
void DFS(Stack * S, int *found, int *FirstVertex, int V, int *EdgeList,int E, int i);

#endif /*_DFS_H*/