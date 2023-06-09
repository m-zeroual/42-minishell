/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:18:19 by esalim            #+#    #+#             */
/*   Updated: 2023/06/05 17:39:40 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_pipes(t_list *pipes)
{
	while (pipes)
	{
		pipe(pipes->content->pipe_fds);
		pipes = pipes->next;
	}
}

void	close_all_pipes(t_content *content)
{
	close(content->pipe_fds[0]);
	close(content->pipe_fds[1]);
	free(content->pipe_fds);
}
