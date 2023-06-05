/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:15:25 by esalim            #+#    #+#             */
/*   Updated: 2023/06/05 17:39:40 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_all(t_shell *_shell)
{
	if (!setup_output_redirections(_shell->pipes) \
		|| !setup_input_redirections(_shell))
	{
		free_double_pointer(_shell->pipes->content->commands);
		free(_shell->pipes->content);
		exit(1);
	}
	close(_shell->pipes->content->pipe_fds[0]);
	close(_shell->pipes->content->pipe_fds[1]);
	if (_shell->pipes->content->here_doc_string)
		setup_here_doc(_shell->pipes->content->here_doc_string);
}
