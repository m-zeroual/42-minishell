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
			src/execution/utils/ft_utils.c	\
			src/execution/echo/ft_echo.c	\
			src/execution/pwd/ft_pwd.c	\
			src/execution/cd/ft_cd.c	\
			src/execution/export/ft_export_1.c	\
			src/execution/export/display_export.c	\
			src/execution/export/ft_export.c	\
			src/execution/other_cmd/ft_command.c	\
			src/execution/other_cmd/ft_excute.c	\
			src/execution/unset/ft_unset.c	\
			src/execution/env/ft_env.c \
			src/execution/exit/ft_exit.c \
			src/pipes/pipes.c \
			src/extra_functions.c

OBJS	=	$(SRCS:%.c=%.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror #-fsanitize=address
RM		=	rm -f

all	:	$(NAME)

$(NAME)	:	$(OBJS)
	@make -C libft
	@make -C ft_printf
	$(CC) $(CFLAGS)  $^ libft/libft.a ft_printf/libftprintf.a -o $@ -lreadline

%.o		:	%.c
	@$(CC) $(CFLAGS) -c $^ -o $@
	

run		: all
	./minishell

clean	:
	@make clean -C libft
	@make clean -C ft_printf
	@$(RM) $(OBJS)

fclean	:	clean
	@make fclean -C libft
	@make fclean -C ft_printf
	@$(RM) $(NAME)

re		: fclean	all
