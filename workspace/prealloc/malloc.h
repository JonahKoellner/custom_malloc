#ifndef MALLOC_H
#define MALLOC_H

/** Includes */
#include <sys/mman.h> // mmap(), munmap()
#include <stddef.h> // size_t, NULL
#include <unistd.h> //getpagesize(),
#include <stdio.h> // TODO: remove after debugging

/** Macro Defines */
#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS 0x20 // cant find MAP_ANONYMOUS in sys/mman.h in this system
#endif

#define ZONE_SMALL_FACTOR 2
#define ZONE_TINY_FACTOR 16

/** Function Definitions */
void free(void *ptr);
void *malloc(size_t size);

/** Vector Functions*/
t_storage *_create_storage_vector(size_t size);
t_storage *_realloc_storage_vector(t_storage *old_vector, size_t new_size);

typedef struct s_storage {
	void *ptr;
	size_t size;
	struct s_storage *next;
	struct s_storage *blocks; //will be NULL when its a block (doing it like this saves allocation by 1 when creating a zone or block)
} t_storage;

#endif

