#include "malloc.h"

t_linkStorage *g_zones = NULL;

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

void *_createZone(size_t size) {
	t_linkStorage *newZone;

	newZone = mmap(NULL, sizeof(t_linkStorage), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (newZone == MAP_FAILED) {
		return (NULL);
	}
	if ((newZone->ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED) {
		munmap(newZone, sizeof(t_linkStorage)); // free created zone if there was a error
		return (NULL);
	}
	newZone->size = size;
	newZone->next = NULL;
	newZone->blocks = NULL;
	return (newZone);
}

void *_createBlock(size_t size, void *ptr) {
	t_linkStorage *newBlock;

	newBlock = mmap(NULL, sizeof(t_linkStorage), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (newBlock == MAP_FAILED) {
		return (NULL);
	}
	newBlock->size = size;
	newBlock->ptr = ptr;
	return (newBlock);
}

void _freeZone(t_linkStorage *zone) {
	munmap(zone->ptr, zone->size); // free created zone if there was a error
	munmap(zone, sizeof(t_linkStorage)); // free created zone if there was a error
}

// version to save [size][allocatedmemory] with Preallocation to minize system calls and enhance performance
void *malloc(size_t size) {

	// TODO: check if there are existing zones, and they still have place for the size

	// There are no available zones , create one
	size_t zone_size = zone_calc(size);
	if (g_zones == NULL) {
		// No zone / allocation before
		if ((g_zones = _createZone(zone_size)) == NULL) {
			return (NULL);
		}
		if ((g_zones->blocks = _createBlock(size, g_zones->ptr)) == NULL) { // since its a new zone we can be sure that the first block has the starting point on the beginning of the zone
			_freeZone(g_zones);
			return (NULL);
		}
	}

	// TODO: This is the "old" version. Remove or encorporate into the new version
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

