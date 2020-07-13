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
int find_connected_components_DFS(int *FirstVertex, int V, int *EdgeList,int E);
#endif /*_DFS_H*/