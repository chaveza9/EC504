// Copyright 2019 Richard Brower brower@bu.edu
#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;
#include "sorting.h"

/***********************************************************
Main progam template for sorting timing
************************************************************/

int main(int argc, char *argv[])
{
  /* Timeing and IO setup */
  chrono::time_point<chrono::steady_clock> start, stop; 
  chrono::duration<double> difference_in_time;
  double difference_in_seconds; // Holds the final run time
  ifstream infile;
  
  /* Input File Size */
  int size;
 
  /* Input Data: Do NOT CHANGE */
  infile.open(argv[1]);
  if(!infile){
    cout << "Error opening file " <<endl;
    return -1;
  } 
  infile >> size;

  int *A = new int[size];
  for(int i=0; i<size ; i++)
    infile >> A[i];
  infile.close();

  /* Keep Copy of List */
  int *a_tmp = new int[size];
   for(int i=0; i<size ; i++)
     a_tmp[i] = A[i];
  
  /* slow sorting   */
  start = chrono::steady_clock::now();
  insertionsort(A,size); 
  stop = chrono::steady_clock::now();
  difference_in_time = stop - start;
  difference_in_seconds = double(difference_in_time.count());

  //Begin output file : DO NOT CHANGE
  ofstream outfile(strcat(argv[1],"_out"));
  outfile << difference_in_seconds << endl;

  //Time slow Sort
  start = chrono::steady_clock::now();
  insertionsort(A,size); 
  stop = chrono::steady_clock::now();
  difference_in_time = stop - start;
  difference_in_seconds = double(difference_in_time.count());


   //Time fast Sort

    for(int i=0; i<size ; i++)
     A[i] = a_tmp[i];
    
  start = chrono::steady_clock::now();
   mergeSort(A,  a_tmp, 0, size-1);
  stop = chrono::steady_clock::now();
  difference_in_time = stop - start;
  difference_in_seconds = double(difference_in_time.count());
  outfile << difference_in_seconds << endl;

  
  //End output file
  cout << size << endl;
  for(int i=0; i<size ; i++)
    cout << A[i] << endl;

  
  return 0;
}

