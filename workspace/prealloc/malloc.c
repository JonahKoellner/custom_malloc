#include "malloc.h"

t_storage*	storage = NULL;

void*	malloc(size_t size) {
	if (size == 0) {
		return (NULL);
	}
	if (storage == NULL) {
		if (init_storage(storage))
		  return (NULL);
	}
	t_zone *zone = find_zone(storage, size);
	if (zone == NULL) {
		return (NULL);
	}
	return (get_memory(zone, size));
}

void free(void *ptr ){
    
}
