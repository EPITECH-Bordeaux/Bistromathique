SRCS_PARSER	= parser.c				\
		  parser_btree.c			\
		  parser_type.c

SRCS_CALC	= calc_add.c				\
		  calc_sub.c				\
		  calc_mul.c				\
		  calc_div.c				\
		  calc_mod.c

SRCS_UTILS	= xalloc.c				\
		  print_error.c

SRCS		= main.c				\
		  init.c				\
		  base.c				\
		  options.c				\
		  reader.c				\
		  display.c				\
		  $(addprefix parser/, $(SRCS_PARSER))	\
		  $(addprefix calc/, $(SRCS_CALC))	\
		  $(addprefix utils/, $(SRCS_UTILS))

OBJS		= $(addprefix src/, $(SRCS:.c=.o))

PROJECT		= Bistromathique_2.0

NAME		= Bistromathique

RM		= rm -f

CC		= gcc

LIBS		= -Llib/lib_btree/ -lbtree

CFLAGS		= -W -Wall -Wextra -Werror
CFLAGS		+= -Wno-variadic-macros
CFLAGS		+= -Wno-unused-parameter
CFLAGS		+= -ansi -pedantic
CFLAGS		+= -std=c99 -D_DEFAULT_SOURCE
CFLAGS		+= -Ofast
CFLAGS		+= -Iinclude -Ilib/lib_btree/include
CFLAGS		+= $(LIBS)

LDFLAGS		+= $(LIBS)

LBTREE_NAME	= lib/lib_btree/libbtree.a
LBTREE_MAKE	= make -C lib/lib_btree/

$(PROJECT):	$(LBTREE_NAME) $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

$(LBTREE_NAME):
		$(LBTREE_MAKE)

all:		$(PROJECT)

clean:
		$(RM) $(OBJS)
		$(LBTREE_MAKE) clean

fclean:		clean
		$(RM) $(NAME)
		$(LBTREE_MAKE) fclean

re:		fclean all

.PHONY: re fclean clean all $(PROJECT)
