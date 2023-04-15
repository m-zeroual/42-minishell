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
#define EN  "env"
#define EX  "export"
#define UNS  "unset"
#define EXIT  "exit"


#define EXP 1
#define ENV 2





typedef struct s_shell
{
	int		ac;
	char 	**av;
	char 	**ev;
	char 	**export;
	char 	**env;
	char	*cmd;
	char	*first_part_cmd_l;
	char	*second_part;
	char 	**cmd_split;
	char	**path;

	
}	t_shell;


//		======> ft_utils.c <=======
void	free_split(char **str);
char	*ft_str_tolower(char *cmd);
void	ft_exe(t_shell *_shell);
// int ft_get_index(char *str, char c);
int		ft_get_index_reverse(char *str, char c, int count);


// 		======> ft_pwd.c <=======
char	*curr_path(t_shell _shell);
void	ft_exe_pwd(t_shell _shell);
void	ch_pwd(t_shell *_shell);


// 		======> env.c <=======
void	ft_exe_env(t_shell _shell);


// 		======> ft_cd.c <=======
void	ft_exe_cd(t_shell _shell);
// void	cd_home(t_shell *_shell);         *
// void cd_root(t_shell *_shell);
// void cd_2dots(t_shell *_shell);
// void cd_path(t_shell *_shell);         *


//		======> ft_export.c <=======
long ft_abs(long num);
int ft_count_env(char **env);
char **ft_fill_env(char **env, int lines);



void	ft_exe_export(t_shell *_shell);
int 	ft_add_var(t_shell *_shell);
int		check_var_error(char *var);
int		ft_check_var_exist(char **env, char *var);
int		ft_edit_var(t_shell *_shell, char *var, char *value);
void	fill_env(t_shell *_shell, char *var, char *value);
char	*ft_getenv(char **env, char *var);


#endif
