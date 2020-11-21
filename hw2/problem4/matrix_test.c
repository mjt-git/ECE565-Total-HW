#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

long N = 1024;
double ** A;
double ** B;
double ** C;
int mode; // 0 -> I-J-K; 1 -> J-K-I; 2 -> I-K-J
struct timespec start_time, end_time;

double calc_time(struct timespec start, struct timespec end) {
  double start_sec = (double)start.tv_sec*1000000000.0 + (double)start.tv_nsec;
  double end_sec = (double)end.tv_sec*1000000000.0 + (double)end.tv_nsec;

  if (end_sec < start_sec) {
    return 0;
  } else {
    return end_sec - start_sec;
  }
}

void assign_val(double ** m) {
	int i, j;
	for(i = 0; i < N; ++i) {
		for(j = 0; j < N; ++j) {
			m[i][j] = (double)rand();
		}
	}
}

void init_matrix() {
	int i;
	A = (double**)malloc(N * sizeof(double*));
	B = (double**)malloc(N * sizeof(double*));
	C = (double**)malloc(N * sizeof(double*));

	for(i = 0; i < N; ++i) {
		A[i] = (double*)malloc(N * sizeof(double));
		B[i] = (double*)malloc(N * sizeof(double));
		C[i] = (double*)malloc(N * sizeof(double));
	}

	assign_val(A);
	assign_val(B);
}

void exec_ijk_tiling() {
	int i, j, k, ii, jj, kk;
	double sum;
	clock_gettime(CLOCK_MONOTONIC, &start_time);
	for (i=0; i<N; i+=64) {
	    for (j=0; j<N; j+=64) {
	    	for(ii = i; ii < i+64; ++ii) {
	    		for(jj = j; jj < j + 64; ++jj) {
	    			sum = 0;
			        for (k=0; k<N; k+=64) {
			        	for(kk = k; kk < k+64; ++kk) {
			        		sum += A[ii][kk] * B[k][jj];	
			        	}
			        }
			        C[ii][jj] = sum;
	    		}
	    	}
	        
		} 
	}
	clock_gettime(CLOCK_MONOTONIC, &end_time);
}

void exec_ijk() {
	int i, j, k;
	double sum;
	clock_gettime(CLOCK_MONOTONIC, &start_time);
	for (i=0; i<N; i++) {
	    for (j=0; j<N; j++) {
	        sum = 0;
	        for (k=0; k<N; k++) {
	            sum += A[i][k] * B[k][j];
	        }
	        C[i][j] = sum;
		} 
	}
	clock_gettime(CLOCK_MONOTONIC, &end_time);
}

void exec_jki() {
	int i, j, k;
	double tmp;
	clock_gettime(CLOCK_MONOTONIC, &start_time);
	for (j=0; j<N; j++) {
	    for (k=0; k<N; k++) {
	        tmp = B[k][j];
	        for (i=0; i<N; i++) {
	            C[i][j] += tmp * A[i][k];
			} 
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end_time);
}

void exec_ikj() {
	int i, j, k;
	double tmp;
	clock_gettime(CLOCK_MONOTONIC, &start_time);
	for (i=0; i<N; i++) {
	    for (k=0; k<N; k++) {
	        tmp = A[i][k];
	        for (j=0; j<N; j++) {
	            C[i][j] += tmp * B[k][j];
			} 
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end_time);
}

void print_matrix(double ** m) {
	int i, j;
	for(i = 0; i < N; ++i) {
		for(j = 0; j < N; ++j) {
			printf("%f ", m[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
	if(argc != 2) {
		printf("The usage should be \"./matrix_test <ijk or jki or ikj or ijk_tiling>\"\n");
		return 1;
	}
	if(strcmp(argv[1], "ijk") != 0 && strcmp(argv[1], "jki") != 0 && strcmp(argv[1], "ikj") != 0 && strcmp(argv[1], "ijk_tiling") != 0) {
		printf("should only input <ijk or jki or ikj or ijk_tiling>\n");
		return 1;
	}

	init_matrix();
	

	if(strcmp(argv[1], "ijk") == 0) {
		exec_ijk();
	} else if(strcmp(argv[1], "jki") == 0) {
		exec_jki();
	} else if(strcmp(argv[1], "ikj") == 0) {
		exec_ikj();
	} else {
		exec_ijk_tiling();
	}

	double elapsed_ns = calc_time(start_time, end_time);
	printf("Total Time = %f seconds\n", elapsed_ns / pow(10, 9));

	return 0;
}