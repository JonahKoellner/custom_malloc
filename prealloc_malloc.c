#include <sys/mman.h> // mmap(), munmap()
#include <stddef.h> // size_t, NULL
#include <unistd.h> //getpagesize(),


#include <stdio.h> // remove after debugging


#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS 0x20 // cant find MAP_ANONYMOUS in sys/mman.h in this system
#endif

enum zone{ LARGE = 1, SMALL = 2, TINY = 3 };

// Calculate the zone size for the given size
size_t zone_calc(size_t size) {
	int ps = getpagesize();

	if (size <= (unsigned long)(ps / TINY)) {
		return (ps / TINY);
	}
	if (size <= (unsigned long)(ps / SMALL)) {
		return (ps / SMALL);
	}
	return (size);
}

// version to save [size][allocatedmemory] with Preallocation to minize system calls and enhance performance
void *malloc(size_t size) {

	// TODO: check if there are existing zones, and they still have place for the size

	size_t zone_size = zone_calc(size);
	size_t *ptr = mmap(NULL, zone_size + sizeof(size_t), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED) {
		return NULL;
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

int main(void) {
	/**
	 * Allocation Test
	*/
	void *ptr = malloc(10);
	void *ptr_mid = malloc(2000);
	void *ptr_large = malloc(2000000);

	if (ptr == NULL) {
		return (1);
	}
	printf("ptr = %p\n", ptr);

	/**
	 * Accessing allocated memory Test
	*/
	int i = 0;
	while (i < 12) {
		((char *)ptr)[i] = i + '0';
		i++;
	}
	i = 0;
	while (i < 15) {
		printf("%d\n", ((char *)ptr)[i]);
		i++;
	}

	/**
	 * Free Test
	*/
	free(ptr);
	free(ptr_mid);
	free(ptr_large);
	free(NULL); //NOop
	//free(ptr); // free error

	printf("%d\n", getpagesize());

	return (0);
}
