#include <iostream>
#include <fstream>
#include <chrono>
#include <stdio.h>
#include <string.h>
using namespace std;

/***********************************************************
Exercise: Given two sorted arrays: A and B find
the median of the combined sorted  array: C = A + B. 
This out actual constructing C this can be done in order  
 log(smaller of the A and B array). Assume the size of the A and B 
is oded 
************************************************************/

int find_median(int *a, int n, int *b, int m);

int main(int argc, char *argv[]){

  chrono::time_point<chrono::steady_clock> start, stop; 
  chrono::duration<double> difference_in_time;
  double difference_in_seconds; // Holds the final run time
  
  ifstream infile1;
  int n;
  int m;
  int median=0;
  
  infile1.open(argv[1]);
  if(!infile1){
    cout << "Error opening file " <<endl;
    return -1;
  } 
  
    infile1 >> n;
    int *A = new int[n];
    for(int i=0; i<n ; i++)
      infile1 >> A[i];
    
    infile1 >> m;
    int *B = new int[m];
    for(int i=0; i<m ; i++)
      infile1 >> B[i];
    
    infile1.close();
    
    /* Find the median \  */
    start = chrono::steady_clock::now();
    median=find_median(A, n, B, m);
    stop = chrono::steady_clock::now();
    difference_in_time = stop - start;
    difference_in_seconds = double(difference_in_time.count());

    //Begin output file : DO NOT CHANGE
    ofstream outfile(strcat(argv[1],"_out"));
    outfile << difference_in_seconds << endl;
    outfile << median << endl;
    //End output file
     
    return 0;
}

// Function to find max 
int maximum(int a, int b)  
{ 
    return a > b ? a : b; 
} 
  
// Function to find minimum 
int minimum(int a, int b)  
{ 
    return a < b ? a : b;  
} 

int find_median(int *a, int n, int *b, int m){
int min_index = 0, max_index = n, i, j, median; 
      
    while (min_index <= max_index) 
    { 
        i = (min_index + max_index) / 2; 
        j = ((n + m + 1) / 2) - i; 
      
        if (i < n && j > 0 && b[j - 1] > a[i])         
            min_index = i + 1; 
                  

        else if (i > 0 && j < m && b[j] < a[i - 1])         
            max_index = i - 1; 
  
        else
        { 

            if (i == 0)             
                median = b[j - 1];             
              
  
            else if (j == 0)             
                median = a[i - 1];             
            else            
                median = maximum(a[i - 1], b[j - 1]);             
            break; 
        } 
    } 
      

    if ((n + m) % 2 == 1) 
        return (double)median; 
          
    if (i == n) 
        return (median+b[j]) / 2.0; 
          
    if (j == m) 
        return (median + a[i]) / 2.0; 
      
    return (median + minimum(a[i], b[j])) / 2.0; 
}
