#include "../../includes/minishell.h"

char *ft(char *str)
{
	if (ft_strchr(str, '/'))
		str = ft_strdup(str + (ft_get_index_reverse(str, '/', 1) + 1));
	else
		return (str);
	return (ft_strdup(str));
}

int	ft_exe_command(t_shell *_shell)
{
	char *cmd;
	
	cmd = ft(_shell->cmd_split[0]);
	if (!ft_strncmp(_shell->first_part_cmd_l, ECHO, 5))
		ft_exe_echo(*_shell);
	else if (!ft_strncmp(_shell->first_part_cmd_l, PWD, 4))
		ft_exe_pwd(*_shell);
	else if (!ft_strncmp(_shell->first_part_cmd_l, EN, 4))
		ft_exe_env(*_shell);
	else if (!ft_strncmp(cmd, CD, 3))      // just lowercase
		ft_exe_cd(_shell);
	else if (!ft_strncmp(cmd, EX, 7))     // just lowercase
		ft_exe_export(_shell);
	else if (!ft_strncmp(cmd, UNS, 5))   // just lowercase
		ft_exe_unset(_shell);
	else if (!ft_strncmp(cmd, EXIT, 6))  // just lowercase
		return (0);
	else
		ft_exec_cmd(_shell);
	return (1);
}

char	*ft_join_cmd(char *cmd)
{
	int		i;
	char	*help_for_free;
	char	*path_cmd;
	char	**path;

	path = ft_split(getenv("PATH"), ':');


	i = 0;
	if (!ft_strchr(cmd, '/'))
	{
		while (path[i])
		{
			help_for_free = ft_strjoin(path[i], "/");
			path_cmd = ft_strjoin(help_for_free, cmd);
			free(help_for_free);
			if (!access(path_cmd, F_OK))
			{
				free_split(path);
				return (path_cmd);
			}
			free(path_cmd);
			i++;
		}
	}
	else
	{
		free_split(path);
		return (ft_strdup(cmd));

	}
		free_split(path);
	return (0);
}


int all_speace(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	ft_init(t_shell *_shell)
{
	char *cwd = curr_path(*_shell);
	char *s = ft_strjoin(ft_strrchr(cwd, '/') + 1, "\033[0;32m →\033[0m ");
	free(cwd);
	_shell->cmd = readline(s);
	// printf("|%s|\n", _shell->cmd);
	free(s);
	if (!_shell->cmd)
		exit (0);
	if (*_shell->cmd == 0 || all_speace(_shell->cmd))
		return (0);
	if (_shell->cmd == 0)
		exit (1);
	add_history(_shell->cmd);
	t_list *pipe = main_parsing(_shell->cmd);
	t_content *content = pipe->content;
	_shell->cmd_split = content->commands;
	// int i = -1;
	// while (_shell->cmd_split[++i])
	// 	printf("%s\n", _shell->cmd_split[i]);
	free(content);
	free(pipe);
	_shell->first_part_cmd_l = ft_str_tolower(_shell->cmd_split[0]);
	return (1);
}

int	ft_exe(t_shell *_shell)
{
	if (!ft_init(_shell))
		return (1);
	_shell->command = ft_join_cmd(_shell->cmd_split[0]);
	if (!ft_exe_command(_shell))
		return (0);
	free_split(_shell->cmd_split);
	free(_shell->first_part_cmd_l);
	free(_shell->command);
	return (1);
}
