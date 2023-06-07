/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeroual <mzeroual@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:08:01 by mzeroual          #+#    #+#             */
/*   Updated: 2023/06/07 15:08:04 by mzeroual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// void	exec_path_cmd(t_shell *_shell)
// {
// 	if (ft_strchr(_shell->cmd, '/'))
// 	{
// 		if (access(_shell->first_part_cmd_l, F_OK) == 0)
// 		{
// 			if (execve(_shell->first_part_cmd_l, 
//_shell->pipes->content->commands, _shell->ev) == -1)
// 				printf("Error in execve function\n");
// 		}
// 		ft_printf("minishell: %s: No such file or directory\n" 
// 			, _shell->pipes->content->commands[0]);
// 		exit (127);
// 	}
// }

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
