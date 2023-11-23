/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:18:19 by esalim            #+#    #+#             */
/*   Updated: 2023/05/29 23:18:39 by esalim           ###   ########.fr       */
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
