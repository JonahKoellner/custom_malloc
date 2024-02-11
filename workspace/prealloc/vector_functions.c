#include "malloc.h"

// Creates and returns a array of t_storage * size
t_storage *_create_storage_vector(size_t size) {
	t_storage *new_vector;

	new_vector = mmap(NULL, sizeof(t_storage), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	return (new_vector);
}

// Reallocates the given vector to the new size. If the allocation for the new vector fails the old vector will NOT be freed. On success it will be freed
t_storage *_realloc_storage_vector(t_storage *old_vector, size_t new_size) {
	t_storage *new_vector;

	new_vector = mmap(NULL, sizeof(t_storage), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (new_vector == MAP_FAILED) {
		return (NULL);
	}

	// copy the old vector to the new vector

	munmap(old_vector, sizeof(t_storage));
	return (new_vector);
}
