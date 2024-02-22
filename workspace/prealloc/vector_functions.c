#include "malloc.h"

/** 
    - This function is acting as a vector function for a vector.
    If vector is NULL the function will create an array with size.
    
    - If vector is NOT NULL the function will create a new array and copy all the fitting data from vector to the new one. It also frees the vector
    
    - Returns new t_alloc array OR NULL on error
*/
void* vector_extend(void* vector, size_t old_size, size_t new_size) {
    void* return_vector;
    
    return_vector = mmap(NULL, new_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (vector == NULL || return_vector == NULL)
        return (return_vector);
    
    memcpy(return_vector, vector, old_size);
    munmap(vector, old_size);
    return (return_vector);
}
