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
#define EXP  "export"
#define UNS  "unset"
#define EXIT  "exit"


typedef struct s_shell
{
	int		ac;
	char 	**av;
	char 	**ev;
	char	*cmd;
	char	*first_part_cmd_l;
	char	*second_part;
	char 	**cmd_split;
	char	**path;

	
}	t_shell;


// ======> utils.c <=======
void free_split(char **str);
char *ft_str_tolower(char *cmd);
void ft_exe(t_shell *_shell);
int ft_get_index(char *str, char c);
int ft_get_index_reverse(char *str, char c, int count);


// ======> pwd.c <=======
char *curr_path(t_shell _shell);
void ft_exe_pwd(t_shell _shell);
void ch_pwd(t_shell *_shell);


// ======> env.c <=======
void ft_exe_env(t_shell _shell);


// ======> env.c <=======
void cd_home(t_shell *_shell);
// void cd_root(t_shell *_shell);
// void cd_2dots(t_shell *_shell);
void cd_path(t_shell *_shell);


char *ft_getenv(char **env, char *var);


#endif
