NAME	=	minishell

SRCS	=	src/main.c \
			src/parsing_args/parsing_single_double_quotes/parsing_single_double_quotes.c \
			src/parsing_args/parsing_single_double_quotes/parsing_single_double_quotes_utils.c \
			src/ft_utils.c	\
			src/ft_pwd.c	\
			src/ft_cd.c	\
			src/ft_export_1.c	\
			src/ft_export_2.c	\
			src/ft_export_3.c	\
			src/ft_export.c	\
			src/ft_command.c	\
			src/ft_excute.c	\
			src/ft_unset.c	\
			src/ft_env.c

OBJS	=	$(SRCS:%.c=%.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g #-fsanitize=address
RM		=	rm -f

all	:	$(NAME)

$(NAME)	:	$(OBJS)
	@make -C ft_printf
	@make -C libft
	$(CC) $(CFLAGS)  $^ libft/libft.a ft_printf/libftprintf.a -o $@ -lreadline # -fsanitize=address

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
