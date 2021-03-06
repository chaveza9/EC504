#include <iostream>
#include <fstream>
#include <chrono>
#include <string.h>
#include "dfs.h"
#include "bfs.h"

using namespace std;

/***********************************************************
Given two arrays: FirstVertex pointing to the EdgeList with destination 
node for an undirected graph G(V,E). 

The input file begins with number of vertices (V = |V|)
and number of edges (E =|E|) and the list of value for 

int FirstVertex[V+1]
int EdgeList[E+1]

The vertices(nodes) are numbered 0,..,|V| -1.  The last entry 
FirstVertex[V] = E pointing to  EdgeList[E] = -1;
represented as a null

You are to compute the number of the connected components.

************************************************************/
void PrintAdjacencyListFormat(int *FirstVertex, int V, int *EdgeList,int E);
// void BFS(Queue * Q,, int *Found, int *FirstVertex, int V, int *EdgeList,int E);

int main(int argc, char *argv[]){

  chrono::time_point<chrono::steady_clock> start, stop; 
  chrono::duration<double> difference_in_time;
  double difference_in_seconds_BFS; // Holds the final run time for BFS
  
  ifstream infile1;
  int V;
  int E;
  int NumberCC_BFS;
  
  infile1.open(argv[1]);
  if(!infile1){
    cout << "Error opening file " <<endl;
    return -1;
  } 
  
     infile1 >> V;
     infile1 >> E;
    
    int *FirstVertex = new int[V+1];
    for(int i=0; i< V +1 ; i++) 
      infile1 >> FirstVertex[i];  //  Note: FirstVertex[V] = E  fake extra link
    
    int *EdgeList = new int[E+1];
    for(int i=0; i< E +1 ; i++)
      infile1 >> EdgeList[i];   // Note  EdgeList[E] = -1;  is null flag
    
    infile1.close();

 #if 1 // set to 1 to debug 
     cout << endl << "A print in Adjacency  List form to help with Debugging! " << endl;
     PrintAdjacencyListFormat(FirstVertex, V, EdgeList, E);
#endif
    
    /* Find NumberCC_BFS   */
    start = chrono::steady_clock::now();
    NumberCC_BFS=find_connected_components_BFS(FirstVertex, V, EdgeList,E);
    stop = chrono::steady_clock::now();
    difference_in_time = stop - start;
    difference_in_seconds_BFS = double(difference_in_time.count());

    //Begin output file : DO NOT CHANGE
    ofstream outfile(strcat(argv[1],"_out"));
    outfile << difference_in_seconds_BFS << endl;
    outfile << NumberCC_BFS << endl;
    //     outfile << difference_in_seconds_DFS << endl;  
    //   outfile << NumberCC_DFS << endl;
    //End output file
     
    return 0;
}

void PrintAdjacencyListFormat(int *FirstVertex, int V, int *EdgeList,int E)
{
	int v;
	int e;
	cout << "V = " << V << "  E = " <<E <<endl;
	for( v = 0; v < V; v++)
	{
		cout << endl;
		cout << v  << ": ";

		for(e = FirstVertex[v]; e < FirstVertex[v+1]; e++) 
			cout << EdgeList[e]<< "-> ";

		cout <<"nil";
	}

	cout << endl;
	cout << v  << " : ";
	cout << EdgeList[e]  << " That's Edge List  nil  Folks " << endl;
}


