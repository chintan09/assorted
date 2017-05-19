#include "common.h"
#include "circular-buf.h"
#include "min-heap.h"

int process_input(FILE *fp, accel_t *data)
{
	int r = -1;

	static bool odd = true;
	static uint8_t last_nib;

	const int FREAD_SIZE = 1;

	size_t result;
	uint8_t tmp[2];

	do {
		accel_t accel_val = 0;
		result = fread(&tmp[0], FREAD_SIZE, 1, fp); 
		if (result != FREAD_SIZE) {
			break;
		}

		if (odd) {
			result = fread(&tmp[1], FREAD_SIZE, 1, fp); 
			if (result != FREAD_SIZE) {
				break;
			} 
			accel_val = (tmp[0] << 4) + (tmp[1] >> 4);
			last_nib = tmp[1] & 0xf;
		} else {
			accel_val = (last_nib << 8) + tmp[0];
		}

		odd = !odd;
		*data = accel_val;
		r = 0;

	} while (0);

	return r;
}


int main(const int argc, const char* argv[])
{
	if (argc != 3) {
		printf("Incorrect arguments \n");
		return -1;
	}

	FILE *input, *output;
	circular_buf_t cbuf;
	min_heap_t mheap;

	circular_buf_init(&cbuf, WINDOW_SIZE);
	min_heap_init(&mheap, WINDOW_SIZE);

	input = fopen(argv[1], "r");
	output = fopen(argv[2], "w+");

	if (!input || !output) {
		printf("Failed to open files \n");
		return -1;
	}

	int ret;
	accel_t accel_val; 

	while ((ret = process_input(input, &accel_val)) != -1) {
		circular_buf_put(&cbuf, accel_val);
		min_heap_put(&mheap, accel_val);
	}

	fprintf(output, "--Sorted Max %d Values--\n", WINDOW_SIZE);
	while ((ret = min_heap_get(&mheap, &accel_val)) != -1) {
		fprintf(output, "%d\n", accel_val);
	}
	
	fprintf(output, "--Last %d Values--\n", WINDOW_SIZE);
	while ((ret = circular_buf_get(&cbuf, &accel_val)) != -1) {
		fprintf(output, "%d\n", accel_val);

	}

	/* Close fd & clear buffers */
	circular_buf_reset(&cbuf);
	min_heap_reset(&mheap);

	fclose(input);
	fclose(output);

	return 0;
}
