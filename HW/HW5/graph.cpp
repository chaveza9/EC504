#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define LARGE 99999999

// Create Graph
Graph* createGraph(int Na, int Nm){
    // create empty graph
    Graph* graph = (struct Graph*) malloc(sizeof(struct Graph)); 
	graph->Na = Na; // number of arcs
    graph->Nm = Nm; // number of nodes
	// Create an adjacency list array with size Na
	graph->array = (struct Node*) malloc(Nm * sizeof(Node)); 
	/*  Initialize each adjacency list as empty by making head as NULL 
     Since this node structure will be also used as part of the tagg algorithms
     initialize labels as infinite, and heap position and predecessor node as 0 for shortest 
    path */
	for (int i = 0; i < Nm; ++i) {
		graph->array[i].first = NULL;
        graph->array[i].D = LARGE;
        graph->array[i].P = 0;
        graph->array[i].Q = -1;
    }
	return graph; 
};
// Include edge
void addEdge(Graph* graph, int start, int dest, int weight){
    // Add edge to from start to dest. 
    arc* edge = (arc *)malloc(sizeof(arc));
    // Populate lenght of arc and arc destination
    edge->length = weight; edge->end = dest;
    //Include new edge to the adjacency list of src. 
    // Node is added at the beginning 
    edge->next = graph->array[start].first;
    graph->array[start].first = edge;
};

void resetNodeLabels(Graph* graph){
    int Nm = graph->Nm;
    for (int i=0;i<Nm;i++){
        graph->array[i].D = LARGE;
        graph->array[i].P = 0;
        graph->array[i].Q = -1;
  }
}

void printGraph(Graph* graph){
    int V = graph->Nm;
    // util variables
    int v, weight;
    arc* edge = (arc*)malloc(sizeof(arc));
    for(int u=1;u<=V;u++){
        printf("%d -->", u);
        edge = graph->array[u].first;
        while (edge != NULL)
        {
            v = edge->end; //Extract destination vertex
            weight = edge->length; // extract length of edge
            printf("%d,%d -->",v, weight);
            // go to next node
            edge = edge->next;
        }
        printf("NIL \n"); 

    }  
    printf("\n"); 
    free(edge);
}