SRCS		= main.c

OBJS		= $(addprefix source/, $(SRCS:c=.o))

PROJECT		= Bistromathique_2.0

NAME		= Bistromathique

RM		= rm -f

CC		= gcc

LIBS		= -Llib/lib_btree/ -lbtree

CFLAGS		= -W -Wall -Wextra -Werror
CFLAGS		+= -Wno-variadic-macros
CFLAGS		+= -Wno-unused-parameter
CFLAGS		+= -pedantic
CFLAGS		+= -Ofast
CFLAGS		+= -Iinclude -Ilib/lib_btree/include
CFLAGS		+= $(LIBS)

LDFLAGS		+= $(LIBS)

LIB_BTREE	= make -C lib/lib_btree/

$(PROJECT):	makelib $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

makelib:
		$(LIB_BTREE)

all:		$(PROJECT)

clean:
		$(RM) $(OBJS)

flcean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: re fclean clean all $(PROJECT)
