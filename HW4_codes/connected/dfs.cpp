#include "dfs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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


