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

void	ft_exe_command(t_shell *_shell)
{
	char *cmd;
	char *cmd_lower;

	cmd = _shell->pipes->content->commands[0];
	cmd_lower = ft_str_tolower(cmd);

	if (!ft_strncmp(cmd, EX, ft_strlen(EX) + 1))     // just lowercase
		ft_exe_export(_shell);
	else if (!ft_strncmp(cmd, UNSET, ft_strlen(UNSET) + 1))   // just lowercase
		ft_exe_unset(_shell);
	else if (!ft_strncmp(cmd, EXIT, ft_strlen(EXIT) + 1))  // just lowercase
	{
		if (_shell->pipes->next || _shell->i > 1)
			return free(cmd_lower);
		exit(ft_exit(_shell));
	}
	else if (!ft_strncmp(cmd, CD, ft_strlen(CD) + 1))      // just lowercas
		ft_exe_cd(_shell);
// --------------------------------------------------------------------
	else if (!ft_strncmp(cmd_lower, ECHO, ft_strlen(ECHO) + 1))
		ft_exe_echo(_shell);
	else if (!ft_strncmp(cmd_lower, PWD, ft_strlen(PWD) + 1))
		ft_exe_pwd(_shell);
	else if (!ft_strncmp(cmd_lower, EN, ft_strlen(EN) + 1))
		ft_exe_env(_shell);
	else
		ft_exec_cmd(_shell);
	free(cmd_lower);
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

void	free_struct(t_shell *_shell, t_list *tmp)
{
	if (_shell->command_with_path)
	{
		free(_shell->command_with_path);
		_shell->command_with_path = NULL;
	}
	if (!tmp)
		return ;
    free_double_pointer(tmp->content->commands);
	free_t_redirect(tmp->content->output_redirections);
	free_t_redirect(tmp->content->input_redirections);
	free(tmp->content->here_doc_string);
	free(tmp->content);
    free(tmp);
}

void	del_content(void *cont)
{
	t_content *content = (t_content *)cont;
	free_double_pointer(content->commands);
	free_t_redirect(content->output_redirections);
	free_t_redirect(content->input_redirections);
	free(content->here_doc_string);
	free(content);
	return ;
}

int	init(t_shell *_shell)
{
	t_content   *content;

    content  = _shell->pipes->content;
	if (!content)
		return (0);

    if (!content->commands || !content->commands[0] || !content->commands[0][0])
	{
		// _shell->status = 1;
		if (content->commands && content->commands[0] && !content->commands[0][0])
		{
			ft_printf("minishell: : command not found\n");
			_shell->status = 127;
		}
		_shell->command_with_path = ft_strdup("");
		return (0);
	}
	_shell->command_with_path = ft_join_cmd(_shell);
	if (!_shell->command_with_path)
		return (0);
	return (1);
}

int     create_redirections(t_shell *shell, t_list *node)
{
    t_content   *content;
    char        error;

    error = 0;
    content  = node->content;
    if (!content)
            return (0);
    content->output_redirections = create_output_files(shell, content->output_redirections, &error);
    if (error == 1)
            return (0);
    content->input_redirections = get_input_file(shell, content->input_redirections, &error);
    int i = -1;
    while (content->input_redirections && content->input_redirections[++i].file)
    {
    	if (!content->input_redirections[i + 1].file && content->input_redirections[i].is_here_doc)
    	{
    	    node->content->here_doc_string = get_here_doc_content(shell, content->input_redirections[i].file);
    	    continue;
    	}
    	if (content->input_redirections[i].is_here_doc)
    	   free(get_here_doc_content(shell, content->input_redirections[i].file));
    }
    if (error == 2)
		return (0);
	if (error == 3)
	{
		ft_printf("minishell: No such file or directory\n");
		shell->status = 1;
		return (0);
	}
	if (error == 4)
	{
		ft_printf("minishell: Permission denied\n");
		shell->status = 1;
		return (0);
	}
    return (1);
}

int	minishell(t_shell *_shell)
{
	t_list		*tmp;
	// int			status;

	if (!ft_init(_shell))
		return (0);
	create_pipes(_shell->pipes);
	close(_shell->pipes->content->pipe_fds[0]);
	tmp = _shell->pipes;
	while (_shell->pipes && ++(_shell->i))
    {
		if (!create_redirections(_shell, _shell->pipes) || !init(_shell))
		{
			if (_shell->pipes->next)
				close(_shell->pipes->next->content->pipe_fds[0]);
			tmp = _shell->pipes;
			_shell->pipes = _shell->pipes->next;
			free_struct(_shell, tmp);
            continue ;
		}
		ft_exe_command(_shell);
		if (_shell->pipes->next)
		{
			close(_shell->pipes->content->pipe_fds[0]);
			close(_shell->pipes->content->pipe_fds[1]);
			close(_shell->pipes->next->content->pipe_fds[1]);
		}
        tmp = _shell->pipes;
        _shell->pipes = _shell->pipes->next;
		free_struct(_shell, tmp);
	}
	// while ((_shell->i)--)
	// {
	// 	wait(&status);
	// 	if (WIFEXITED(status))
	// 		_shell->status = WEXITSTATUS(status);
	// }
	return (1);
}
