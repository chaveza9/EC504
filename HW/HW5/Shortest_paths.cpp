/***************************************************
Shortest path algorithms on G(N,A) with the node
labled 1, 2, ..., |N| = Nm and Arcs 1,..., |A| = Na
Read form files 
Or = 1 set source node to 1 ;
Implemtation of 1 to All by  Dijkstra and  Bellman Ford.

***********************************************/
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>   // enable cout.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "graph.h"
#include "stack.h"
#include "heap.h"
#define maxnodes 200000
#define maxarcs  500000
#define LARGE 99999999

 using namespace std;


//clock_t clock(void);
int HP[maxnodes]; /* heap array, points to node in position */
void BellmanFord(Graph *graph, int src);
void Dijkstra(Graph *graph, int src);
void printPath(Graph *graph, int src, FILE *fpout);
//void printPath2(Graph *graph, int src, FILE *fpout);

int main(int argc, char *argv[])
{
  int Na,Nm,Or;
  double TT2;
  clock_t startt, endt; 
  int start,val,col;
  long c0=0;
  long c1 = 0;
  FILE *fp1,*fpout;
  char *infile;
  char *outfile;
/*......................*/

/* For simplicity, we will skip node 0, label all with true nodes */

  // Call input file with graph
  infile =  argv[1];
  cout <<" infile  " << infile << endl;
  fp1 = fopen(infile,"r");
  if (fp1 == NULL) {
	  printf("Did not find input file \n");
	  exit(1);
  }
  printf("Building Graph\n");
  // Initialization Label of nodes to infinity
  fscanf(fp1,"%d %d",&Nm,&Na);
  // Create Graph
  Graph* graph = createGraph(Na,Nm);
  // Extract edges from graph (edge = outnode=>innode, weight)
  for (int i=0;i<Na;i++){ 
     fscanf(fp1,"%d %d %d",&start,&col,&val);
     addEdge(graph, start, col, val);
  }
  printf("Graph Done\n");
  printGraph(graph);
  
  // Close graph input file
  fclose(fp1);
  // Create output file
  outfile = strcat(infile,"_out");
  fpout = fopen(outfile,"w");
  cout << " fpout " << outfile << endl;
  // Shortest path Computation1
  Or = 5; // source node
  /*------------- Dijkstra-----------*/
  printf("CALLING DIJKSTRA/HEAP TO SOLVE THE PROBLEM\n");
  fprintf(fpout,"CALLING DIJKSTRA/HEAP TO SOLVE THE PROBLEM\n");

  startt = clock(); 
  Dijkstra(graph, Or);
  endt = clock();
  TT2 = (double)(endt-startt)/CLOCKS_PER_SEC;
  printf("FINISHED --- TOTAL CPU TIME %f SECS \n",(float)TT2);
  fprintf(fpout,"FINISHED --- TOTAL CPU TIME %f SECS \n",(float)TT2);
  printPath(graph, Or, fpout);
 /*-------------Bellman Ford----------------------*/
 
 // Initialization Label of nodes to infinity
  /* ------------------------------*/
  //resetNodeLabels(graph);
  printf("CALLING Bellman-Ford TO SOLVE THE PROBLEM\n");
  fprintf(fpout,"CALLING Bellman-Ford TO SOLVE THE PROBLEM\n");
  startt = clock();
  BellmanFord(graph,Or);
  endt = clock();
  TT2 = (double)(endt-startt)/CLOCKS_PER_SEC;
  printf("FINISHED --- TOTAL CPU TIME %f SECS \n",(float)TT2);
  fprintf(fpout,"FINISHED --- TOTAL CPU TIME %f SECS \n",(float)TT2);
  printPath(graph, Or, fpout);
  
/*  -------------*/
  fclose(fpout);

  return 0;
}

void printPath(Graph *graph, int src, FILE *fpout){
  // Extract graph properties
  int V = graph->Nm;
  // Create destination stack
  Stack *Destinations = createStack(V);
  ///util variables
  int col, count;
  for(int i=1; i<=V; i++){
    fprintf(fpout,"Shortest distance to %d is %d \n", i, graph->array[i].D);
    //handle if there is no path to node
    if(graph->array[i].D==LARGE){
      fprintf(fpout,"%d \n \n", i);
      continue;
    }
    col = graph->array[i].P;
    Push(Destinations,i);
    // fill destinations stack
    while(col!=src)
    {
      Push(Destinations,col);
      col = graph->array[col].P;
      if(Destinations->size==Destinations->capacity)
        break;
    }
    fprintf(fpout,"%d ", src);
    // Print path
    while( Destinations->size>0 )
    {
      fprintf(fpout,"--> %d ", Pop(Destinations));
    }
    fprintf(fpout,"\n \n");
  }
}

