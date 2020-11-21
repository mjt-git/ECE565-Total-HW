#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

long num_elements;
long num_traversals;
int mode;   // 0 -> only write; 1 -> read:write = 1:1; 2 -> read:write = 2:1
uint32_t *array;

double calc_time(struct timespec start, struct timespec end) {
  double start_sec = (double)start.tv_sec*1000000000.0 + (double)start.tv_nsec;
  double end_sec = (double)end.tv_sec*1000000000.0 + (double)end.tv_nsec;

  if (end_sec < start_sec) {
    return 0;
  } else {
    return end_sec - start_sec;
  }
}

void init_array() {
	int i = 0;
	for(i = 0; i < num_elements; ++i) {
		array[i] = rand();
	}
}

int main(int argc, char *argv[]) {
	int i, j;
	struct timespec start_time, end_time;
	if(argc != 4) {
		printf("The usage should be \"./bandwith_test <num_elements> <num_traversals> <mode>\"");
	}
	if(mode != 0 && mode != 1 && mode != 2) {
		printf("mode should be 0 or 1 or 2");
	}
	// if(!(num_traversals == 10000000 || num_traversals == 100000000)) {
	// 	printf("num_traversals should be 10000000 or 100000000");	
	// }
	  num_elements = atoi(argv[1]);
  	num_traversals = atoi(argv[2]);
  	mode = atoi(argv[3]);

  	array = (uint32_t*)malloc(num_elements * sizeof(uint32_t));
  	if(mode == 2 || mode == 3) {
  		init_array();
  	}

  	if(mode == 0) {
  		clock_gettime(CLOCK_MONOTONIC, &start_time);
	  	for(i = 0; i < num_traversals; ++i) {
	  		for(j = 0; j < num_elements; j+=1) {
          array[j] = 500;   // just pick normal number
	  		}
	  	}
	  	clock_gettime(CLOCK_MONOTONIC, &end_time);
  	}
  	else if(mode == 1) {
  		int val1;
  		clock_gettime(CLOCK_MONOTONIC, &start_time);
	  	for(i = 0; i < num_traversals; ++i) {
	  		for(j = 0; j < num_elements-1; j+=1) {
          array[j] = 500;
	  			val1 = array[j+1];
	  		}
	  	}
	  	clock_gettime(CLOCK_MONOTONIC, &end_time);
  	}
  	else if(mode == 2) {
  		int val1, val2;
  		clock_gettime(CLOCK_MONOTONIC, &start_time);
	  	for(i = 0; i < num_traversals; ++i) {
	  		for(j = 0; j < num_elements-2; j+=1) {
          array[j] = 500;
	  			val1 = array[j+1];
	  			val2 = array[j+2];
	  		}
	  	}
	  	clock_gettime(CLOCK_MONOTONIC, &end_time);
  	}

  	double elapsed_ns = calc_time(start_time, end_time);
  	printf("Time=%f\n", elapsed_ns);
  	long access_count = 0;
    printf("num_traversals: %ld\n", num_traversals);
    printf("num_elements: %ld\n", num_elements);
  	switch(mode) {
  		case 0:
  			access_count = num_traversals * num_elements;
  			break;
  		case 1:
  			access_count = num_traversals * num_elements * 2;
  			break;
  		case 2:
  			access_count = num_traversals * num_elements * 3;
  			break;
  	}
  	printf("access_count: %ld\n", access_count);
  	printf("Bandwith = %fGB/s\n", (float)(access_count * 4 / pow(2, 30)) / (elapsed_ns / pow(10, 9)));

    free(array);

	return 0;
}