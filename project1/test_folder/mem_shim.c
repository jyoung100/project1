#define _GNU_SOURCE
#include <stddef.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define max_allocations 10000

void *(*original_malloc) (size_t size) = NULL;
void *(*original_calloc) (size_t, size_t) = NULL;
void (*original_free) (void* ptr);
void *(*original_realloc) (void* ptr, size_t size) = NULL;

typedef struct{
	void *ptr;
	size_t size;
} allocations;

int extra = 0;
int leakcount = 0;
int bytes = 0;
int resolving = 0;

allocations table[max_allocations];

int insert(void *p, size_t size){
	for(int i = 0; i < max_allocations; i++){
		if(table[i].ptr == p) {
			size_t prev_size = table[i].size;
			table[i].size = size;
			if(size >= prev_size){bytes+=(size-prev_size);}
			else{bytes-=(prev_size - size);}
			return 1;
		}
	}

	for(int i = 0; i < max_allocations; i++){
		if(table[i].ptr == NULL){
			table[i].ptr = p; 
			table[i].size = size;  
			bytes+= size;
			return 1;}
	}
	return 0;
}

int delete(void *p){
for(int i = 0; i < max_allocations; i++){
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


void __attribute__((destructor)) library_cleanup() {
	
	for(int j = 0; j < max_allocations; j++){
		if(table[j].ptr != NULL){
			dprintf(STDERR_FILENO, "Leak\t%zu\n", table[j].size);
		}
	}
	dprintf(STDERR_FILENO, "Total %zu\t%zu\n", (size_t)leakcount, (size_t)bytes);
}

void *malloc(size_t size){
	if(!original_malloc){
		if(resolving)
			return NULL;
		resolving = 1;
		original_malloc = dlsym(RTLD_NEXT , "malloc");
		resolving = 0;
		if(!original_malloc)
			return NULL;
	}
	++leakcount;
	void* ptr = original_malloc(size);
	insert(ptr, size);
	return ptr;
}

void *calloc(size_t count, size_t size){
	original_calloc = dlsym(RTLD_NEXT, "calloc");
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
	//original_realloc = dlsym(RTLD_NEXT, "realloc");

	free(ptr);
	/*size_t old = 0;
	int check_early_allocation = -1;
	if(ptr){
		for(int i = 0; i < max_allocations; i++){
			if(table[i].ptr == ptr){
				check_early_allocation = i;
				old = table[i].size;
				break;
			}
			if(check_early_allocation != -1){
				delete(ptr);
			}
		}
	}*/
	void *new_ptr = malloc(size);
	//void *new_ptr = original_realloc(ptr, size);
	/*if(new_ptr){
	insert(new_ptr, size);
	leakcount++;
	}
	/*else{
		insert(ptr, old);
		leakcount++;
	}*/
	return new_ptr;
}




   


