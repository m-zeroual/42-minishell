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

	cmd = _shell->pipes->content->commands[0];
	cmd_lower = ft_str_tolower(cmd);

	if (!ft_strncmp(cmd, EX, ft_strlen(EX) + 1))     // just lowercase
		ft_exe_export(_shell);
	else if (!ft_strncmp(cmd, UNSET, ft_strlen(UNSET) + 1))   // just lowercase
		ft_exe_unset(_shell);
	else if (!ft_strncmp(cmd, EXIT, ft_strlen(EXIT) + 1))  // just lowercase
		exit(0);
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

char	*ft_join_cmd(t_shell *_shell)
{
	int		i;
	char	*help_for_free;
	char	*path_cmd;
	char	**path;
	char	*cmd = 0;

	if (!_shell->pipes->content->commands)
		return (NULL);
	if (ft(_shell->pipes->content->commands[0]))
		return (ft_strdup(_shell->pipes->content->commands[0]));
	cmd = ft_getenv(_shell->env, "PATH");
	path = ft_split(cmd, ':');
	if (!path)
	{
		printf("minshell: %s: %s\n", _shell->pipes->content->commands[0], "No such file or directory");
		_shell->status = 126;
		return (0);
	}
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
				printf("minshell: %s%s: %s\n", path[i], cmd, "Permission denied");
				free_split(path);
				_shell->status = 126;
				return (NULL);
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

	cmd = readline("minishell -> ");
	if (!cmd)
		exit(0);
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
		free(_shell->command_with_path);
	if (!tmp)
		return ;
    free_double_pointer(tmp->content->commands);
	free_t_redirect(tmp->content->output_redirections);
	free_t_redirect(tmp->content->input_redirections);
	free(tmp->content);
    free(tmp);
}

void	del_content(void *cont)
{
	t_content *content = (t_content *)cont;
	free_double_pointer(content->commands);
	free_t_redirect(content->output_redirections);
	free_t_redirect(content->input_redirections);
	free(content);
	return ;
}

int	minishel(t_shell *_shell)
{
	t_list		*tmp;
    t_content   *content;
    char        error;

	if (!ft_init(_shell))
		return (0);
//	no LEAKS
	// create_pipes(_shell->pipes);
	while (_shell->pipes && ++(_shell->i))
    {
        error = 0;
        content  = _shell->pipes->content;
        if (!content)
			return (free_struct(_shell, NULL), ft_lstclear(&_shell->pipes, del_content), 0);
        content->output_redirections = create_output_files(content->output_redirections, &error);
        if (error == 1)
			return (free_struct(_shell, NULL), ft_lstclear(&_shell->pipes, del_content), 0);
			
        content->input_redirections = get_input_file(content->input_redirections, &error);
        if (error == 1)
            return (free_struct(_shell, NULL), ft_lstclear(&_shell->pipes, del_content), 0);

		_shell->command_with_path = ft_join_cmd(_shell);
		if (!_shell->command_with_path)
			return (free_struct(_shell, NULL), ft_lstclear(&_shell->pipes, del_content), 0);

		ft_exe_command(_shell);

        // wait(NULL);
        // close(_shell->pipes->content->pipe_fds[1]);

        tmp = _shell->pipes;
        _shell->pipes = _shell->pipes->next;
		free_struct(_shell, tmp);
	}
	// close_all_pipes(_shell->pipes_fds, size);
	return (1);
}
