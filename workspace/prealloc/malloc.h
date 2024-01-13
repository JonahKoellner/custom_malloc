#ifndef MALLOC_H
#define MALLOC_H

/** Includes */
#include <sys/mman.h> // mmap(), munmap()
#include <stddef.h> // size_t, NULL
#include <unistd.h> //getpagesize(),
#include <stdio.h> // TODO: remove after debugging
#include "linked_list/linked_list.h" // t_list

/** Macro Defines */
#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS 0x20 // cant find MAP_ANONYMOUS in sys/mman.h in this system
#endif

#define ZONE_SMALL_FACTOR 2
#define ZONE_TINY_FACTOR 16

/** Function Definitions */
void free(void *ptr);
void *malloc(size_t size);

/**
/** Structs **\/
typedef struct s_zone {
	void *ptr;
	size_t size;
	t_block *block;
} t_zone;

typedef struct s_block {
	void *ptr;
	size_t size;
	struct s_block *next;
} t_block;
*/

typedef struct s_linkStorage {
	void *ptr;
	size_t size;
	struct s_linkStorage *next;
	struct s_linkStorage *blocks; //will be NULL when its a block (doing it like this saves allocation by 1 when creating a zone or block)
} t_linkStorage;

#endif

