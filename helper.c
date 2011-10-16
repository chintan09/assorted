/* Helper file - containing various functions */
#include <stdio.h>

int sum(int val)
{
	int i; 
	int sum;
	for (i=0; i<val; i++) {
		sum += i; 
	}

	return sum; 
}


/* Psudo code to multiply two matrix */

#define MAX_ROWS 2
#define MAX_COLS 2

void matrix_print(int mat[][MAX_ROWS])
{
	int i, j; 

	for (i=0; i < MAX_ROWS; i++) {
		for (j=0; j < MAX_ROWS; j++) {
			printf("Mat[%d][%d] : %d \n", i, j, mat[i][j]);
		}
	}
}
void matrix_mul()
{
	int i, j, k; 
	int sum; 

	int A[MAX_ROWS][MAX_COLS], B[MAX_COLS][MAX_ROWS];
	int C[MAX_ROWS][MAX_ROWS]; 

	/* Initialize the matrix  */
	for (i=0; i < MAX_ROWS; i++) {
		for (j=0; j < MAX_ROWS; j++) {
			A[i][j] = i*j+4; 
			B[j][i] = j+2; 
		}
	}

	printf("Print A \n");
	matrix_print(A);

	printf("Print B \n");
	matrix_print(B);

	for (i=0; i < MAX_ROWS; i++) {
		for (j=0; j < MAX_ROWS; j++) {
			sum = 0;
			for (k=0; k < MAX_COLS; k++) {
				sum += A[i][k] * B[k][j];
			}
			C[i][j] = sum; 
		}
	}

	printf("Print C (Result) \n");
	matrix_print(C);

}
