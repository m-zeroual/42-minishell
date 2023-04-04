#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include "../libft/libft.h"
#include "../ft_printf/ft_printf.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_shell
{
	int		ac;
	char 	**av;
	char 	**ev;
	char	*path;
	char 	**path_split;
	char	*cmd;
	char 	**cmd_split;
	
}	t_shell;

void ft_exe(t_shell *_shell);


#endif
