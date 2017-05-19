
#include "min-heap.h"

#define LCHILD(x) ((2 * (x)) + 1)
#define RCHILD(x) ((2 * (x)) + 2)
#define PARENT(x) (((x) - 1) / 2)


static inline void swap(accel_t *n1, accel_t *n2) 
{
    accel_t temp = *n1 ;
    *n1 = *n2 ;
    *n2 = temp ;
}


static void heapify(min_heap_t *mheap, int i)
{
    int smallest = (LCHILD(i) < mheap->cur_size && 
		mheap->buffer[LCHILD(i)] < mheap->buffer[i]) ? LCHILD(i) : i ;

    if(RCHILD(i) < mheap->cur_size && 
		mheap->buffer[RCHILD(i)] < mheap->buffer[smallest]) {
        smallest = RCHILD(i) ;
    }
    if(smallest != i) {
        swap(&(mheap->buffer[i]), &(mheap->buffer[smallest])) ;
        heapify(mheap, smallest) ;
    }	
}


int min_heap_init(min_heap_t *mheap, size_t size)
{
	int r = -1;
	if (mheap) {
		mheap->size = size;
		mheap->cur_size = 0;
		mheap->buffer = malloc(sizeof(accel_t)*size);

		if (!mheap->buffer) return r;
		
		r = 0;
	}
	return r;
}

void min_heap_reset(min_heap_t *mheap)
{
	if (mheap) {
		mheap->size = 0;
		mheap->cur_size = 0;
		free(mheap->buffer);
	}
}

int min_heap_put(min_heap_t *mheap, accel_t data)
{
	int r = -1;
	
	if (mheap->cur_size < mheap->size) {
		mheap->buffer[mheap->cur_size++] = data;
		
	    for(int i = (mheap->cur_size) / 2; i >= 0; i--) {
	        heapify(mheap, i) ;
	    }

	} else if (mheap->cur_size == mheap->size) {
		accel_t cur_min = 0;
		min_heap_min(mheap, &cur_min);
		if (data > cur_min) {
			mheap->buffer[0] = data;
			heapify(mheap, 0);
		}
	}

	return r;
}

int min_heap_get(min_heap_t *mheap, accel_t *data)
{
	int r = -1;
	if (mheap && data && mheap->cur_size) {
		*data = mheap->buffer[0];

		swap(&mheap->buffer[0], &mheap->buffer[mheap->cur_size-1]);
		mheap->cur_size--;

		heapify(mheap, 0);

		r = 0;
	}
	return r;
}

int min_heap_min(min_heap_t *mheap, accel_t *data)
{
	int r = -1;
	if (mheap && data && mheap->cur_size) {
		*data = mheap->buffer[0];
		r = 0;
	}
	return r;
}
