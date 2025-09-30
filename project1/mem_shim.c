//Jack Young, CPSC 3220, Dr. Sorber
#define _GNU_SOURCE
#include <stddef.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

//Max Allocation number, magic number problem. If more than 10000 allocations, program fails
#define max_allocations 10000

//Function pointers to the original functions
void *(*original_malloc) (size_t size) = NULL;
void *(*original_calloc) (size_t, size_t) = NULL;
void (*original_free) (void* ptr);
void *(*original_realloc) (void* ptr, size_t size) = NULL;

//struct to hold information about each call
typedef struct{
	void *ptr;
	size_t size;
} allocations;

//Variables to keep track of leakcount, number of bytes. Resolving is basically a bool to prevent dlsym from recursing on itself
int leakcount = 0;
int bytes = 0;
int resolving = 0;

//array of struct allocations
allocations table[max_allocations];

//insert function to insert into allocations table
int insert(void *p, size_t size){
	//loop through table
	for(int i = 0; i < max_allocations; i++){
		//check for resizing with realloc
		if(table[i].ptr == p) {
			size_t prev_size = table[i].size;
			table[i].size = size;
			if(size >= prev_size){bytes+=(size-prev_size);}
			else{bytes-=(prev_size - size);}
			return 1;
		}
	}
	//inputting new allocations in the table
	for(int i = 0; i < max_allocations; i++){
		//check if NULL, input into table, add bytes to size
		if(table[i].ptr == NULL){
			table[i].ptr = p; 
			table[i].size = size;  
			bytes+= size;
			return 1;}
	}
	return 0;
}

//delete allocation from the array
int delete(void *p){
for(int i = 0; i < max_allocations; i++){
	//check pointer, set to NULL and 0, subtract bytes from total
	if(table[i].ptr == p){
		table[i].ptr = NULL;
		bytes-=table[i].size;
		table[i].size = 0;
		--leakcount;
		return 1;
	}
}
return 0;
}

//destructor, use dprintf so program doesnt lazy malloc for printf
void __attribute__((destructor)) library_cleanup() {
	
	for(int j = 0; j < max_allocations; j++){
		if(table[j].ptr != NULL){
			dprintf(STDERR_FILENO, "Leak\t%zu\n", table[j].size);
		}
	}
	dprintf(STDERR_FILENO, "TOTAL\t%zu\t%zu\n", (size_t)leakcount, (size_t)bytes);
}

void *malloc(size_t size){
	//If function isn't NULL and Resolving is set to 1, then it recursed, return NULL if so, set it to the next malloc call
	if(!original_malloc){
		if(resolving)
			return NULL;
		resolving = 1;
		original_malloc = dlsym(RTLD_NEXT , "malloc");
		resolving = 0;
		if(!original_malloc)
			return NULL;
	}
	//increment leakcount and insert into array
	++leakcount;
	void* ptr = original_malloc(size);
	insert(ptr, size);
	return ptr;
}

void *calloc(size_t count, size_t size){
	//get next calloc library function
	original_calloc = dlsym(RTLD_NEXT, "calloc");
	//increment leakcount and insert into array
	++leakcount;
	void* ptr = original_calloc(count, size);
	insert(ptr, size*count);
	return ptr;
}

void free(void *ptr){
   if(ptr == NULL){return;}
   original_free = dlsym(RTLD_NEXT, "free");
   delete(ptr);
   original_free(ptr);

   return;
   }

void *realloc(void *ptr, size_t size){
	free(ptr);
	void *new_ptr = malloc(size);
	return new_ptr;
}




   