void BellmanFord(Graph *graph, int src)
{
  int V = graph->Nm;
  int E = graph->Na;
  // temporary variables
  int i,j, u, v, cost, count; 
  int weight; //current distance of vertex
  arc* edge =(arc*)malloc(V*sizeof(arc));
  // Initialize distances from src to other vertices as inf
  resetNodeLabels(graph);
  // initialize distance from source
  graph->array[src].D = 0;
  graph->array[src].P = src;
  // Relax all edges Nm-1 times
  for(int i =1;i<=V-1;i++){
    // Traverse through all vertices (the extracted 
		// vertex) and update their distance values 
    for(int u=1;u<=V;u++){
      edge = graph->array[u].first;
      count = 0;
      while (edge != NULL)
      {
        count++;
        v = edge->end; //Extract destination vertex
        weight = edge->length; // extract length of edge
        cost = graph->array[u].D + weight;
        if(graph->array[u].D != LARGE && cost< graph->array[v].D) 
        {
          // relax node
          graph->array[v].D = cost;
          // update predecessor node
          graph->array[v].P = u;
        }
         // go to next node
          edge = edge->next;      
      }   
    }
  }
  // Check for negative cycles by checking if there is 
  // a shorter path
  for(int u=1;u<=V;u++){
      edge = graph->array[u].first;
      while (edge != NULL)
      {
        v = edge->end; //Extract destination vertex
        weight = edge->length; // extract length of edge
        if(graph->array[u].D != LARGE && graph->array[u].D + weight
            < graph->array[v].D)
        {
          printf("Graph contains negative cycle");
          return;
        }
        // go to next node
        edge = edge->next;
      }    
    }
  
}/* end Bellman-Ford */
/* ---------------*/

void Dijkstra(Graph *graph, int src)
{
  //util variables
  int u,v, weight;
  arc* edge = (arc*)malloc(sizeof(arc));
  MinHeapNode_t* minHeapNode = 
    (MinHeapNode_t*)malloc(sizeof(MinHeapNode_t));
  // Extract Graph parameters
	int Nm = graph->Nm;// Get the number of vertices in graph 
	// minHeap represents set E 
	MinHeap_t* minHeap = createMinHeap(Nm); 
	// Initialize min heap with all vertices including its distances. 
  // Initialize labelswith high value
  resetNodeLabels(graph);
  // initialize distance from source
  graph->array[src].D = 0;
  graph->array[src].P = src;
  // populate heap with initial distances
	for (int i = 0; i < Nm; ++i) 
	{ 
		minHeap->array[i] = newMinHeapNode(i, graph->array[i+1].D); 
		// Update position on Queue
    minHeap->pos[i] = i; 
	} 

	// Make dist value of src vertex as 0 so that it is extracted first 
	minHeap->array[src-1] = newMinHeapNode(src-1, graph->array[src].D); 
	minHeap->pos[src-1] = src-1; 
  //graph->array[src].Q = src;
  graph->array[src].P = src;
	decreaseKey(minHeap, src-1, graph->array[src].D); 
	// Initial size of min heap is equal to Nm 
	minHeap->size = Nm; 

	// In the followin loop, min heap contains all nodes 
	// whose shortest distance is not yet finalized. 
	while (minHeap->size != 0) 
	{ 
    // Extract the vertex with minimum distance value 
		minHeapNode = dequeue(minHeap); 
		u = minHeapNode->v+1; // Store the extracted vertex n
		// Traverse through adjacent vertices of u  
		edge = graph->array[u].first; 
		while (edge != NULL) 
		{ 
			v = edge->end; 
      weight = edge->length; // extract length of edge
			// relax node
			if (isInMinHeap(minHeap, v-1) && graph->array[u].D != LARGE && 
										weight + graph->array[u].D < graph->array[v].D) 
			{ 
        // relax node
				graph->array[v].D = graph->array[u].D + weight; 
        // update predecesor value
        graph->array[v].P = u;
				// update distance value in min heap as well
				decreaseKey(minHeap, v-1, graph->array[v].D); 
			} 
			edge = edge->next; 
		} 
	}  
} /* end Dijkstra */

/* ---------------*/