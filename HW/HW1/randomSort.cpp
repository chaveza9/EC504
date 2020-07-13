#include<iostream>
#include<iomanip>
#include <cstdlib> 
#include <time.h>
#include <math.h>
#include <fstream>
using namespace std;


static int swapCount = 0;

void swap(int* a, int* b);
void insertionsort(int a[], int N);
void initialize_and_permute(int permutation[], int n);
int  uniform(int  m);

/* There are other O(N^2) sorting algorithms you can check if you wish  */
void bubblesort(int a[], int N);
void selectionsort(int a[], int N);

int main()
{
  // Change seed for permutation array
  srand (time(NULL));
  int Asize = 100;
  int *a = new int[Asize];

  /* results print */
  ofstream myfile ("printPerm.txt");
  if (!myfile.is_open())
  {
    cout<<"File could not be Handled"<<endl;
    return -1;
    }
  myfile << "permutation num \t num of swaps"<<endl;
for(int i = 0;i<Asize;i++)  a[i] = (rand() +1)%1000000  ;
   
 cout << Asize << "\n";
 for(int i = 0;i<Asize;i++)
     cout << a[i] << "\n";
 
 int Ncases = 1000;
 int TotalNoOfSwaps = 0;
 double AverageNoOfSwaps = 0.0;
 
 for(int j = 0; j < Ncases; j++)
   {
    insertionsort(a, Asize);
    //bubblesort(a, Asize);
    cout << "Case = " << j << "   swapCount " << swapCount << endl;
    myfile << j << "\t" << swapCount << endl;
    TotalNoOfSwaps += swapCount;
    initialize_and_permute(a , Asize); 
    swapCount = 0;
    
   }

// close File
myfile.close();

 /* Make table of Sizes and Average number of Sorts */

 AverageNoOfSwaps = TotalNoOfSwaps/(double)Ncases;
 
 cout << "For N = " << Asize << "Average No of Swaps =  "<<  AverageNoOfSwaps << endl; 
 
  return 0;
}

void insertionsort(int a[],  int N)
  { 
    int i, j; 
    for (i = 1; i < N; i++){
      for (j = i; (j>0) && (a[j]< a[j-1]); j--){
        swap(&a[j],&a[j-1]);
        swapCount+=1;
      }
    }
  }

/****************************************
Provide funtions below
****************************************/

void swap(int* a, int* b)
{
  // put in swapCount
    int temp;
    temp = *a; 
    *a = *b; 
    *b = temp; 
}

// Returns a random integer 0 <= uniform(m) <= m-1 with uniform distribution 
int  uniform(int  m)
{
  // Return a random number from uniform distribution
  int x = rand()%m;
  //cout<<"random number is "<<x<< endl;
  return x;
}  

// See Knuth's shuffles https://en.wikipedia.org/wiki/Random_permutation 
void initialize_and_permute (int permutation[], int n)  
{   
  int j;
    for (int i = n - 1; i > 0; i--)  
    {  
        // pick a random number from uniform distribution  
        j = uniform (i + 1);  
  
        // Swap ith element from array at random index  
        swap(&permutation[i], &permutation[j]);  
    }  
}  

/* Other O(N^2) Sorting Algorithns */


void bubblesort(int a[], int N)
{
  int i, j;
  for (i = 0; i < N-1; i++)
    for (j = N-1; j > i; j--)
      if (a[j] < a[j-1]){ 
        swap(&a[j], &a[j-1]);
        swapCount+=1;}

}


void selectionsort(int a[], int N)
{ 
  int i, j, min;
   
  for (i = 0; i < N-1; i++)
    { 
      min = i;
      for (j = N-1; j > i; j--) 
        if (a[j] < a[min]) 
          min = j; 
      swap(&a[i], &a[min]);
    } 
  
}

