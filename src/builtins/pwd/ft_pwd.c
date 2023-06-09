/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:40:55 by mzeroual          #+#    #+#             */
/*   Updated: 2023/06/09 14:54:53 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*curr_path(t_shell _shell)
{
	char	**str;
	char	*pwd;
	int		i;

	i = 0;
	while (_shell.env[i])
	{
		str = ft_split(_shell.env[i], '=');
		if (!ft_strncmp(str[0], "PWD", 3))
		{
			pwd = ft_strdup(str[1]);
			free_split(str);
			return (pwd);
		}
		free_split(str);
		i++;
	}
	return (0);
}

void	ft_exe_pwd(t_shell *_shell)
{
	char	*str;
	int		pid;

	str = 0;
	pid = fork ();
	if (pid == 0)
	{
		setup_all(_shell);
		str = getcwd(NULL, 0);
		printf("%s\n", str);
		free(str);
		exit (0);
	}
	else
		_shell->pipes->content->pid = pid;
}

void	ch_pwd(t_shell *_shell)
{
	int		i;
	char	**str;
	char	*str1;

	i = 0;
	while (_shell->env[i])
	{
		str = ft_split(_shell->env[i], '=');
		if (!ft_strncmp(str[0], "PWD", 3))
		{
			free(_shell->env[i]);
			str1 = getcwd(NULL, 0);
			_shell->env[i] = ft_strjoin("PWD=", str1);
			free(str1);
		}
		free_split(str);
		i++;
	}
}
