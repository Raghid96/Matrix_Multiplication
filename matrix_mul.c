#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
// The size of the matrix
#define SIZE 2048

// The variables are visible for all methods therefore static
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


// initial the matrix
void init_mat(void) {
	int i, j;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++) {
			a[i][j] = rand() % 10;
			b[i][j] = rand() % 10;
		}
}

// MULTIPLY THE MATRICES A AND B
void matmul_seq() {
	int i, j, k;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			c[i][j] = 0.0;
			for (k = 0; k < SIZE; k++)
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
		}
	}
}


// Print the matrix
void print_matrix(void) {
	int i, j;
	printf("Matrix A\n");
	for (i = 0; i < SIZE; i++) {
		// Printing matrix A
		for (j = 0; j < SIZE; j++) {
			printf(" %7.2f", a[i][j]);
		}
		printf("\n");
	}
	printf("Matrix B\n");
	for (i = 0; i < SIZE; i++) {
		// Printing matrix B
		for (j = 0; j < SIZE; j++) {
			printf(" %7.2f", b[i][j]);
		}
		printf("\n");
	}
	printf("Matrix C\n");
	for (i = 0; i < SIZE; i++) {
		// Printing matrix C
		for (j = 0; j < SIZE; j++) {
			printf(" %7.2f", c[i][j]);
		}
		printf("\n");
	}
}





// MAIN METHOD
int main(int argc, char **argv) {
	FILE *f = fopen("seq_result.txt", "w");
	startRunTime = get_wall_seconds();
	// Initialte the matrices A and B that will be multiplied
	init_mat();
	// Multiply the matrices A and B
	matmul_seq();
	endTime = get_wall_seconds();
	totalRunTime = endTime - startRunTime;	
	printf("Total Run time::%f\n", totalRunTime);
	fprintf(f, "%d", totalRunTime);
	if(SIZE <= 16) {
		print_matrix();
	}

}








