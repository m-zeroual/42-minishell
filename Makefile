NAME	=	minishell

SRCS	=	src/main.c 
			src/parsing_args/parsing_single_double_quotes/parsing_single_double_quotes.c \
			src/parsing_args/parsing_single_double_quotes/parsing_single_double_quotes_utils.c

OBJS	=	$(SRCS:%.c=%.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g #-fsanitize=address
RM		=	rm -f

all	:	$(NAME)

$(NAME)	:	$(OBJS)
	@make -C ft_printf
	@make -C libft
	$(CC) $(CFLAGS) $^ libft/libft.a ft_printf/libftprintf.a -lreadline -o $@

%.o		:	%.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean	:
	@make -C libft clean
	@make -C ft_printf clean
	@$(RM) $(OBJS)

fclean	:	clean
	@make -C libft fclean
	@make -C ft_printf fclean
	@$(RM) $(NAME)

re		: fclean	all
