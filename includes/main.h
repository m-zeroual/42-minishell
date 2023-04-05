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

#define PWD  "pwd"
#define CD   "cd"
#define ENV  "env"
#define EXIT  "exit"


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


// ======> utils.c <=======
void free_split(char **str);
void ft_str_to_lower(char **path);
void ft_exe(t_shell *_shell);
int ft_get_index(char *str, char c);
int ft_get_index_reverse(char *str, char c);


#endif
