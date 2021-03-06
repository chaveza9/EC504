#include "bfs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

/* QUEUE FUCTIONS */

Queue * createQueue(int maxElements)
{
    /* Create a Queue */
    Queue *Q;
    Q = (Queue*)malloc(sizeof(Queue));
    /* Initialise its properties */
    Q->elements = (int *)malloc(sizeof(int)*maxElements);
    Q->size = 0;
    Q->capacity = maxElements;
    Q->front = 0;
    Q->rear = -1;
    /* Return the pointer */
    return Q;
}

void Enqueue(Queue *Q,int element)
{
    /* If the Queue is full, we cannot push an element into it as there is no space for it.*/
    if(Q->size == Q->capacity)
    {
        printf("Queue is Full\n");
    }
    else
    {
        Q->size++;
        Q->rear = Q->rear + 1;
        /* As we fill the queue in circular fashion */
        if(Q->rear == Q->capacity)
        {
            Q->rear = 0;
        }
        /* Insert the element in its rear side */ 
        Q->elements[Q->rear] = element;
    }
    return;
}

int  Dequeue(Queue *Q)
{
        int  element = -1;
    /* If Queue size is zero then it is empty. So we cannot pop */
    if(Q->size==0)
    {
        printf("Queue is Empty\n");
        return element;
    }
    /* Removing an element is equivalent to incrementing index of front by one */
    else
    {       
        element = Q->elements[Q->front];
        Q->size--;
        Q->front++;
        /* As we fill elements in circular fashion */
        if(Q->front==Q->capacity)
        {
            Q->front=0;
        }
    }
    return element;
}

int find_connected_components_BFS(int *FirstVertex, int V, int *EdgeList,int E)
{  
    int NumberCC_BFS  = 0;
    int *Found = new int[V];
    std::fill_n(Found, V, -1);
    Queue *Q = createQueue(V);
    for (int i = 0; i < V; i++)
    {
        if (Found[i]==-1)
        {
            BFS(Q,Found, FirstVertex, V, EdgeList, E, i);    
            NumberCC_BFS++;
        }
    } 
    return NumberCC_BFS;
}

void BFS(Queue * Q, int *found, int *FirstVertex, int V, int *EdgeList,int E, int s)
{
    // Definition of artificial variables
    int e;      //edge
    int v;      //vertex
    //Populate visited verted array with falses to initiate
//    std::fill_n(found,V,-1);
    // mark vertex as found
    found[s] = 1;
    //Enqueue first vertex
    Enqueue(Q,s);
    // Continue until queue is empty
    while (Q->size > 0)
    {
        // dequeue front
        s = Dequeue(Q);
        // Get all adjacent vertices from vertex
        for(e = FirstVertex[s];e<FirstVertex[s+1];e++)
        {
            // extract vertex from edge list
            v = EdgeList[e];
            // check if node has been visited
            if(found[v]==-1)
            {
                // Mark as visited
                found[v] = 1;
                // Enqueue vertex
                Enqueue(Q,v);
            }
        }
        std::cout<<"OUT:"<< s <<std::endl;
    }
}
