// Copyright 2018 Richard Brower brower@bu.edu
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
//#include <malloc.h>
#include <time.h>
#define maxnodes 200000
#define maxarcs  500000
#define LARGE 99999999

 using namespace std;


clock_t clock(void);

struct arc{
  struct arc *next;
  int length;
  int end;
  };
struct node{
   struct arc *first; /* first arc in linked list */
   int D;  /* Distance estimate */
   int P;  /* Predecessor node in shortest path */
   int Q;  /* Position of node in heap, from 1 to Nm, where 1 is best */
   };
struct node Nodes[maxnodes];
int HP[maxnodes]; /* heap array, points to node in position */
int Na,Nm,Or;

void BellmanFord()
{
  
}/* end Bellman-Ford */
/* ---------------*/


void Dijkstra()
{
   
} /* end Dijkstra */

/* ---------------*/




int main(int argc, char *argv[])
{
  double TT2;
  clock_t startt, endt; 
  int start,val,col;
  struct arc *edge, test;
  long c0=0;
  long c1 = 0;
  FILE *fp1,*fpout;
  char *infile;
  char *outfile;
  int destinations[10];
/*......................*/

/* For simplicity, we will skip node 0, label all with true nodes */
 // printf("Enter file name for input \n");
 // scanf("%s",infile);
// strcpy(infile, argv[1]);
  infile =  argv[1];
 cout <<" infile  " << infile << endl;
  fp1 = fopen(infile,"r");
  if (fp1 == NULL) {
	  printf("Did not find input file \n");
	  exit(1);
  }
  fscanf(fp1,"%d %d",&Nm,&Na);
  for (int i=0;i<=Nm;i++){
	Nodes[i].first = NULL;
	Nodes[i].D = LARGE;
	Nodes[i].P = 0;
	Nodes[i].Q = 0;
  }

  for (int i=0;i<Na;i++){ 
     fscanf(fp1,"%d %d %d",&start,&col,&val);
     edge = (struct arc *)malloc(sizeof(test));
     edge->length = val; edge->end = col;
     edge->next = Nodes[start].first;
     Nodes[start].first=edge;
  }
  fclose(fp1);
  for (int i = 0; i < 10; i++) {
	  destinations[i] = (int)((i + 1)*(Nm / 10) - 1 );
  }

  outfile = strcat(infile,"_out");
  fpout = fopen(outfile,"w");

  cout << " fpout " << outfile << endl;
//#include <fstream>
  Or = 1; // source node


  fprintf(fpout,"CALLING DIJKSTRA/HEAP TO SOLVE THE PROBLEM\n");

  startt = clock(); 
  Dijkstra();
  endt = clock();
  TT2 = (double)(endt-startt)/CLOCKS_PER_SEC;
  //printf("FINISHED --- TOTAL CPU TIME %f SECS \n",(float)TT2);
 // fprintf(fpout,"FINISHED --- TOTAL CPU TIME %f SECS \n",(float)TT2);

  for (int i = 0; i < 10; i++) {
	  col = destinations[i];
	  fprintf(fpout,"Shortest distance to %d is %d \n", col, Nodes[col].D);         
	  fprintf(fpout,"path to %d ", col);
	  col = Nodes[col].P;
	  while (col > 0) {
		  fprintf(fpout," -- %d ", col);
		  col = Nodes[col].P;
	  }
	  fprintf(fpout,"\n \n");
  }
  
  for (int i=0;i<=Nm;i++){
	Nodes[i].D = LARGE;
	Nodes[i].P = 0;
	Nodes[i].Q = -1;
  }

  /* ------------------------------*/
  for (int i=0;i<=Nm;i++){
	Nodes[i].D = LARGE;
	Nodes[i].P = 0;
	Nodes[i].Q = -1;
  }

  fprintf(fpout,"CALLING Bellman-Ford TO SOLVE THE PROBLEM\n");

  startt=clock();
  BellmanFord();
  endt = clock();
  //TT2 = (double)(endt-startt)/CLOCKS_PER_SEC;
  //printf("FINISHED --- TOTAL CPU TIME %f SECS \n",(float)TT2);

  for (int i = 0; i < 10; i++) {
	  col = destinations[i];
	  fprintf(fpout,"Shortest distance to %d is %d \n", col, Nodes[col].D);         
	  fprintf(fpout,"path to %d ", col);
	  col = Nodes[col].P;
	  while (col > 0) {
		  fprintf(fpout," -- %d ", col);
		  col = Nodes[col].P;
	  }
	  fprintf(fpout,"\n \n");
  }
/*  -------------*/
  fclose(fpout);

  return 0;
}

