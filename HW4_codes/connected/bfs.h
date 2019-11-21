#ifndef _BFS_H
#define _BFS_H


typedef struct Queue
{
    int capacity;
    int size;
    int front;
    int rear;
    int *elements;
}Queue;

Queue * createQueue(int maxElements);
void Enqueue(Queue *Q,int element);
int Dequeue(Queue *Q);
int find_connected_components_BFS(int *FirstVertex, int V, int *EdgeList,int E);
void BFS(Queue * Q, int *found, int *FirstVertex, int V, int *EdgeList,int E, int s);

#endif /*_BFS_H*/