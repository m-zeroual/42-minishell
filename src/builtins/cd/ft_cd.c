/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeroual <mzeroual@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:58:20 by mzeroual          #+#    #+#             */
/*   Updated: 2023/06/07 14:58:24 by mzeroual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_chdir(t_shell *_shell, char *str)
{
	char	*cur_working;

	cur_working = getcwd(NULL, 1024);
	if (!chdir(str))
	{
		ch_pwd(_shell);
		_shell->status = 0;
		if (!edit_var(_shell->env, "OLDPWD", cur_working, 1))
			_shell->env = add_var(_shell->env, "OLDPWD", cur_working, 1);
		return ;
	}
	ft_printf("minishell: %s: No such file or directory\n", \
	_shell->pipes->content->commands[1]);
	_shell->status = 1;
}

void	ft_exe_cd(t_shell *_shell)
{
	char	*str;

	if (_shell->pipes->next || _shell->i > 1)
		return ;
	if (_shell->pipes->content->commands[1] == NULL
		|| !ft_strncmp(_shell->pipes->content->commands[1], "~", 1))
	{
		str = ft_getenv(_shell->env, "HOME");
		if (!str)
		{
			ft_printf("minishell: %s: HOME not set\n", \
			_shell->pipes->content->commands[0]);
			_shell->status = 1;
		}
		else
		{
			ft_chdir(_shell, str);
			free(str);
		}
	}
	else
		ft_chdir(_shell, _shell->pipes->content->commands[1]);
}
