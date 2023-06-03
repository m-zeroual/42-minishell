
#include "../../includes/minishell.h"

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
	return (1);
}
