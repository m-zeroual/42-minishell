#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include "../ft_printf/ft_printf.h"
#include <stdio.h>
#include "parsing_single_double_quotes.h"
#include "parsing_redirection_and_pipes.h"
#include <readline/readline.h>
#include "execution.h"
#include "errors.h"
#include <fcntl.h>

int     **get_pipes(int size);
void    create_pipes(t_list    *pipes);
void    close_all_pipes(t_content *content);



// 
void    setup_all(t_shell *_shell);
char    **duplicate_dpointer(char **src);
void	del_content(void *cont);



char	*get_value(t_shell *shell, char **line, char separ, int *a);
char	*get_variable_name(char **line);

void	free_t_redirect_2(t_redirect *redirect);

#endif
