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
t_alloc* alloc_extend(t_alloc *vector, size_t *size); // if vector is NULL new vector is created; if vector has value it is extended
t_zone* zone_extend(t_zone *vector, size_t *size); // if vector is NULL new vector is created; if vector has value it is extended

/** Helper Function Zones */
t_zone *find_zone(size_t size); // finds a zone with enough space for size (if no zone found calls zone_extend and give back the first new zone)
void *get_memory(t_zone *zone, size_t size); // takes zone and gets part of zone_memory for user. If zone memory null it creates new zone_mem

typedef struct s_storage {
	t_zone*	zone;
	size_t	capacity;
}	t_storage;

typedef struct s_alloc {
	void*	start_address;
	size_t	size;
}	t_alloc;

typedef struct s_zone {
	t_alloc	*alloced;
	void	*memory;
	size_t	total_size;
	size_t	biggest_space_available;
}	t_zone;

#endif
