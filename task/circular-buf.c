
#include "circular-buf.h"

int circular_buf_init(circular_buf_t *cbuf, size_t size) 
{
	int r = -1;
	
	if (cbuf) {
		cbuf->size = size; 
		cbuf->buffer = malloc(sizeof(uint16_t) * size);
		if (!cbuf->buffer) {
			return r;
		}

		cbuf->head = 0;
		cbuf->tail = 0;
		cbuf->cur_size = 0;
		r = 0;
	}

	return r;
}


void circular_buf_reset(circular_buf_t *cbuf)
{
	cbuf->head = 0;
	cbuf->tail = 0;
	cbuf->cur_size = 0;
	if (cbuf->buffer) {
		free(cbuf->buffer);
	}
}

int circular_buf_put(circular_buf_t *cbuf, accel_t data)
{
    int r = -1;

    if(cbuf) {
        cbuf->buffer[cbuf->head] = data;

        if(!circular_buf_empty(cbuf) && cbuf->head == cbuf->tail) {
            cbuf->tail = (cbuf->tail + 1) % cbuf->size;
        }
        cbuf->head = (cbuf->head + 1) % cbuf->size;
		cbuf->cur_size++;
		cbuf->cur_size = MIN(cbuf->cur_size, cbuf->size);

        r = 0;
    }

    return r;
}

int circular_buf_get(circular_buf_t *cbuf, accel_t *data)
{
    int r = -1;

    if(cbuf && data && !circular_buf_empty(cbuf)) {
        *data = cbuf->buffer[cbuf->tail];
        cbuf->tail = (cbuf->tail + 1) % cbuf->size;
		cbuf->cur_size--;
		cbuf->cur_size = MAX(cbuf->cur_size, 0);

        r = 0;
    }

    return r;
}

bool circular_buf_empty(circular_buf_t *cbuf)
{
    return (cbuf->cur_size == 0);
}
