#include "malloc.h"

void testfunction(void *ptr) {
	printf("%s\n", (char *)ptr);
}

int main(void) {
	/**
	 * Allocation Test
	*/
	void *ptr = malloc(10);
	void *ptr_mid = malloc(2000);
	void *ptr_large = malloc(2000000);

	if (ptr == (NULL)) {
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

	/**
	 * Linked list test
	*/

	t_list *list = ft_lstnew("Hello");
	ft_lstadd_back(&list, ft_lstnew("World"));
	ft_lstadd_back(&list, ft_lstnew("!!!"));

	ft_lstiter(list, testfunction);

	return (0);
}
