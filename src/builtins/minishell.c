/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 23:51:41 by esalim            #+#    #+#             */
/*   Updated: 2023/06/07 16:40:04 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init(t_shell *_shell)
{
	t_content	*content;

	content = _shell->pipes->content;
	if (!content)
		return (0);
	if (!content->commands || !content->commands[0] \
			|| !content->commands[0][0])
	{
		if (content->commands && content->commands[0] \
				&& !content->commands[0][0])
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

void	open_here_docs(t_shell *shell, t_list *node)
{
	int	i;

	i = -1;
	while (node->content->input_redirections \
			&& node->content->input_redirections[++i].file)
	{
		if (!node->content->input_redirections[i + 1].file \
				&& node->content->input_redirections[i].is_here_doc)
		{
			node->content->here_doc_string = get_here_doc_content(shell, \
						node->content->input_redirections[i].file);
			continue ;
		}
		if (node->content->input_redirections[i].is_here_doc)
			free(get_here_doc_content(shell, \
				node->content->input_redirections[i].file));
	}
}

int	create_redirections(t_shell *shell, t_list *node)
{
	char		error;

	error = 0;
	if (!node->content)
		return (0);
	node->content->output_redirections = create_output_files(shell, \
						node->content->output_redirections, &error);
	if (error == 1)
		return (0);
	node->content->input_redirections = get_input_file(shell, \
						node->content->input_redirections, &error);
	open_here_docs(shell, node);
	if (error > 1)
	{
		if (error > 2)
		{
			if (error == 3)
				ft_printf("minishell: No such file or directory\n");
			else if (error == 4)
				ft_printf("minishell: Permission denied\n");
			shell->status = 1;
		}
		return (0);
	}
	return (1);
}

int	ft_parsing(t_shell *_shell)
{
	char *cmd;
	char *tmp_cmd;

	cmd = readline("minishell -> ");
	if (!cmd)
		exit(_shell->status);
	tmp_cmd = ft_strdup(cmd);
	_shell->pipes = main_parsing(_shell, cmd);
	if (!_shell->pipes)
		return (free(tmp_cmd), 0);
	_shell->i = 0;
	add_history(tmp_cmd);
	free(tmp_cmd);
	return (1);
}

// void	swap_and_free(t_shell *_shell)
// {
// 	t_list	*tmp;

// 	tmp = _shell->pipes;
// 	_shell->pipes = _shell->pipes->next;
// 	free_struct(_shell, tmp);
// }

int	minishell(t_shell *_shell)
{
	t_list	*tmp;
	int		status;

	if (!ft_parsing(_shell))
		return (0);
	create_pipes(_shell->pipes);
	close(_shell->pipes->content->pipe_fds[0]);
	_shell->i = 0;
	tmp = _shell->pipes;
	while (_shell->pipes && ++(_shell->i))
	{
		if (!create_redirections(_shell, _shell->pipes) || !init(_shell))
		{
			close(_shell->pipes->content->pipe_fds[0]);
			close(_shell->pipes->content->pipe_fds[1]);
			if (_shell->pipes->next)
				close(_shell->pipes->next->content->pipe_fds[0]);
			_shell->pipes = _shell->pipes->next;
			continue ;
		}
		ft_exe_command(_shell);
		close(_shell->pipes->content->pipe_fds[0]);
		close(_shell->pipes->content->pipe_fds[1]);
		if (_shell->pipes->next)
			close(_shell->pipes->next->content->pipe_fds[1]);
		_shell->pipes = _shell->pipes->next;
	}
	_shell->pipes = tmp;
	while (_shell->pipes)
	{
		if (_shell->pipes->content->pid)
		{
			waitpid(_shell->pipes->content->pid, &status, 0);
			if (WIFEXITED(status))
				_shell->status = WEXITSTATUS(status);
		}
		tmp = _shell->pipes;
		_shell->pipes = _shell->pipes->next;
		free_struct(_shell, tmp);
	}
	return (1);
}
