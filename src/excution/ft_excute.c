#include "../../includes/minishell.h"

int ft(char *str)
{
	
	if (!ft_strncmp(str, EX, ft_strlen(EX) + 1) \
		|| !ft_strncmp(str, UNSET, ft_strlen(UNSET) + 1) \
		|| !ft_strncmp(str, EXIT, ft_strlen(EXIT) + 1))
		return (1);
	return (0);
}

void	ft_exe_command(t_shell *_shell)
{
	char *cmd;
	char *cmd_lower;
	// char *tmp;
	// char *tmp2;

	
	cmd = _shell->pipes->content->commands[0];
	printf("!%s!\n", cmd);
	cmd_lower = ft_str_tolower(cmd);
	// tmp = cmd_lower + ft_strlen(cmd_lower);
	// tmp2 = cmd + ft_strlen(cmd);
	if (!ft_strncmp(cmd, EX, ft_strlen(EX)))     // just lowercase
		ft_exe_export(_shell);
	else if (!ft_strncmp(cmd, UNSET, ft_strlen(UNSET)))   // just lowercase
		ft_exe_unset(_shell);
	else if (!ft_strncmp(cmd, EXIT, ft_strlen(EXIT)))  // just lowercase
		exit(0);
	else if (!ft_strncmp(cmd, CD, ft_strlen(CD)))      // just lowercas
		ft_exe_cd(_shell);

	else if (!ft_strncmp(cmd_lower, ECHO, ft_strlen(ECHO)))
		ft_exe_echo(_shell);
	else if (!ft_strncmp(cmd_lower, PWD, ft_strlen(PWD)))
		ft_exe_pwd(_shell);
	else if (!ft_strncmp(cmd_lower, EN, ft_strlen(EN)))
		ft_exe_env(_shell);
	else
		ft_exec_cmd(_shell);
	free(cmd_lower);
}

char	*ft_join_cmd(t_shell *_shell)
{
	int		i;
	char	*help_for_free;
	char	*path_cmd;
	char	**path;
	char	*cmd = 0;

	if (ft(_shell->pipes->content->commands[0]))
		return (ft_strdup(cmd));
	path = ft_split(ft_getenv(_shell->env, "PATH"), ':');
	if (!path)
	{
		printf("minshell: %s: %s\n", cmd, "No such file or directory");
		_shell->status = 126;
		return (0);
	}

	cmd = _shell->pipes->content->commands[0];
	i = 0;
	
	if (!ft_strchr(cmd, '/'))
	{
		while (path[i])
		{
			help_for_free = ft_strjoin(path[i], "/");
			path_cmd = ft_strjoin(help_for_free, cmd);
			free(help_for_free);
			if (!access(path_cmd, F_OK) && !access(path_cmd, X_OK))
			{
				free_split(path);
				return (path_cmd);
			}
			free(path_cmd);
			i++;
		}
		printf("minshell: %s: %s\n", cmd, "command not found");
		_shell->status = 127;
	}
	else if (!access(cmd, F_OK) && cmd[ft_strlen(cmd) - 1] == '/')
	{
		printf("minshell: %s: %s\n", cmd, "is a directory");
		_shell->status = 126;
	}
	else if (!access(cmd, F_OK) && !access(cmd, X_OK))
		return (free_split(path), ft_strdup(cmd));
	else
	{
		printf("minshell: %s: %s\n", cmd, strerror(errno));
		_shell->status = 126;
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
	// printf("#%s#\n", cwd);
	// char *s = ft_strjoin(ft_strrchr(cwd, '/') + 1, "\033[0;32m →\033[0m ");
	// printf("#%s#\n", s);
	// free(cwd);
	// cmd = readline(s);
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
					// int i = -1;
					// while (_shell->pipes->content->commands[++i])
					// 	printf("\"%s\"\n", _shell->pipes->content->commands[i]);
					// printf("\n");
	// // free(content);
	// // free(_shell->pipes);
	return (1);
}

int	minishel(t_shell *_shell)
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
	// close(_shell->pipes_fds[0][0]);

	while (_shell->pipes && ++(_shell->i))
    {
        if (!_shell->pipes->content)
            break ;
		_shell->command = ft_join_cmd(_shell);
		if (!_shell->command)
			return (0);
		ft_exe_command(_shell);

        // wait(NULL);
        close(_shell->pipes_fds[_shell->i - 1][0]);

        tmp = _shell->pipes;
		free(_shell->command);
        _shell->pipes = _shell->pipes->next;
        free_double_pointer(tmp->content->commands);
		free(tmp->content);
        free(tmp);
	}
	close_all_pipes(_shell->pipes_fds, size);
	return (1);
}
