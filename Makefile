CC = gcc
CFLAGS = -Wall -Wextra -Werror
SOURCES = main.c network_init.c utils.c nodes_init.c compute_output.c \
		  ft_malloc.c matrix.c print_structure.c \
		  network_file_init.c grd_init.c matrix_op.c 
NAME = nn

all: $(NAME)

$(NAME): $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(NAME)
