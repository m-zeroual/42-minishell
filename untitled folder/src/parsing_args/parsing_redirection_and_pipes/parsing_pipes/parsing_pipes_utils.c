/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:48:41 by esalim            #+#    #+#             */
/*   Updated: 2023/05/29 23:48:54 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	get_number_of_commands(char **commands, int j)
{
	int	i;

	if (!commands)
		return (0);
	i = 0;
	while (commands[j + i] && commands[j + i][0] != PIPE)
		i++;
	return (i);
}

int	get_number_of_pipe(char **commands)
{
	int	number_of_pipes;
	int	i;

	if (!commands || !*commands)
		return (0);
	number_of_pipes = 0;
	i = -1;
	while (commands[++i])
		if (commands[i][0] == PIPE)
			number_of_pipes++;
	return (number_of_pipes);
}
