
#include "../../includes/minishell.h"

int	ft_init(t_shell *_shell)
{
	char *cmd;

	cmd = readline("minishell -> ");
	if (!cmd)
		exit(_shell->status);
	add_history(cmd);
	_shell->pipes = main_parsing(_shell, cmd);
	// int i =-1;
	// while (_shell->pipes->content->commands[++i])
	// 	printf("%s\n", _shell->pipes->content->commands[i]);
	if (!_shell->pipes)
		return (0);
	_shell->i = 0;
	return (1);
}

int	init_pipe(t_shell *_shell)
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
			ft_printf("minishell: command not found\n");
			_shell->status = 127;
		}
		return (0);
	}
	_shell->command_with_path = ft_join_cmd(_shell);
	if (!_shell->command_with_path)
		return (0);
	return (1);
}

int	create_redirections(t_shell *shell)
{
	t_list	*lst;
	t_content   *content;
    char        error;
	
	lst = shell->pipes;
	while (lst)
	{
		error = 0;
		content  = lst->content;
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
        	    lst->content->here_doc_string = get_here_doc_content(shell, content->input_redirections[i].file);
        	    return (1);
        	}
        	if (content->input_redirections[i].is_here_doc)
        	   free(get_here_doc_content(shell, content->input_redirections[i].file));
		}
		i = -1;
		while (content->input_redirections && content->input_redirections[++i].file)
        	if (content->input_redirections[i].file && !content->input_redirections[i].is_here_doc && !check_permissions(shell, content->input_redirections[i].file, "1100"))
        	    break ;
		if (error == 1)
			return (0);
		lst = lst->next;
	}
	return (1);
}

int	minishel(t_shell *_shell)
{
	// t_list		*tmp;
	// int			i;
	if (!ft_init(_shell))
		return (0);
	// no LEAKS
	create_pipes(_shell->pipes);
	close(_shell->pipes->content->pipe_fds[0]);
	if (!create_redirections(_shell))
		return (0);

	while (_shell->pipes && ++(_shell->i))
    {
		if (!init_pipe(_shell))
		{
			if (_shell->pipes->next)
				close(_shell->pipes->next->content->pipe_fds[0]);
			_shell->pipes = _shell->pipes->next;
            continue ;
		}
		ft_exe_command(_shell);
		if (_shell->pipes->next)
		{
			close(_shell->pipes->content->pipe_fds[0]);
			close(_shell->pipes->content->pipe_fds[1]);
			close(_shell->pipes->next->content->pipe_fds[1]);
		}
        // tmp = _shell->pipes;
        _shell->pipes = _shell->pipes->next;
		// free_struct(_shell, tmp);
	}
    return (0);
}
