#include "../../../includes/minishell.h"

int ft_is_builtins(char *str)
{
	
	if (!ft_strncmp(str, EX, ft_strlen(EX) + 1) \
		|| !ft_strncmp(str, UNSET, ft_strlen(UNSET) + 1) \
		|| !ft_strncmp(str, CD, ft_strlen(CD) + 1)
		|| !ft_strncmp(str, PWD, ft_strlen(PWD) + 1)
		|| !ft_strncmp(str, EN, ft_strlen(EN) + 1)
		|| !ft_strncmp(str, ECHO, ft_strlen(ECHO) + 1)
		|| !ft_strncmp(str, EXIT, ft_strlen(EXIT) + 1))
		return (1);
	return (0);
}


char *ft_fix_path(char *path)
{
	int		i;
	int		j;
	int		len;
	char	*new_path;

	i = -1;
	j = 0;
	len = ft_strlen(path);
	while (path[++i])
		if ((path[i] == ':' && (!i || i == len - 1)) || (path[i] == ':' && path[i + 1] == ':'))
			j++;
	new_path = ft_calloc((len + j + 1) , sizeof(char));
	if (!new_path)
		return (0);
	i = 0;
	j = 0;
	while (path[i])
	{
		if ((path[i] == ':' && i == 0))
		{
			new_path[j++] = '.';
			if ((path[i] == ':' && path[i + 1] == ':'))
			{
				new_path[j++] = path[i];
				new_path[j++] = '.';
			}
			else
				new_path[j++] = path[i];
		}
		else if ((path[i] == ':' && i == len - 1) || (path[i] == ':' && path[i + 1] == ':'))  // /bin/bash::
		{
			new_path[j++] = path[i];
			new_path[j++] = '.';
		}
		else
			new_path[j++] = path[i];
		i++;
	}
	free(path);
	return (new_path);
}

char	*ft_join_cmd(t_shell *_shell)
{
	int		i;
	char	*help_for_free;
	char	*path_cmd;
	char	**path;
	char	*cmd = 0;

	if (!_shell->pipes->content->commands)
		return (NULL);
	if (ft_is_builtins(_shell->pipes->content->commands[0]))
		return (ft_strdup(_shell->pipes->content->commands[0]));
	if (!ft_strchr(_shell->pipes->content->commands[0], '/'))
	{
		cmd = ft_getenv(_shell->env, "PATH");
		if (!cmd)
		{
			ft_printf("minishell: No such file or directory\n");
			// ft_printf("minshell: %s: %s\n", _shell->pipes->content->commands[0], "No such file or directory");
			_shell->status = 127;
			return (0);
		}
	}
	else
		cmd = ft_strdup(_shell->pipes->content->commands[0]);
	
	cmd = ft_fix_path(cmd);
	if (!cmd)
		return (0);
	// printf("|%s|\n", cmd);
	path = ft_split(cmd, ':');
	// if (!path)
	// {
	// 	ft_printf("minishell: No such file or directory\n");
	// 	// ft_printf("minshell: %s: %s\n", _shell->pipes->content->commands[0], "No such file or directory");
	// 	// _shell->status = 126;
	// 	_shell->status = 127;
	// 	return (0);
	// }
	free(cmd);
	cmd = _shell->pipes->content->commands[0];
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
				if (!access(path_cmd, X_OK))
				{
					free_split(path);
					return (path_cmd);
				}
				ft_printf("minishell: %s%s: %s\n", path[i], cmd, "Permission denied");
				free_split(path);
				_shell->status = 1;
				return (NULL);
			}
			free(path_cmd);
			i++;
		}
		// ft_printf("minishell: %s: %s\n", cmd, "command not found");
		ft_printf("minishell: command not found\n");
		_shell->status = 127;
	}
	else if (!access(cmd, F_OK) && cmd[ft_strlen(cmd) - 1] == '/')
	{
		ft_printf("minishell: %s: %s\n", cmd, "is a directory");
		_shell->status = 126;
	}
	else if (cmd[ft_strlen(cmd) - 1] == '/' && !(cmd[ft_strlen(cmd) - 1] = '\0') && !access(cmd, F_OK))
	{
		ft_printf("minishell: %s/: %s\n", cmd, "Not a directory");
		_shell->status = 126;
	}
	else if (!access(cmd, F_OK) && !access(cmd, X_OK))
		return (free_split(path), ft_strdup(cmd));
	else
	{
		// ft_printf("minshell: %s: %s\n", cmd, strerror(errno));
		ft_printf("minishell: No such file or directory\n");
		_shell->status = 127;
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

	cmd = readline("minishell -> ");
	if (!cmd)
		exit(_shell->status);
	add_history(cmd);
	_shell->pipes = main_parsing(_shell, cmd);
	if (!_shell->pipes)
		return (0);
	_shell->i = 0;
	return (1);
}
