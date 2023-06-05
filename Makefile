NAME	=	minishell

SRCS	=	src/main.c \
			src/builtins/minishell.c \
			src/errors/print_error.c \
			src/parsing_args/main_parsing.c \
			src/parsing_args/expanding_variables/expanding.c \
			src/parsing_args/expanding_variables/expanding_utils.c \
			src/parsing_args/parsing_single_double_quotes/checking.c \
			src/parsing_args/parsing_single_double_quotes/parsing_single_double_quotes.c \
			src/parsing_args/parsing_single_double_quotes/parsing_single_double_quotes_tools.c \
			src/parsing_args/parsing_single_double_quotes/parsing_single_double_quotes_utils.c \
			src/parsing_args/parsing_redirection_and_pipes/parsing_pipes/parsing_pipes.c \
			src/parsing_args/parsing_redirection_and_pipes/parsing_pipes/parsing_pipes_utils.c \
			src/parsing_args/parsing_redirection_and_pipes/parsing_redirections/parsing_redirection.c \
			src/parsing_args/parsing_redirection_and_pipes/parsing_redirections/parsing_redirection_tools.c \
			src/parsing_args/parsing_redirection_and_pipes/parsing_redirections/parsing_redirection_utils.c \
			src/builtins/utils/ft_utils.c	\
			src/builtins/echo/ft_echo.c	\
			src/builtins/pwd/ft_pwd.c	\
			src/builtins/cd/ft_cd.c	\
			src/builtins/export/ft_export_1.c	\
			src/builtins/export/display_export.c	\
			src/builtins/export/ft_export.c	\
			src/builtins/other_cmd/ft_command.c	\
			src/builtins/other_cmd/ft_exe_command.c	\
			src/builtins/other_cmd/ft_execute.c	\
			src/builtins/unset/ft_unset.c	\
			src/builtins/env/ft_env.c \
			src/builtins/exit/ft_exit.c \
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
