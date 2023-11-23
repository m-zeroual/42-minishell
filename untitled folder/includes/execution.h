/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 19:58:34 by mzeroual          #+#    #+#             */
/*   Updated: 2023/06/09 15:19:57 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <string.h>
# include <sys/wait.h>
# include <inttypes.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define ECHO  "echo\0"
# define PWD  "pwd\0"
# define CD   "cd\0"
# define EN  "env\0"
# define EX  "export\0"
# define UNSET  "unset\0"
# define EXIT  "exit\0"

# define EXP 1
# define ENV 2

typedef struct s_shell
{
	char	*line;
	int		status;
	char	**env;
	char	*command_with_path;
	t_list	*pipes;
	int		i;
	int		here_doc_parsing;
	int		isheredoc;
	int		check;
	int		isopen;
	int		index;
	char	separator;
	int		fd;
}	t_shell;

void	ft_exe_echo(t_shell *_shell);

void	free_split(char **str);
char	*ft_str_tolower(char *cmd);

char	*curr_path(t_shell _shell);
void	ft_exe_pwd(t_shell *_shell);
void	ch_pwd(t_shell *_shell);

char	**ft_fill_env(char **env, int lines);
int		ft_count_env(char **env);
void	ft_exe_env(t_shell *_shell);

void	ft_exe_cd(t_shell *_shell);

void	ft_exec_cmd(t_shell *_shell);

void	ft_exe_command(t_shell *_shell);
char	*ft_join_cmd(t_shell *_shell);
int		ft_parsing(t_shell *_shell);
int		minishell(t_shell *_shell);

int		edit_var(char **str, char *var, char *value, int equal);
char	**add_var(char **env, char *var, char *value, int equal);
char	*ft_getenv(char **env, char *var);
char	*ft_getvar(char *str);
int		ft_check_var_exist(char **env, char *var);

int		check_var_error(char *var);
void	ft_exe_export(t_shell *_shell);

void	ft_display_export(char **exp);

void	ft_exe_unset(t_shell *_shell);

int		ft_exit(t_shell *_shell);

#endif
