NAME	=	minishell

SRCS	=	src/main.c \
			src/errors/print_error.c \
			src/parsing_args/main_parsing.c \
			src/parsing_args/parsing_single_double_quotes/parsing_single_double_quotes.c \
			src/parsing_args/parsing_single_double_quotes/parsing_single_double_quotes_utils.c \
			src/parsing_args/parsing_redirection_and_pipes/parsing_pipes/parsing_pipes.c \
			src/parsing_args/parsing_redirection_and_pipes/parsing_pipes/parsing_pipes_utils.c \
			src/parsing_args/parsing_redirection_and_pipes/parsing_redirections/parsing_redirection.c \
			src/parsing_args/parsing_redirection_and_pipes/parsing_redirections/parsing_redirection_tools.c \
			src/parsing_args/parsing_redirection_and_pipes/parsing_redirections/parsing_redirection_utils.c \
			src/excution/ft_utils.c	\
			src/excution/ft_echo.c	\
			src/excution/ft_pwd.c	\
			src/excution/ft_cd.c	\
			src/excution/ft_export_1.c	\
			src/excution/ft_export_2.c	\
			src/excution/ft_export_3.c	\
			src/excution/ft_export.c	\
			src/excution/ft_command.c	\
			src/excution/ft_excute.c	\
			src/excution/ft_unset.c	\
			src/excution/ft_env.c \
			src/pipes/pipes.c \
			src/extra_functions.c

OBJS	=	$(SRCS:%.c=%.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address
RM		=	rm -f

all	:	$(NAME)

$(NAME)	:	$(OBJS)
	@make -C libft
	$(CC) $(CFLAGS)  $^ libft/libft.a -o $@ -lreadline

%.o		:	%.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean	:
	@make clean -C libft
	@$(RM) $(OBJS)

fclean	:	clean
	@make fclean -C libft
	@$(RM) $(NAME)

re		: fclean	all
