#include "malloc.h"


// Calculate the zone size for the given size
size_t zone_calc(size_t size) {
	int ps = getpagesize();

	if (size <= (unsigned long)(ps / ZONE_TINY_FACTOR)) {
		return (ps / ZONE_TINY_FACTOR);
	}
	if (size <= (unsigned long)(ps / ZONE_SMALL_FACTOR)) {
		return (ps / ZONE_SMALL_FACTOR);
	}
	return (size);
}

// version to save [size][allocatedmemory] with Preallocation to minize system calls and enhance performance
void *malloc(size_t size) {

	// TODO: check if there are existing zones, and they still have place for the size

	size_t zone_size = zone_calc(size);
	size_t *ptr = mmap(NULL, zone_size + sizeof(size_t), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED) {
		return (NULL);
	}
	(*ptr) = zone_size;
	return (void *)(ptr + 1);
}

// takes [size] and frees [allocatedmemory] with Preallocation to minize system calls and enhance performance
void free(void *ptr) {

	// TODO: implement zone freeing

	size_t *realptr = (size_t *)ptr - 1;
	printf("freeing %p with size %ld\n", realptr, *realptr);
	munmap(realptr, *realptr + sizeof(size_t));
}

