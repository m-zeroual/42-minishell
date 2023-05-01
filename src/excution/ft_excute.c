#include "../../includes/minishell.h"

char *ft(char *str)
{
	if (ft_strchr(str, '/'))
		str = ft_strdup(str + (ft_get_index_reverse(str, '/', 1) + 1));
	else
		return (str);
	return (ft_strdup(str));
}

void	ft_exe_command(t_shell *_shell)
{
	char *cmd;
	char *cmd_lower;
	
	cmd = ft(_shell->pipes->content->commands[0]);
	cmd_lower = ft_str_tolower(_shell->pipes->content->commands[0]);
	if (!ft_strncmp(cmd_lower, ECHO, 5))
		ft_exe_echo(*_shell);
	else if (!ft_strncmp(cmd_lower, PWD, 4))
		ft_exe_pwd(*_shell);
	else if (!ft_strncmp(cmd_lower, EN, 4))
		ft_exe_env(*_shell);
	else if (!ft_strncmp(cmd, CD, 3))      // just lowercase
		ft_exe_cd(_shell);
	else if (!ft_strncmp(cmd, EX, 7))     // just lowercase
		ft_exe_export(_shell);
	else if (!ft_strncmp(cmd, UNS, 5))   // just lowercase
		ft_exe_unset(_shell);
	else if (!ft_strncmp(cmd, EXIT, 6))  // just lowercase
		exit(0);
	else
		ft_exec_cmd(_shell);
	free(cmd_lower);
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
	char *cmd;

	// char *cwd = curr_path(*_shell);
	// char *s = ft_strjoin(ft_strrchr(cwd, '/') + 1, "\033[0;32m →\033[0m ");
	// free(cwd);
	cmd = readline("minishell -> ");
	// printf("|%s|\n", _shell->cmd);
	// free(s);
	if (!cmd)
		exit (0);
	add_history(cmd);
	_shell->pipes = main_parsing(cmd);
	if (!_shell->pipes)
		return (0);
	_shell->i = 0;
	// t_content *content = _shell->pipes->content;

	// _shell->pipes->content->commands = content->commands;
	// // int i = -1;
	// // while (_shell->pipes->content->commands[++i])
	// // 	printf("|%s|\n", _shell->pipes->content->commands[i]);
	// // free(content);
	// // free(_shell->pipes);
	return (1);
}

int	ft_exe(t_shell *_shell)
{
	t_list	*tmp;
	int		size;

	ft_init(_shell);
	if (!_shell)
		return 1;
	size = ft_lstsize(_shell->pipes);
	_shell->pipes_fds = create_pipes(size);
	if (!_shell->pipes_fds)
	{
		print_error(NULL, ": Pipes Error\n");
		return (1);
	}
	close(_shell->pipes_fds[0][0]);
		
	while (_shell->pipes && ++(_shell->i))
    {
        if (!_shell->pipes->content)
            break ;
		_shell->command = ft_join_cmd(_shell->pipes->content->commands[0]);
		ft_exe_command(_shell);

        // wait(NULL);
        // close(_shell->pipes_fds[_shell->i - 1][0]);

        tmp = _shell->pipes;
        _shell->pipes = _shell->pipes->next;
		free(_shell->command);
		// free_split(_shell->pipes->content->commands);
        free_double_pointer(_shell->pipes->content->commands);
		// free(_shell->pipes->content);
        // free(tmp);
		// free(_shell->first_part_cmd_l);
	}
	// close_all_pipes(_shell->pipes_fds, size);
	return (1);
}
