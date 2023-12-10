CC = gcc
CFLAGS = -Wall -Wextra -Werror
SOURCES = main.c network_init.c utils.c nodes_init.c
NAME = nn 

all:$(NAME)

$(NAME):$(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@

clear:
	rm -f nn