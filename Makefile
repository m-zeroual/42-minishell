NAME	=	minishell

SRCS	=	main.c
OBJS	=	$(SRCS:.c=.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
RM		=	rm -f

all	:	$(NAME)

$(NAME)	:	$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o		:	%.c
	$(CC) $(CFLAGS) -c $^

clean	:
	$(RM) $(OBJS)

fclean	:	clean
	$(RM) $(NAME)

re		: fclean	all
