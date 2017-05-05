/* 
 * WHAT THIS EXAMPLE DOES
 * 
 * We create a pool of 4 threads and then add 40 tasks to the pool(20 task1 
 * functions and 20 task2 functions). task1 and task2 simply print which thread is running them.
 * 
 * As soon as we add the tasks to the pool, the threads will run them. It can happen that 
 * you see a single thread running all the tasks (highly unlikely). It is up the OS to
 * decide which thread will run what. So it is not an error of the thread pool but rather
 * a decision of the OS.
 * 
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "thpool.h"

#define TEST_DEPTH	4
#define TEST_W		1024
#define TEST_H		1024

int main(){
	struct timeval s_time, e_time;
	int *buf0 = (int*)calloc(TEST_DEPTH*TEST_W*TEST_H, sizeof(int));
	int *buf1 = (int*)calloc(TEST_DEPTH*TEST_W*TEST_H, sizeof(int));

	
	gettimeofday(&s_time, NULL);
	for(int pidx = 0; pidx < TEST_DEPTH; pidx++){
		int *plane = buf0 + pidx*TEST_W*TEST_H;
		for(int yidx = 0; yidx < TEST_H; yidx++){
			for(int xidx = 0; xidx < TEST_W; xidx++){
				plane[yidx*TEST_W + xidx] = pidx*4096 + (yidx + xidx);
			}
		}
	}
	gettimeofday(&e_time, NULL);
	printf("single thread - %ld us\n", (e_time.tv_sec - s_time.tv_sec)*1000000 + (e_time.tv_usec - s_time.tv_usec));

	puts("Making threadpool with 4 threads");
	threadpool thpool = thpool_init(4);

	gettimeofday(&s_time, NULL);
	for(int pidx = 0; pidx < TEST_DEPTH; pidx++){
		int *plane = buf1 + pidx*TEST_W*TEST_H;
		thpool_add_block(thpool, ^{
			for(int yidx = 0; yidx < TEST_H; yidx++){
				for(int xidx = 0; xidx < TEST_W; xidx++){
					plane[yidx*TEST_W + xidx] = pidx*4096 + (yidx + xidx);
				}
			}
		});
	}
	thpool_wait(thpool);
	gettimeofday(&e_time, NULL);
	printf("4 threads - %ld us\n", (e_time.tv_sec - s_time.tv_sec)*1000000 + (e_time.tv_usec - s_time.tv_usec));
	printf("result %d\n", memcmp(buf0, buf1, TEST_DEPTH*TEST_W*TEST_H*sizeof(int)));

	puts("Killing threadpool");
	thpool_destroy(thpool);
	
	free(buf0);
	free(buf1);
	return 0;
}
