/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:15:25 by esalim            #+#    #+#             */
/*   Updated: 2023/06/09 13:53:50 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_all(t_shell *_shell)
{
	t_list	*tmp;

	if (!setup_output_redirections(_shell->pipes) \
		|| !setup_input_redirections(_shell))
	{
		free_struct(_shell, _shell->pipes);
		exit(1);
	}
	tmp = _shell->pipes;
	while (tmp)
	{
		close(tmp->content->pipe_fds[0]);
		close(tmp->content->pipe_fds[1]);
		tmp = tmp->next;
	}
	if (_shell->pipes->content->here_doc_string)
		setup_here_doc(_shell->pipes->content->here_doc_string);
}

void	ft_swap(t_shell *_shell)
{
	t_list	*tmp;

	close(_shell->pipes->content->pipe_fds[0]);
	close(_shell->pipes->content->pipe_fds[1]);
	if (_shell->pipes->next)
		close(_shell->pipes->next->content->pipe_fds[1]);
	tmp = _shell->pipes;
	_shell->pipes = _shell->pipes->next;
	free_struct(_shell, tmp);
}

int	ft_parsing(t_shell *_shell)
{
	add_history(_shell->line);
	_shell->pipes = main_parsing(_shell, _shell->line);
	if (!_shell->pipes)
		return (0);
	_shell->i = 0;
	return (1);
}
