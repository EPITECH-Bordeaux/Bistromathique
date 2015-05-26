##
## Makefile for myutils in /home/poirie-n/blinux/poirie_n/repo/MyProjects/C_Lib_MyUtils
## 
## Made by Nathan Poirier
## Login   <poirie-n@epitech.net>
## 
## Started on  Wed Dec 10 13:08:35 2014 Nathan Poirier
## Last update Sun Feb 22 02:12:28 2015 Nathan Poirier
##

NAME	= libbtree.a

SRCS	= btree_exec.c		\
	  btree_get.c		\
	  btree_init.c		\
	  btree_move.c		\
	  btree_node_add.c	\
	  btree_reset.c

OBJS	= $(addprefix source/, $(SRCS:.c=.o))

CC	= gcc

CFLAGS	+= -O3
CFLAGS	+= -W -Wall -Wextra
CFLAGS	+= -Wno-unused-parameter -Wno-variadic-macros
CFLAGS	+= -ansi -pedantic
CFLAGS	+= -Iinclude/

LDFLAGS	=

RM	= rm -f

$(NAME):	$(OBJS)
	ar rc $(NAME) $(OBJS)

all:		$(NAME)

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re
