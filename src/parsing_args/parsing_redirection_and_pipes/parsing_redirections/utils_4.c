/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:31:43 by esalim            #+#    #+#             */
/*   Updated: 2023/06/05 17:39:40 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	split_commands(t_shell *shell, t_redirect	*redirect, char	**commands)
{
	int	res;
	int	i;
	int	j;

	i = 0;
	j = 0;
	res = 0;
	while (commands[j])
	{
		res = for_each_command(redirect, commands, &i, &j);
		if (!res || res == 4)
		{
			free(redirect);
			shell->status = 2;
			if (res == 4)
				shell->status = 1;
			return (0);
		}
		if (res == 2)
			break ;
	}
	return (1);
}
