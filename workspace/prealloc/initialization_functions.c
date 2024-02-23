#include "malloc.h"

/** 
    Initilizes a Storage pointer with 5 zones preallocated
*/
int init_storage(t_storage *storage) {
    storage = mmap(NULL, sizeof(t_storage) * 1, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (storage == NULL)
        return (1);
    storage->zones = mmap(NULL, sizeof(t_zone) * 5, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (storage->zones == NULL) {
        munmap(storage, sizeof(t_storage) * 1);
        return (1);
    }
    storage->capacity = 5;
    int counter = 0;
    while (counter < storage->capacity) {
        storage->zones[counter] = (t_zone){
            .biggest_space_available = 0,
            .allocs = NULL,
            .allocs_amount = 0,
            .memory = NULL,
            .total_size = 0,
            .ttl = -1,
        };
        counter++;
    }
    
    return (0);
}
