#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include "parsing_single_double_quotes.h"
#include "parsing_redirection_and_pipes.h"
#include <readline/readline.h>
#include "execution.h"
#include "errors.h"
#include <fcntl.h>

int **get_pipes(int size);
int **create_pipes(int size);
void    close_all_pipes(int **pipes, int size);

#endif
