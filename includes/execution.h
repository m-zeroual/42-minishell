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

#define ECHO  "echo\0"
#define PWD  "pwd\0"
#define CD   "cd\0"
#define EN  "env\0"
#define EX  "export\0"
#define UNSET  "unset\0"
#define EXIT  "exit\0"


#define EXP 1
#define ENV 2

typedef struct s_shell
{
	int		status;
	char 	**env;
	char	*command_with_path;
	t_list 	*pipes;
	int		i;
	int		a;
}	t_shell;

void	rl_replace_line(const char *str, int i);
// 		======> src/excution/echo/ft_echo.c.c <=======
void    ft_exe_echo(t_shell *_shell);


//		======> src/excution/utils/ft_utils.c <=======
void	free_split(char **str);
// char	*ft_str_tolower(char *cmd);                                       // change
// int		ft_exe(t_shell *_shell);
// int ft_get_index(char *str, char c);
int		ft_get_index_reverse(char *str, char c, int count);


// 		======> src/excution/pwd/ft_pwd.c <=======
char	*curr_path(t_shell _shell);
void	ft_exe_pwd(t_shell *_shell);
void	ch_pwd(t_shell *_shell);


// 		======> src/excution/env/env.c <=======
char	**ft_fill_env(char **env, int lines);
int		ft_count_env(char **env);
void	ft_exe_env(t_shell *_shell);


// 		======> src/excution/cd/ft_cd.c <=======
void	ft_exe_cd(t_shell *_shell);



// 		======> src/excution/other_cmd/ft_command.c <=======
void exec_path_cmd(t_shell *_shell);
void ft_exec_cmd(t_shell *_shell);


// 		======> src/excution/other_cmd/ft_excute.c <=======
void ft_exe_command(t_shell *_shell);
char *ft_join_cmd(t_shell *_shell);
int ft_init(t_shell *_shell);
int	minishel(t_shell *_shell);


//		======> src/excution/export/ft_export1.c <=======
int	edit_var(char **str, char *var, char *value, int equal);
char	**add_var(char **env, char *var, char *value, int equal);
char *ft_getenv(char **env, char *var);
char *ft_getvar(char *str);
int	ft_check_var_exist(char **env, char *var);


//		======> src/excution/export/ft_export.c <=======
int	check_var_error(char *var);
void ft_exe_export(t_shell *_shell);


//		======> src/excution/export/display_export.c <=======
void	ft_display_export(char **exp);


//		======> src/excution/unset/ft_unset.c <=======
void ft_exe_unset(t_shell *_shell);

//		======> src/excution/exit/ft_exit.c <=======
int ft_exit(t_shell *_shell);



#endif
