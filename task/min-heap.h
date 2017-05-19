#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include "common.h"
typedef struct {
	size_t size, cur_size;
	accel_t *buffer;
} min_heap_t;


/**
* Initialize constant size binary heap (min-heap) with a given size (N).  
*/
int min_heap_init(min_heap_t *mheap, size_t size);

/**
* Reset memory allocation done by min-heap earlier
*/
void min_heap_reset(min_heap_t *mheap);

/**
* Insert an element into min-heap. 
* For heap sizes less than the max size, all the elements are inserted.
* After heap is full, add elements only if it is greater than current Min 
* of the min-heap. This way we store N elements in the heap which are maximum. 
* Complexity: O(logn)
*/
int min_heap_put(min_heap_t *mheap, accel_t data);

/**
* Removes top element from the min-heap. 
* As it is a min-heap, this removes a current minimum from the heap. 
* Complexit: O(logn)
*/
int min_heap_get(min_heap_t *mheap, accel_t *data);

/**
* Get current minimum from the heap. Does not modify the heap. 
* Complexity: O(1)
*/
int min_heap_min(min_heap_t *mheap, accel_t *data);


#endif