#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>

#define BIG 1000000000L  //1 billion

uint64_t sum = 0;
pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;

void add_up_to_big() {
	for (uint64_t i = 0; i < BIG; i++) {
		pthread_mutex_lock(&mylock);
		sum += i; //atomic
		pthread_mutex_unlock(&mylock);
		//read sum
		//read i
		//sum + i
		//write sum 
	}
}

void * mythreadfunc(void *arg) {
	add_up_to_big();
	
	return NULL;
}

int main(int argc, char **argv) {
	
	pthread_t t1, t2;

	pthread_create(&t1, NULL, mythreadfunc, NULL);
	pthread_create(&t2, NULL, mythreadfunc, NULL);
	//add_up_to_big();
	//add_up_to_big();


	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	printf("The result is %lu\n", sum);
	return 0;
}
