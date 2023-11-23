/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 23:51:41 by esalim            #+#    #+#             */
/*   Updated: 2023/06/09 13:55:00 by esalim           ###   ########.fr       */
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

int	open_here_docs(t_shell *shell, t_list *node)
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
			if (!node->content->here_doc_string)
				return (0);
			continue ;
		}
		if (node->content->input_redirections[i].is_here_doc)
			free(get_here_doc_content(shell, \
				node->content->input_redirections[i].file));
	}
	return (1);
}

int	create_redirections(t_shell *shell, t_list *node)
{
	char		error;

	error = 0;
	node->content->output_redirections = create_output_files(shell, \
						node->content->output_redirections, &error);
	if (error == 1)
		return (0);
	node->content->input_redirections = get_input_file(shell, \
						node->content->input_redirections, &error);
	if (!open_here_docs(shell, node))
		return (0);
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

int	*exec(t_shell *_shell, int lstsize)
{
	int	*pids;

	pids = ft_calloc(lstsize + 1, sizeof(*pids));
	if (!pids)
		return (NULL);
	while (_shell->pipes && ++(_shell->i))
	{
		if (!_shell->pipes->content)
			continue ;
		if (!create_redirections(_shell, _shell->pipes) || !init(_shell))
		{
			ft_swap(_shell);
			continue ;
		}
		ft_exe_command(_shell);
		pids[_shell->i - 1] = _shell->pipes->content->pid;
		ft_swap(_shell);
	}
	return (pids);
}

int	minishell(t_shell *_shell)
{
	int	lstsize;
	int	status;
	int	*pids;
	int	i;

	if (!ft_parsing(_shell))
		return (0);
	create_pipes(_shell->pipes);
	close(_shell->pipes->content->pipe_fds[0]);
	_shell->i = 0;
	lstsize = ft_lstsize(_shell->pipes);
	pids = exec(_shell, lstsize);
	if (!pids)
		return (0);
	i = -1;
	while (++i <= lstsize)
	{
		if (pids[i])
		{
			waitpid(pids[i], &status, 0);
			if (WIFEXITED(status))
				_shell->status = WEXITSTATUS(status);
		}
	}
	return (free(pids), 1);
}
