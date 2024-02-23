#include "malloc.h"

/** 
    Initilizes a Storage pointer with 5 zones preallocated
*/
int init_storage(t_storage *storage) {
    storage = mmap(NULL, sizeof(t_storage) * 1, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (storage == NULL)
        return (1);
    storage->zones = mmap(NULL, sizeof(t_zone) * PREALLOC_AMOUNT, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (storage->zones == NULL) {
        munmap(storage, sizeof(t_storage) * 1);
        return (1);
    }
    storage->capacity = PREALLOC_AMOUNT;
    memset_s(storage->zones, sizeof(t_zone) * PREALLOC_AMOUNT, 0, sizeof(t_zone) * 5); // sets the entire zone to 0
    
    return (0);
}
