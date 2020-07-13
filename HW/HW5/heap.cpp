#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Utility function to create a new Min Heap Node 
MinHeapNode_t* newMinHeapNode(int v, int dist){
    // allocate memory
    MinHeapNode_t* minHeapNode = 
		(MinHeapNode_t*) malloc(sizeof(MinHeapNode_t));
    // populate heap graph node
	minHeapNode->v = v; 
	minHeapNode->dist = dist; 
	return minHeapNode;     
};

// A utility function to create a Min Heap 
MinHeap_t* createMinHeap(int capacity)
{ 
    // Allocate memory for priority queue
	MinHeap_t* minHeap = 
		(MinHeap_t*) malloc(sizeof(MinHeap_t)); 
    // Allocate memory for graph node position array
	minHeap->pos = (int *)malloc(capacity * sizeof(int)); 
	// initialize queue size
    minHeap->size = 0; 
    // include priority queue capacity
	minHeap->capacity = capacity; 
	minHeap->array = 
		(MinHeapNode_t**) malloc(capacity * sizeof(MinHeapNode_t*)); 
	return minHeap; 
}
// A utility function to swap two nodes of min heap. Needed for min heapify 
void swapMinHeapNode(MinHeapNode_t** a, MinHeapNode_t** b)
{ 
	MinHeapNode_t* temp = *a; 
	*a = *b; 
	*b = temp; 
};
// A standard function to heapify at given idx 
// This function also updates position of nodes when they are swapped. 
// Position is needed for decreaseKey() 
void minHeapify(MinHeap_t* minHeap, int idx)
{ 
    // Define util heap indexes 
	int smallest, left, right; 
	smallest = idx; 
	left = 2 * idx + 1; 
	right = 2 * idx + 2; 
    
	if (left < minHeap->size && 
		minHeap->array[left]->dist < minHeap->array[smallest]->dist ) 
	smallest = left; 

	if (right < minHeap->size && 
		minHeap->array[right]->dist < minHeap->array[smallest]->dist ) 
	smallest = right; 

	if (smallest != idx) 
	{ 
		// Define nodes to be swapped 
		MinHeapNode_t *smallestNode = minHeap->array[smallest]; 
		MinHeapNode_t *idxNode = minHeap->array[idx]; 

		// Swap positions indexes
		minHeap->pos[smallestNode->v] = idx; 
		minHeap->pos[idxNode->v] = smallest; 

		// Swap nodes 
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]); 
        // continue with other nodes in array
		minHeapify(minHeap, smallest); 
	} 
};
// Standard function to extract minimum node from heap 
MinHeapNode_t* dequeue(MinHeap_t* minHeap){ 
	// Check if priority queue is empty
    if (minHeap->size==0) 
		return NULL; 
	// Store the minimum heap node 
	MinHeapNode_t* root = minHeap->array[0]; 
	// Replace root node with last node 
	MinHeapNode_t* lastNode = minHeap->array[minHeap->size - 1]; 
	minHeap->array[0] = lastNode; 
	// Update position of last node 
	minHeap->pos[root->v] = minHeap->size-1; 
	minHeap->pos[lastNode->v] = 0; 
	// Update heap size and correct heap order
	--minHeap->size; 
	minHeapify(minHeap, 0); 
	return root; 
};
// Standard function to add node to priority queue 
MinHeapNode_t* enqueue(MinHeap_t* minHeap, int v, int dist)
{
    // populate values and increase heap size
    minHeap->array[v] = newMinHeapNode(v, dist); 
	minHeap->pos[v] = v;
    minHeap->size ++;
};
// Function to decreasy dist value of a given vertex v. This function 
// uses pos[] of min heap to get the current index of node in min heap 
void decreaseKey(MinHeap_t* minHeap, int v, int dist)
{ 
	// Get the index of v in heap array 
	int i = minHeap->pos[v]; 

	// Get the node and update its dist value 
	minHeap->array[i]->dist = dist; 

	// Travel up while the complete tree is not hepified. 
	// This is a O(Logn) loop 
	while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) 
	{ 
		// Swap this node with its parent 
		minHeap->pos[minHeap->array[i]->v] = (i-1)/2; 
		minHeap->pos[minHeap->array[(i-1)/2]->v] = i; 
		swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]); 
		// move to parent index 
		i = (i - 1) / 2; 
	} 
}; 
// A utility function to check if a given vertex 
// 'v' is in min heap or not 
bool isInMinHeap(MinHeap_t *minHeap, int v)
{ 
    if (minHeap->pos[v] < minHeap->size) 
        return true; 
    return false; 
};

