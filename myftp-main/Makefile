##
## EPITECH PROJECT, 2022
## B-CPE-110-TLS-1-1-dante-nicolas.gouy
## File description:
## Dante Makefile
##

NAME = myftp

CC = gcc

SRC =	src/main.c \
		src/commande.c	\
		src/set_serveur.c	\
		src/other.c	\
		src/help.c	\

CFLAGS = -I include/ -g3

OBJ	= $(SRC:.c=.o)

all: $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all
