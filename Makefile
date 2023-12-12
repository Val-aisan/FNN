CC = gcc
CFLAGS = -Wall -Wextra -Werror
SOURCES = main.c network_init.c utils.c nodes_init.c forward.c
NAME = n 

all:$(NAME)

$(NAME):$(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@

clear:
	rm -f nn