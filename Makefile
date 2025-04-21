##
## EPITECH PROJECT, 2025
## wolf3d
## File description:
## Makefile
##

SRC =	$(wildcard src/*.c) \
		$(wildcard src/**/*.c)

OBJ = $(SRC:.c=.o)
NAME = wolf3d

CC = gcc
CFLAGS += -Wall -Wextra -Wpedantic -I./include
CSFML_FLAGS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(CSFML_FLAGS) -lm -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

coding-style:	fclean
	clear
	mango

.PHONY: all clean fclean re
