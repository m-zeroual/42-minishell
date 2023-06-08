/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeroual <mzeroual@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:40:55 by mzeroual          #+#    #+#             */
/*   Updated: 2023/06/07 19:41:14 by mzeroual         ###   ########.fr       */
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
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		setup_all(_shell);
		str = getcwd(NULL, 1024);
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
	char	str1[1024];

	i = 0;
	while (_shell->env[i])
	{
		str = ft_split(_shell->env[i], '=');
		if (!ft_strncmp(str[0], "PWD", 3))
		{
			free(_shell->env[i]);
			getcwd(str1, 1024);
			_shell->env[i] = ft_strjoin("PWD=", str1);
		}
		free_split(str);
		i++;
	}
}
