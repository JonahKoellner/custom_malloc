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

/** Function Definitions*/
void free(void *ptr);
void *malloc(size_t size);

#endif

