#include<iostream>
#include<iomanip>
#include <cstdlib> 
#include <time.h>
#include <math.h>
using namespace std;

#define Asize  10000

static int swapCount = 0;

void swap(int* a, int* b);
void insertionsort(int a[], int N);
void mergeSort(int a[], int a_tmp[], int l, int r);
void initialize_and_permute(int permutation[], int n);
int  uniform(int  m);

/* The problem is set to use insertion sort but you may try these
other O(N^2) local sorting methods if you wish
*/
void bubblesort(int a[], int N);
void selectionsort(int a[], int N);

int main()
{
  
  int a[Asize];
  int a_tmp[Asize];

for(int i = 0;i<Asize;i++)  a[i] = (rand() +1)%1000000  ;
   
 cout << Asize << "\n";
 for(int i = 0;i<Asize;i++)
     cout << a[i] << "\n";
 
 int Ncases = 10;
 for(int j = 0; j < Ncases; j++)
   {
  insertionsort(a, Asize);
  cout << "Case = " << j << "   swapCount " << swapCount << endl; 
   initialize_and_permute(a , Asize); 
  swapCount = 0;
   }
 
     //mergeSort(a,  a_tmp, 0, Asize-1);
  return 0;
}

void insertionsort(int a[],  int N)
  { 
    int i, j; 
    for (i = 1; i < N; i++)
      for (j = i; (j>0) && (a[j]< a[j-1]); j--)
        swap(&a[j],&a[j-1]);
  }

void mergeSort(int a[], int a_tmp[], int l, int r)
{
    int i, j, k, m;
   
    if (r > l)
      {
        m = (r+l)/2;
        mergeSort(a, a_tmp, l, m);  
        mergeSort(a,a_tmp, m+1, r);
        for (i = m+1; i > l; i--){
          a_tmp[i-1] = a[i-1];
        }
        for (j = m; j < r; j++){
          a_tmp[r+m-j] = a[j+1]; 
        }
        for (k = l; k <= r; k++){
          a[k] = (a_tmp[i] < a_tmp[j]) ? a_tmp[i++] : a_tmp[j--];       
        }
      }
  }


void swap(int* a, int* b)
{
    int temp;
    temp = *a; 
    *a = *b; 
    *b = temp; 
}

/* Returns a random integer 0 <= uniform(m) <= m-1 with uniform distribution */
int  uniform(int  m)
{
  return 0;
}  

/* See Knuth's shuffles https://en.wikipedia.org/wiki/Random_permutation */

void initialize_and_permute(int permutation[], int n)
{

}



void bubblesort(int a[], int N)
{
  int i, j;
  for (i = 0; i < N-1; i++)
    for (j = N-1; j > i; j--)
      if (a[j] < a[j-1]) 
     swap(&a[j], &a[j-1]);
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

