NAME	=	minishell

CFILES	=	main.c test.c

SRCS	=	src/$(CFILES)
OBJS	=	bin/$(CFILES:.c=.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
RM		=	rm -f

all	:	$(NAME)

$(NAME)	:	$(OBJS)
	@make -C ft_printf
	@make -C libft
	$(CC) $(CFLAGS) bin/$^ libft/libft.a ft_printf/libftprintf.a -o $@

bin/%.o		:	src/%.c
	@$(CC) $(CFLAGS) -c $^

clean	:
	@make -C libft clean
	@make -C ft_printf clean
	@$(RM) $(OBJS)

fclean	:	clean
	@make -C libft fclean
	@make -C ft_printf fclean
	@$(RM) $(NAME)

re		: fclean	all
