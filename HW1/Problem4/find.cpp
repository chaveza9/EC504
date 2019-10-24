#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
using namespace std;

/***********************************************************
Main progam template for find by bisecton and dictonaruy
************************************************************/

static int OpCount = 0;

int findBisection(int key, int *a, int n);
int findDictionary(int key, int *a, int n);

int main(int argc, char *argv[]) 
{
  /* Timeing and IO setup */
  chrono::time_point<chrono::steady_clock> start, stop; 
  chrono::duration<double> difference_in_time;
  double difference_in_seconds_bisection; // Holds the final run time
  double difference_in_seconds_dictionary; // Holds the final run time
  ifstream infile;
  
  /* Local data */
  int n;
  int k;
  int key;
  int find_index_dictionary = -1;
  int find_index_bisection = -1;
  int NoOfKeys = 100;
  int *keytable = new int[NoOfKeys];
  
  // Input Data:  DO NOT CHANGE 
  infile.open(argv[1]);
  //infile.open(strcat(argv[1],".txt"));
  if(!infile){
    cout << "Error opening file " <<endl;
    return -1;
  }
  
  infile >> n;
  int *A = new int[n];

  for(int i=0; i<n ; i++)
    infile >> A[i];
  infile.close();

  // Define out put file 
   ofstream outfile(strcat(argv[1],"_out"));
  
  /* Select Set of Keys */
  for( k = 0; k < NoOfKeys; k++)
    {
      keytable[k] = A[rand()%n];
    }



  for( k = 0; k < NoOfKeys; k++)
    {
      key = keytable[k];
      
  /* Find Key by Bisection  Search  */
  OpCount = 0;
  start = chrono::steady_clock::now();
  find_index_bisection = findBisection(key, A,  n);
  cout << "Bisection Method Started" << endl;
  stop = chrono::steady_clock::now();
  difference_in_time = stop - start;
  difference_in_seconds_bisection = double(difference_in_time.count());
  int  OpCountBisection =  OpCount; 
  
  /* Find Key by Dictionary Search  */
  OpCount = 0;
  start = chrono::steady_clock::now();
  find_index_dictionary = findDictionary(key, A, n);
  stop = chrono::steady_clock::now();
  difference_in_time = stop - start;
  difference_in_seconds_dictionary = double(difference_in_time.count());
  int  OpCountDictionary =  OpCount; 
  
  
  /* Check against Key by Bisection  */
  cout << "Bisection " << find_index_bisection << " vs Dictionary " <<  find_index_dictionary << endl;
  if(find_index_dictionary !=-1)
    {
      cout << A[find_index_dictionary] << " found key = " <<  key<< endl;
    }
  cout << "Bisection:  " <<  difference_in_seconds_bisection << " count "  << OpCountBisection <<  endl;
  cout << "Dictionary: " << difference_in_seconds_dictionary  << " count "  << OpCountDictionary << endl;

  // Begin output file : DO NOT CHANGE
  outfile << key <<"          " << difference_in_seconds_bisection <<"        "<<  OpCountBisection;
  outfile <<"        " << difference_in_seconds_dictionary <<"       "<<  OpCountDictionary << endl;
  
  //End output file
    } // end of loop over keys
  return 0;
}

/****************************************
Provide funtions below
****************************************/

int findBisection(int key, int *a, int N)
{
  // Initialize index
  int index = -1; //Element is not present in the list
  // Initialize indexes
  int left = 0, right = N-1; 
  int m;
  // look within array iteratively
  while (left <= right && key>=a[left] && key<=a[right])
  {
    // Bisect the array (divide by 2)
    m = (left+right)/2;
    // Compare array against key
    if (a[m]==key){            // Value has been found at index m
      index = m;
      break;
      }              
    else if(a[m]<key){         // Value is on the right array
      left = m+1;}
    else {                     // Value is on the left array
      right = m-1;}
    // count number of iterations
    OpCount++;
  } 
  return index;
}

int findDictionary(int key, int *a, int N)
{
  // Initialize index
  int index = -1; // Element is not present in the list
  // Initialize indexes
  int left = 0, right = N-1; 
  // Define pivot variables
  int m; 
  double x;
  // look within array iteratively
  while (left <= right && key>=a[left] && key<=a[right])
  {
    // Compute fraction change from uniform distribution
    x = double(key-a[left])/(double(a[right])-a[left]);
    // Estimate new index
    m = int(left+x*(right-left));
    // Compare array against key
    if (a[m]==key){           // Value has been found at index m
      index = m;
      return m;
    }
    else if(a[m]<key)        // Value is on the right array
      left = m+1;
    else                     // Value is on the left array
      right = m-1;
    // count number of iterations
    OpCount++;
  } 
  return index;
}

