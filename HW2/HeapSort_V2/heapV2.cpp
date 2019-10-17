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

void heapify(int arr[], int n, int i) ;
void CheckHeapOrder(int *Heap,int n);
int  DeleteHeap(int index,int *Heap,int ntemp);
void InsertHeap(int value ,int *Heap, int ntemp);
void HeapSort(int *arr, int n);
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
      CheckHeapOrder(Heap,n); // Is it still a  Heap?
#endif
      
/* 
 Test and compare  efficiency of Heap Sort  relative to Merge Sort
 */
      
  int* a_tmp = new int[n+1];      
      
  OpCount = 0;
  start = chrono::steady_clock::now();
   mergeSort(Heap, a_tmp,  1, n);
   // REPLACE WITH HEAP SORT //
   // HeapSort(Heap, n);
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

  void heapify(int arr[], int n, int i) 
{ 
    int largest = i; // Initialize largest as root 
    int l = 2*i + 1; // left = 2*i + 1 
    int r = 2*i + 2; // right = 2*i + 2 
  
    // If left child is larger than root 
    if (l < n && arr[l] > arr[largest]) 
        largest = l; 
  
    // If right child is larger than largest so far 
    if (r < n && arr[r] > arr[largest]) 
        largest = r; 
  
    // If largest is not root 
    if (largest != i) 
    { 
        swap(arr[i], arr[largest]); 
  
        // Recursively heapify the affected sub-tree 
        heapify(arr, n, largest); 
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

  return  save;
}
void InsertHeap(int value ,int *Heap, int ntemp)
{
 
}
void HeapSort(int *arr, int n)
{
// Build heap (rearrange array) 
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i); 
  
    // One by one extract an element from heap 
    for (int i=n-1; i>=0; i--) 
    { 
        // Move current root to end 
        swap(arr[0], arr[i]); 
  
        // call max heapify on the reduced heap 
        heapify(arr, i, 0); 
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