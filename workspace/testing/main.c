#include <sys/mman.h> // mmap(), munmap()
#include <stddef.h> // size_t, NULL
#include <unistd.h> //getpagesize(),
#include <stdio.h> // TODO: remove after debugging

#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS 0x20 // cant find MAP_ANONYMOUS in sys/mman.h in this system
#endif

typedef struct s_test {
    void *test;
    size_t other_test;
}   t_test;

int main(void) {
	void *ptr = mmap(NULL, 1, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	void *ptr2 = mmap(ptr, 1, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	void *ptr4 = mmap(NULL, 1, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	void *ptr3 = mmap(ptr2, 1, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	printf("%p\n", ptr);
	printf("%p\n", ptr2);
	printf("%p\n", ptr3);
	printf("%p\n", ptr4);
	t_test test = {.other_test = 2, .test=NULL};
	t_test test1 = {.other_test = 2, .test=NULL};
	t_test test2 = {.other_test = 2, .test=NULL};
	t_test old[] = {
	{.other_test = 2, .test=NULL},
	{.other_test = 2, .test=NULL},
	{.other_test = 2, .test=NULL},
	{.other_test = 2, .test=NULL},
	};
	t_test* map = mmap(NULL, 3 * sizeof(t_test) , PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	map[0] = test;
	map[1] = test1;
	map[2] = test2;
	printf("dynamic: %lu, mmap: %lu\n", sizeof(old) / sizeof(t_test), sizeof(map) / sizeof(t_test));
}
