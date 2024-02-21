#include "malloc.h"

t_storage*	storage = NULL;

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

void*	malloc(size_t size) {
	if (size == 0) {
		return (NULL);
	}
	if (storage == NULL) {
		init_storage();
	}
	t_zone *zone = find_zone(size);
	if (zone == NULL) {
		return (NULL);
	}
	return (get_memory(zone, size));
}
