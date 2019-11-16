#include "dfs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

//Stack Functions Defitinition

/* STACK FUNCTIONS */
Stack * createStack(int maxElements)
{
    /* Create a Stack */
    Stack *S;
    S = (Stack*)malloc(sizeof(Stack));
    /* Initialise its properties */
    S->elements = (int *)malloc(sizeof(int)*maxElements);
    S->size = 0;
    S->capacity = maxElements;
    S->top = -1;
    /* Return pointer containing stack */
    return S;
}

void Push(Stack *S,int element)
{
    /* If the Queue is full, we cannot push an element into it as there is no space for it.*/
    if(S->size == S->capacity)
    {
            printf("Stack is Full\n");
    }
    else
    {
        // Increment top pointer
        S->top++;
        // increment size pointer
        S->size++;
        /* Insert the element in its rear side */ 
        S->elements[S->top] = element;
    }
    return;
}

int  Pop(Stack *S)
{
    // Deine a return element integer
    int  element = -1;
    /* If Stack size is zero then it is empty. So we cannot pop */
    if(S->size==0)
    {
        printf("Stack is Empty\n");
        return element;
    }
    /* Removing an element is equivalent to decrementing index of top by one */
    else
{       element = S->elements[S->top];
        S->size--;  // Decrease stack size
        S->top--; //Decrease top index
    }
    return element;
}

/* DFS FUNCTIONS */
void DFS(Stack * S, int *found, int *FirstVertex, int V, int *EdgeList,int E, int i)
{
    // Definition of artificial variables
    int e;      //edge
    int w;      //vertex
    int count = 0;
    //Populate visited vertex array with falses to initiate
    bool *visited = new bool[V];
    std::fill_n(visited,V,false);
    //Push first vertex
    Push(S,i);
    // Continue until queue is empty
    while (S->size > 0)
    {
        // Pop vertex from stack and print 
        i = Pop(S);
        // Mark vertex as visited only if it has not been visited
        if (!visited[i])
        {
            std::cout<<"OUT:"<<i<<std::endl;
            found[count] = i; // dumm
            visited[i] = true;
            // Get all adjacent vertices from vertex
            for(e = FirstVertex[i];e<FirstVertex[i+1];e++)
            {   
                // extract vertex from edge list
                w = EdgeList[e];
                //if a adjacent has not been visited, push to stack
                if (!visited[w])
                {
                    Push(S,w);
                }
            }
        }
        // increase found counter
        count++;
    }
}

