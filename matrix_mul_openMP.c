#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#define SIZE 2048


static double a[SIZE][SIZE];
static double b[SIZE][SIZE];
static double c[SIZE][SIZE];


// Timers
double totalRunTime = 0;    // time of running the program
double startRunTime;
double endTime;
// Timing function
static double get_wall_seconds() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
	return seconds;
}


// When initializing the matrix
void init_matrix(void) {
	int i, j;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++) {
			a[i][j] = rand() % 10;
			b[i][j] = rand() % 10;
		}
}

// Here we parallelize the matrix multiplication
void matmul_seq() {
	int i, j, k;
#pragma omp parallel shared(a,b,c) private(i,j,k) num_threads(8)
{
#pragma omp for schedule (static)
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				c[i][j] = 0.0;
				for (k = 0; k < SIZE; k++)
					c[i][j] = c[i][j] + a[i][k] * b[k][j];
			}
		}
	}
}


// Print the matrices as before
void print_matrix(void) {
	int i, j;
	printf("Matrix A\n");
	// Printing matrix A
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			printf(" %7.2f", a[i][j]);
		}
		printf("\n");
	}
	printf("Matrix B\n");
	// Printing matrix B
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			printf(" %7.2f", b[i][j]);
		}
		printf("\n");
	}
	printf("Matrix C\n");
	// Printing matrix C
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			printf(" %7.2f", c[i][j]);
		}
		printf("\n");
	}
}


// Main method
int main(int argc, char **argv) {
	// initiate the matrices A and B
	init_matrix();
	// Multiply the matrices to get C
	matmul_seq();
	if(SIZE <= 16) {
		print_matrix();
	}
}



