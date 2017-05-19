#ifndef CIRCULAR_BUF_H
#define CIRCULAR_BUF_H

#include "common.h"


typedef struct {
	size_t head, tail;
	size_t size, cur_size;
	accel_t *buffer;
} circular_buf_t;

/**
* Initialize a circular buffer with a given size (N).  
*/
int circular_buf_init(circular_buf_t *cbuf, size_t size);

/**
* Reset memory allocation done by circular buffer earlier
*/
void circular_buf_reset(circular_buf_t *cbuf);


/**
* Insert an element into circular buffer. 
* Heap pointer tracks the position of insert.
* Complexity: O(1)
*/
int circular_buf_put(circular_buf_t *cbuf, accel_t data);

/**
* Removes an element from circular buffer
* Tail pointer tracks position of removal.
* Complexit: O(1)
*/
int circular_buf_get(circular_buf_t *cbuf, accel_t *data);

/**
* Check if circular buffer is empty.
* Complexity: O(1)
*/
bool circular_buf_empty(circular_buf_t *cbuf);

#endif