/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:08:01 by mzeroual          #+#    #+#             */
/*   Updated: 2023/06/08 20:46:02 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_exec_cmd(t_shell *_shell)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_all(_shell);
		if (execve(_shell->command_with_path, \
				_shell->pipes->content->commands, _shell->env) == -1)
		{
			perror("minishell: ");
			exit(1);
		}
	}
	else
		_shell->pipes->content->pid = pid;
}
