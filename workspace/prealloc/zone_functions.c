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
    Checks the TTL (Time To Live) of a zone. If the ttl is set it takes one away. If the ttl expired it removes the memory and sets the zone to {0}; If ttl == -1 it doesnt do anything
*/
int check_ttl(t_zone* zone) {
    zone->ttl -= ((zone->ttl == -1) ? 0 : 1);
    if (zone->ttl == 0) {
        if (munmap(zone->memory, zone->total_size))
            return (1);
        return (memset_s(zone, sizeof(t_zone), 0, sizeof(t_zone)));
    }
    return (0);
}

/** 
    Takes in a requested memory size and returns a suitable zone from the storage.
    If there is not zone available it will extend the storage with a zone.
*/
t_zone* find_zone(t_storage* storage, size_t size) {
    int counter = 0;
    t_zone zeroZone = {0};
    size_t zone_size = zone_size_calc(size);
     
    while (counter < storage->capacity) {
        if (memcmp(&storage->zones[counter], &zeroZone, sizeof(t_zone)) == 0) {
            storage->zones[counter] = (t_zone){
                .allocs = NULL,
                .allocs_amount = 0,
                .biggest_space_available = zone_size,
                .total_size = zone_size,
                .ttl = -1,
                .memory = mmap(NULL, zone_size,  PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)
            };
            if (storage->zones[counter].memory == NULL)
                return (NULL);
            return (&storage->zones[counter]);
        }
        if (storage->zones[counter].biggest_space_available >= size) {
            return (&storage->zones[counter]);
        }
        if (check_ttl(&storage->zones[counter]))
            return (NULL);
        counter++;
    }
    storage = vector_extend(storage, storage->capacity, storage->capacity + PREALLOC_AMOUNT);
    if (storage == NULL)
        return (NULL);
    storage->zones[counter] = (t_zone){
        .allocs = NULL,
        .allocs_amount = 0,
        .biggest_space_available = zone_size,
        .total_size = zone_size,
        .ttl = -1,
        .memory = mmap(NULL, zone_size,  PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)
    };
    if (storage->zones[counter].memory == NULL)
        return (NULL);
    return (&storage->zones[counter]);
}

void* get_memory(t_zone* zone, size_t size) {
    
    // make arrangements for storing
    // store 
}
