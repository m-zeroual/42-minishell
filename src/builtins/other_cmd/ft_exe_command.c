/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeroual <mzeroual@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:09:25 by mzeroual          #+#    #+#             */
/*   Updated: 2023/06/07 15:09:29 by mzeroual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*ft_str_tolower(char *cmd)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_calloc(ft_strlen(cmd) + 1, 1);
	if (!str)
		return (0);
	while (cmd[i])
	{
		str[i] = ft_tolower(cmd[i]);
		i++;
	}
	return (str);
}

void	ft_exe_command(t_shell *_shell)
{
	char	*cmd;
	char	*cmd_lower;

	cmd = _shell->pipes->content->commands[0];
	cmd_lower = ft_str_tolower(cmd);
	if (!ft_strncmp(cmd, EX, ft_strlen(EX) + 1)) // just lowercase
		ft_exe_export(_shell);
	else if (!ft_strncmp(cmd, UNSET, ft_strlen(UNSET) + 1)) // just lowercase
		ft_exe_unset(_shell);
	else if (!ft_strncmp(cmd, EXIT, ft_strlen(EXIT) + 1)) // just lowercase
		exit(ft_exit(_shell));
	else if (!ft_strncmp(cmd, CD, ft_strlen(CD) + 1)) // just lowercas
		ft_exe_cd(_shell);
// --------------------------------------------------------------------
	else if (!ft_strncmp(cmd_lower, ECHO, ft_strlen(ECHO) + 1))
		ft_exe_echo(_shell);
	else if (!ft_strncmp(cmd_lower, PWD, ft_strlen(PWD) + 1))
		ft_exe_pwd(_shell);
	else if (!ft_strncmp(cmd_lower, EN, ft_strlen(EN) + 1))
		ft_exe_env(_shell);
	else
		ft_exec_cmd(_shell);
	free(cmd_lower);
}
