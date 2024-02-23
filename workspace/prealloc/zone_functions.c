#include "malloc.h"

// Calculate the zone size for the given size
size_t zone_size_calc(size_t size) {
	int ps = getpagesize();

	if (size <= (unsigned long)(ps / ZONE_TINY_FACTOR)) {
		return (ps / ZONE_TINY_FACTOR);
	}
	if (size <= (unsigned long)(ps / ZONE_SMALL_FACTOR)) {
		return (ps / ZONE_SMALL_FACTOR);
	}
	return (size);
}

/** 
    Takes in a requested memory size and returns a suitable zone from the storage.
    If there is not zone available it will extend the storage with a zone.
*/
t_zone* find_zone(t_storage* storage, size_t size) {
    
}

void* get_memory(t_zone* zone, size_t size) {
    
}
