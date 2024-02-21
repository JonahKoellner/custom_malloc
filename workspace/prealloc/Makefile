AR := ar rcs
CFLAGS := -Wall -Werror -Wextra


ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

# LIBS
CFILES := malloc.c vector_functions.c
OFILES := $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	@$(AR) $(NAME) $(OFILES)
	@echo "Compiled!"

%.o : %.c
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm -f $(OFILES)
	@echo "Cleaned!"

fclean: clean
	@rm -f $(NAME)
	@rm -f ./tester
	@echo "FCleaned!"

re: fclean all

main: $(NAME)
	$(CC) $(CFLAGS) main.c -o tester $(NAME)
