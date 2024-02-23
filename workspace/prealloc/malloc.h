#ifndef MALLOC_H
#define MALLOC_H

/** Includes */
#include <sys/mman.h> // mmap(), munmap()
#include <stddef.h> // size_t, NULL
#include <unistd.h> //getpagesize(),
#include <string.h> // memcpy
#include <stdio.h> // TODO: remove after debugging

/** Macro Defines */
#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS 0x20 // cant find MAP_ANONYMOUS in sys/mman.h when running on 42MacOs
#endif

#define ZONE_SMALL_FACTOR   2
#define ZONE_TINY_FACTOR    16
#define TTL_TIME            3

/** Structs */
typedef struct s_alloc {
	void*	start_address;
	size_t	size;
}	t_alloc;

typedef struct s_zone {
	t_alloc*   allocs;
	size_t     allocs_amount;
	void       *memory;
	size_t     total_size;
	size_t     biggest_space_available;
	int        ttl;
}	t_zone;

typedef struct s_storage {
    t_zone* zones;
	size_t	capacity;
}	t_storage;

/** Main Function Declarations */
void free(void *ptr);
void *malloc(size_t size);

/** Vector Function Declarations*/
void*   vector_extend(void* vector, size_t old_size, size_t new_size);

/** Zone Helper Function Declarations */
// Calculates the zone size for the given size
size_t zone_size_calc(size_t size);
// On any error returns NULL
t_zone *find_zone(t_storage* storage, size_t size); // finds a zone with enough space for size (if no zone found calls zone_extend and give back the first new zone)
void *get_memory(t_zone *zone, size_t size); // takes zone and gets part of zone_memory for user. If zone memory null it creates new zone_mem

/** Generell Functions */
int init_storage(t_storage* storage);

#endif
