SRCS_PARSER	= parser.c				\
		  parser_token.c

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
		  $(addprefix parser/, $(SRCS_PARSER))	\
		  $(addprefix calc/, $(SRCS_CALC))	\
		  $(addprefix utils/, $(SRCS_UTILS))

OBJS		= $(addprefix src/, $(SRCS:.c=.o))

PROJECT		= Bistromathique_2.0

NAME		= Bistromathique

RM		= rm -f

CC		= gcc -g3 # WARNING -g3

LIBS		=

CFLAGS		= -W -Wall -Wextra -Werror
CFLAGS		+= -Wno-variadic-macros
CFLAGS		+= -Wno-unused-parameter
CFLAGS		+= -ansi -pedantic
CFLAGS		+= -std=c99 -D_BSD_SOURCE
CFLAGS		+= -Ofast
CFLAGS		+= -Iinclude
CFLAGS		+= $(LIBS)

LDFLAGS		+= $(LIBS)

$(PROJECT):	$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

all:		$(PROJECT)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: re fclean clean all $(PROJECT)
