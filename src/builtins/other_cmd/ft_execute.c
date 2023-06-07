/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeroual <mzeroual@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:11:20 by mzeroual          #+#    #+#             */
/*   Updated: 2023/06/07 15:11:22 by mzeroual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_is_builtins(char *str)
{
	if (!ft_strncmp(str, EX, ft_strlen(EX) + 1) \
		|| !ft_strncmp(str, UNSET, ft_strlen(UNSET) + 1) \
		|| !ft_strncmp(str, CD, ft_strlen(CD) + 1)
		|| !ft_strncmp(str, PWD, ft_strlen(PWD) + 1)
		|| !ft_strncmp(str, EN, ft_strlen(EN) + 1)
		|| !ft_strncmp(str, ECHO, ft_strlen(ECHO) + 1)
		|| !ft_strncmp(str, EXIT, ft_strlen(EXIT) + 1))
		return (1);
	return (0);
}

char	*ft_path(t_shell *_shell)
{
	char	*cmd;

	cmd = 0;
	if (!_shell->pipes->content->commands)
		return (NULL);
	if (ft_is_builtins(_shell->pipes->content->commands[0]))
		return (ft_strdup(_shell->pipes->content->commands[0]));
	if (!ft_strchr(_shell->pipes->content->commands[0], '/'))
	{
		cmd = ft_getenv(_shell->env, "PATH");
		if (!cmd)
		{
			ft_printf("minshell: %s: %s\n", \
_shell->pipes->content->commands[0], "No such file or directory");
			_shell->status = 127;
			return (0);
		}
	}
	else
		cmd = ft_strdup(_shell->pipes->content->commands[0]);
	return (cmd);
}

static char	*next(t_shell *_shell, char **path, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path_cmd;

	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		path_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(path_cmd, F_OK))
		{
			if (!access(path_cmd, X_OK))
				return (path_cmd);
			ft_printf("minishell: %s%s: %s\n", path[i], cmd, \
			"Permission denied");
			return (free_split(path), _shell->status = 1, NULL);
		}
		free(path_cmd);
	}
	return (print_error2(_shell, cmd, 127, "command not found"), NULL);
}

char	*check_error(t_shell *_shell, char **path, char *cmd)
{
	char	*path_cmd;

	if (!ft_strchr(cmd, '/'))
	{
		path_cmd = next(_shell, path, cmd);
		if (!path_cmd)
			return (free_split(path), NULL);
		return (path_cmd);
	}
	else if (!access(cmd, F_OK) && cmd[ft_strlen(cmd) - 1] == '/')
		return (free_split(path), print_error2(_shell, cmd, 126, \
		"is a directory"), NULL);
	else if (cmd[ft_strlen(cmd) - 1] == '/')
	{
		cmd[ft_strlen(cmd) - 1] = '\0';
		if (!access(cmd, F_OK))
			return (free_split(path), print_error2(_shell, cmd, 126, \
			"Not a directory"), NULL);
	}
	else if (!access(cmd, F_OK) && !access(cmd, X_OK))
		return (free_split(path), ft_strdup(cmd));
	return (free_split(path), print_error2(_shell, cmd, 127, \
	"No such file or directory"), NULL);
}

char	*ft_join_cmd(t_shell *_shell)
{
	char	**path;
	char	*cmd;

	cmd = ft_path(_shell);
	if (ft_is_builtins(cmd))
		return (cmd);
	path = ft_split(cmd, ':');
	free(cmd);
	cmd = _shell->pipes->content->commands[0];
	return (check_error(_shell, path, cmd));
}
