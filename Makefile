##
## EPITECH PROJECT, 2025
## wolf3d
## File description:
## Makefile
##

SRC =	$(wildcard src/*.c) \
		$(wildcard src/**/*.c) \
		$(wildcard src/**/***/*.c)

OBJ = $(patsubst src/%.c,objects/%.o,$(SRC))
NAME = wolf3d

CC = gcc
CFLAGS += -Wall -Wextra -Wpedantic -I./include
CSFML_FLAGS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio

ifeq ($(ENV), dev)
	CFLAGS	+=	-g3 -DENV_DEV
else
	CFLAGS	+=	-O2 -fno-builtin
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(CSFML_FLAGS) -lm -o $(NAME)

objects/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf objects

fclean: clean
	rm -f $(NAME)

re: fclean all

coding-style:	fclean
	clear
	mango

cs: fclean
	coding-style . > /dev/null
	cat coding-style-reports.log
	$(RM) coding-style-reports.log

.PHONY: all clean fclean re
