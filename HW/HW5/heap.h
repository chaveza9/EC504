#ifndef _HEAP_H
#define _HEAP_H

// Priority Queue Node 
// Structure to represent a min heap graph node 
typedef struct MinHeapNode 
{ 
	int v; 
	int dist; 
} MinHeapNode_t; 

// Structure to represent a min heap 
typedef struct MinHeap 
{ 
	int size;	 // Number of heap nodes present currently 
	int capacity; // Capacity of min heap 
	int *pos;	 // This is needed for decreaseKey() 
	MinHeapNode_t**array; 
}MinHeap_t; 
// Utility function to create a new Min Heap Node 
MinHeapNode_t* newMinHeapNode(int v, int dist);
// A utility function to create a Min Heap 
MinHeap_t* createMinHeap(int capacity);
// A utility function to swap two nodes of min heap. Needed for min heapify 
void swapMinHeapNode(MinHeapNode_t** a, MinHeapNode_t** b);
// A standard function to heapify at given idx 
// This function also updates position of nodes when they are swapped. 
// Position is needed for decreaseKey() 
void minHeapify(MinHeap_t* minHeap, int idx);
// Standard function to extract minimum node from heap 
MinHeapNode_t* dequeue(MinHeap_t* minHeap);
// Standard function to add node to priority queue 
MinHeapNode_t* enqueue(MinHeap_t* minHeap, int v, int dist);
// Function to decreasy dist value of a given vertex v. This function 
// uses pos[] of min heap to get the current index of node in min heap 
void decreaseKey(MinHeap_t* minHeap, int v, int dist); 
// A utility function to check if a given vertex 
// 'v' is in min heap or not 
bool isInMinHeap(MinHeap_t *minHeap, int v);


#endif /*_HEAP_H*/