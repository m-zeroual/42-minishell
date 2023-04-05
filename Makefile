NAME	=	minishell

SRCS	=	src/main.c  src/utils.c

OBJS	=	$(SRCS:%.c=%.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror 
RM		=	rm -f

all	:	$(NAME)

$(NAME)	:	$(OBJS)
	@make -C ft_printf
	@make -C libft
	$(CC) $(CFLAGS) $^ libft/libft.a ft_printf/libftprintf.a -o $@ -lreadline


%.o		:	%.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean	:
	@make clean -C libft
	@make clean -C ft_printf
	@$(RM) $(OBJS)

fclean	:	clean
	@make fclean -C libft
	@make fclean -C ft_printf
	@$(RM) $(NAME)

re		: fclean	all
