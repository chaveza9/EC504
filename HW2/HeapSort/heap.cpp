#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
using namespace std;


/***********************************************************
Main progam template build a Max Heap and Heap Sort in place
************************************************************/

static int OpCount = 0;

int localSize = 100;

void mergeSort(int *a, int *a_tmp, int l, int r);

void Heapify(int *Heap, int n);
void CheckHeapOrder(int *Heap,int n);
int  DeleteHeap(int index,int *Heap,int ntemp);
void InsertHeap(int value ,int *Heap, int ntemp);
void HeapSort(int *Heap, int n);
void swap(int* a, int* b);
 
int main(int argc, char *argv[]) 
{
  /* Timeing and IO setup */
  chrono::time_point<chrono::steady_clock> start, stop; 
  chrono::duration<double> difference_in_time;
  double difference_in_seconds_heap_sort;  // Holds the final run time
  ifstream infile;
  ofstream outfile;
  
  /* Local data */
  int n;
 
  
  // Input Data:  DO NOT CHANGE 
  infile.open(argv[1]);

  int* Heap = NULL;
  
  if(!infile)
    {
      cout << "No input files so put in Heap file of size = "<<  localSize  << endl;
      n = localSize;
      cout << "n  = " << n << endl;
      Heap = new int[n+1];
      Heap[0] = n;  // Set zero entry in in heap to n
      for(int i=1; i<n+1 ; i++)  Heap[i] = rand()%100000;
      // Define out put file
       outfile.open("SortedRandomList.dat");
    }
  else
    {
      infile >> n;
      Heap = new int[n+1];
      Heap[0] = n;  // Set zero entry in in heap to n	    
      for(int i=1; i<n+1 ; i++) infile >> Heap[i];
      infile.close();
      // Define out put file 
      outfile.open(strcat(argv[1],"_out"));
    }
  
  

   /* Set up Heat */
   
   Heapify(Heap, n);

   CheckHeapOrder(Heap,n);
   
     /* Practive delete and insert */
 
   int ntemp = n;
   int index = 0;
   int value = -1;

   /* 
 You might want to do a Merge Sort and compare to make sure you haven't lost anything and compare with the Merge Sort after Insert/Delete test!
 */
   
# if 1   
   // Try Deleting 5 
   for(int k = 0; k <5; k++)
     {
       index = rand()%ntemp + 1;
       cout <<"value to be deleted at index "<< index<< endl;
       cout <<"ntemp "<< ntemp<< endl;
       value = DeleteHeap(index,Heap,ntemp); // Also reHeapfies 
       Heap[ntemp] = value;
       ntemp--;
     }
   //Reinsert 5       
   for(int k = 0; k <5; k++)
     {
       value = Heap[ntemp +1];
       cout <<"value to be added  "<< value <<"at ntemp "<< ntemp<< endl;
       InsertHeap(value,Heap, ntemp); // Also reHeapfies
       ntemp++;
     }

     cout <<"heapify complete"<<endl;
      CheckHeapOrder(Heap,n); // Is it still a  Heap?
#endif
      
/* 
 Test and compare  efficiency of Heap Sort  relative to Merge Sort
 */
      
  int* a_tmp = new int[n+1];      
      
  OpCount = 0;
  start = chrono::steady_clock::now();
   //mergeSort(Heap, a_tmp,  1, n);
   // REPLACE WITH HEAP SORT //
   HeapSort(Heap, n);
  stop = chrono::steady_clock::now();
  difference_in_time = stop - start;
  difference_in_seconds_heap_sort = double(difference_in_time.count());
  
  //Begin output file : DO NOT CHANGE  
 
  outfile << Heap[0] << endl;
  for(int i=1; i< Heap[0]+1  ; i++)
    outfile << Heap[i] << endl;

  //End output file

  return 0;
}

void mergeSort(int *a, int *a_tmp, int l, int r)
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


/****************************************
Provide funtions below
****************************************/
 void Heapify(int *Heap, int n)
 {
   // Check if heap array is empty
  if(n ==0)
    return;

  for (int i = 1; i < n; i++)  
    { 
        // Detect if child is greater than parent  (Max-heap property)
        if (Heap[i] > Heap[(i - 1) / 2])  
        { 
            int j = i; 
            // swap child and parent until child is smaller 
            while (Heap[j] > Heap[(j - 1) / 2])  
            { 
                swap(Heap[j], Heap[(j - 1) / 2]); 
                j = (j - 1) / 2; 
            } 
        } 
    } 
 }

void  CheckHeapOrder(int *Heap,int n)
{
  // We can print the array Heap to check order
  for (int i = 0; i < n; i++)
      cout << Heap[i]<<" ";
  cout << "End of Array" << endl;
  
}

int  DeleteHeap(int index,int *Heap,int ntemp)
{
  int save = Heap[index];
  // Shift values from heap 
  for(int i = index; i < ntemp-1; i++)
    Heap[i]=Heap[i+1]; // copy elements and shift to the left
  // Heapify new array
  Heapify(Heap, ntemp);
  return  save;
}
void InsertHeap(int value ,int *Heap, int ntemp)
{
  // Insert Heap into the last index of array
  Heap[ntemp] = value;
  // Heapify new array
  Heapify(Heap, ntemp);
}
void HeapSort(int *Heap, int n)
{
  /* Place Heap array in max-heap order just to be sure
   that input is a heap*/
  Heapify (Heap, n);
  //Define looping variables
  int j, index;
  for (int i = n - 1; i > 0; i--) 
  { 
    swap(Heap[0], Heap[i]); 
    //restart looping variables
    j = 0;
    index = 0;
    while (index<i)
    {
      index = (2*j+1);
      // Left child is smaller than right child
      if(Heap[index]<Heap[index+1] && index < (i-1))
      {
      // move index to the right child  
        index ++;
      }
      // New Parent is smaller than the child
      if (Heap[j]<Heap[index] && index < i)
      {
      // Swap nodes
        swap(Heap[j], Heap[index]);
      }
      j = index;
    }  
  }
}
/* sources:
 - https://rosettacode.org/wiki/Sorting_algorithms/Heapsort
 - http://www.mathcs.emory.edu/~cheung/Courses/171/Syllabus/9-BinTree/heap-sort2.html
*/
void swap(int* a, int* b)
{
  // put in swapCount
    int temp;
    temp = *a; 
    *a = *b; 
    *b = temp; 
}