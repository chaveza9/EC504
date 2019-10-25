#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
using namespace std;


/***********************************************************
Main progam template test BST Search 
************************************************************/

static int OpCount = 0;

int localSize = 10;
int numPermutations = 10;
int deletionNum = 500;

int  uniform(int  m);
void initialize_and_permute(int permutation[], int n);
double average (int array[], int size);
void swap(int* a, int* b);



int main(int argc, char *argv[]) 
{

   /* Timeing and IO setup */
  chrono::time_point<chrono::steady_clock> start, stop; 
  chrono::duration<double> difference_in_time;
  double difference_in_seconds_heap_sort;  // Holds the final run time
  ifstream infile;
  ofstream outfile;
  
  // Define Random List Sizes
  int N[] = {8,18,32,512,1024};
  int treeHeight[numPermutations];
  /* Local data */
  int n;
  int i, k; // iterators
 
  
  // Input Data:  DO NOT CHANGE 
  infile.open(argv[1]);

  int* InputList = NULL;
  
  if(!infile)
    {
      cout << "No input files so put in InputList file of size = "<<  localSize  << endl;
      n = localSize;
      cout << "n  = " << n << endl;
      InputList = new int[n+1];
      InputList[0] = n;  // Set zero entry in in heap to n
      for(int i=1; i<n+1 ; i++)  InputList[i] = rand()%100000;
      // Define out put file
       outfile.open("SortedRandomList.dat");
    }
  else
    {
      infile >> n;
      InputList = new int[n+1];
      InputList[0] = n;  // Set zero entry in in heap to n	    
      for(int i=1; i<n+1 ; i++) infile >> InputList[i];
      infile.close();
      // Define out put file 
      //outfile.open(strcat(argv[1],"_out"));
    }

    /* results print */
    ofstream myfile ("nodeHeight.dat");
    if (!myfile.is_open())
    {
        cout<<"File could not be Handled"<<endl;
        return -1;
    }
    //Headers for array
    myfile << "# Node lenght \t Average Height"<<endl;

    int* NodeArray = NULL;
    int sizeArray;
    int delIndx [deletionNum]; 
   

    // Create Empty Tree
    SearchTree T;
    Position P;
   for( int j =0; j< 5; j++)
   {
        sizeArray = N[j];
       
        // Define Array for permutations
        NodeArray = new int[sizeArray];
        

        //for( i = 1; i < InputList[0]; i++ )
        for( i = 1; i < N[j]; i++ )
            NodeArray[i] = InputList[i];
        
        
        for (k = 0; k < numPermutations; k++)
        {
            // Empty Previous Tree
            T = MakeEmpty( NULL );
            for( i = 0; i < sizeArray ; i++ )
                T = Insert( NodeArray[i], T );
            // Store tree Height
            treeHeight [k]= getHeight (T);
            cout <<"Node Size:"<<sizeArray<<"\tPermutation:"<< k+1<<"\t Height:"<< treeHeight [k]<<endl;
            // Permute array
            initialize_and_permute(NodeArray , sizeArray); 

        }
        // Compute Average and print
        
        myfile << sizeArray<< "\t" << average(treeHeight,numPermutations) <<endl;
        
        if(sizeArray==1024)
        {
            cout << "Analysis Part 2"<<endl;
            cout << "created"<<endl;
            cout<<" Height Before Deletion:"<< getHeight(T)<<endl;
            // Delete Elements from Array
            for (i = 0; i < deletionNum; i++)
            {
                delIndx[i] = NodeArray[rand()%1024]; 
                //cout<<"val to be deleted: "<<delIndx[i]<<endl;
                T = Delete(delIndx[i], T );    
            }

            cout<<" Size After Deletion:" <<getHeight(T)<<endl;
            // Insert Values into tree again
            for (i = 0; i < deletionNum; i++)
            {
                T = Insert(  delIndx[i], T );    
            }
            cout<<" Size After Insertion:" <<getHeight(T)<<endl;
              
        }

        // delete Array
        delete[] NodeArray;
   } 

    return 0;
}

void swap(int* a, int* b)
{
    int temp;
    temp = *a; 
    *a = *b; 
    *b = temp; 
}
int  uniform(int  m)
{
  return rand() % m;
}  

void initialize_and_permute(int permutation[], int n)
{
  
    for (int i = 0; i <= n-2; i++) {
        int  j = i+uniform(n-i); /* A random integer such that i ≤ j < n */
        swap(permutation[i], permutation[j]);   /* Swap the randomly picked element with permutation[i] */
    }
}

double average (int array[], int size){
    double sum;
    for (int i = 0; i < size; i++)
    {
        sum = sum + array[i];
    }
    double avg = sum/size;
    return avg;
}