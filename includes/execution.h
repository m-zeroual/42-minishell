#ifndef EXECUTION_H
#define EXECUTION_H

#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

#define ECHO  "echo"
#define PWD  "pwd"
#define CD   "cd"
#define EN  "env"
#define EX  "export"
#define UNSET  "unset"
#define EXIT  "exit"


#define EXP 1
#define ENV 2

typedef struct s_shell
{
	int		status;
	char 	**env;
	char	*command;
	char 	**cmd_split;
	t_list 	*pipes;
	// int     **pipes_fds;
	int		i;
}	t_shell;


// 		======> ft_echo.c.c <=======
void    ft_exe_echo(t_shell *_shell);


//		======> ft_utils.c <=======
void	free_split(char **str);
char	*ft_str_tolower(char *cmd);
// int		ft_exe(t_shell *_shell);
// int ft_get_index(char *str, char c);
int		ft_get_index_reverse(char *str, char c, int count);


// 		======> ft_pwd.c <=======
char	*curr_path(t_shell _shell);
void	ft_exe_pwd(t_shell *_shell);
void	ch_pwd(t_shell *_shell);


// 		======> env.c <=======
void	ft_exe_env(t_shell *_shell);


// 		======> ft_cd.c <=======
void	ft_exe_cd(t_shell *_shell);
// void	cd_home(t_shell *_shell);         *
// void cd_root(t_shell *_shell);
// void cd_2dots(t_shell *_shell);
// void cd_path(t_shell *_shell);         *


// 		======> ft_command.c <=======
void exec_path_cmd(t_shell *_shell);
void ft_exec_cmd(t_shell *_shell);





// 		======> ft_excute.c <=======
void ft_exe_command(t_shell *_shell);
char *ft_join_cmd(t_shell *_shell);
int ft_init(t_shell *_shell);
int	minishel(t_shell *_shell);

//		======> ft_export1.c <=======
int ft_getvar_and_value(char *command, char **env, char **var, char **value);
char *ft_getenv(char **env, char *var);
char *ft_getvar(char *str);
int	ft_check_var_exist(char **env, char *var);
int ft_var_error(t_shell _shell, char *var);

//		======> ft_export2.c <=======
int	edit_var(char **str, char *var, char *value, int equal);
char	**add_var(char **env, char *var, char *value, int equal);
char **ft_fill_env(char **env, int lines);
int ft_count_env(char **env);

//		======> ft_export.c <=======
int check_var_error(char *var);
void ft_display_export(char **exp);
int ft_add_var(t_shell *_shell);
void ft_exe_export(t_shell *_shell);


//		======> ft_unset.c <=======
void ft_exe_unset(t_shell *_shell);



#endif
