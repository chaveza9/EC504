#ifndef _GRAPH_H
#define _GRAPH_H
// structure to define edges with weight
typedef struct arc
{
    arc *next;      //next node
    int length;     // weight of arc
    int end;        //destination
}arc;

// structure to define adjacency list node
typedef struct Node{
   arc *first; /* first arc in linked list */
   int D;  /* Distance estimate */
   int P;  /* Predecessor node in shortest path */
   int Q;  /* Position of node in heap, from 1 to Nm, where 1 is best */
}Node;

// Structure to represent a graph
typedef struct Graph
{
    int Na;     // number of nodes
    int Nm;     // number of vertex
    Node* array;
}Graph;

// Create Graph
Graph* createGraph(int Na, int Nm);
// Include edge
void addEdge(Graph* graph, int start, int dest, int weight);
// function to reset node labels
void resetNodeLabels(Graph* graph);
void printGraph(Graph* graph);
#endif /*_GRAPH_H*/