/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:50:42 by esalim            #+#    #+#             */
/*   Updated: 2023/06/05 17:39:40 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/expanding.h"

void	expand_exit_status(t_shell *shell, char **dest, char **line, int *j)
{
	char	*str;
	int		i;

	str = ft_itoa(shell->status);
	(*line)++;
	i = 0;
	while (str[i])
		(*dest)[(*j)++] = str[i++];
	free(str);
}

void	expand_redirections(t_shell *shell, char **dest, char **line, int *j)
{
	char	*var_name;
	int		q;

	shell->check = 0;
	if (shell->isheredoc)
	{
		shell->isheredoc = 0;
		(*dest)[(*j)++] = '$';
		if (shell->separator && shell->isopen)
			(*dest)[(*j)++] = -42;
	}
	else
	{
		(*dest)[(*j)++] = '$';
		var_name = get_variable_name(line);
		q = 0;
		while (var_name[q])
			(*dest)[(*j)++] = var_name[q++];
		free(var_name);
		(*dest)[(*j)++] = -22;
	}
}

void	expanding(t_shell *shell, char **dest, char **line, int *j)
{
	if (shell->check)
		expand_redirections(shell, dest, line, j);
	else if (((shell->separator == '"' && shell->isopen) \
			|| (!shell->separator && !shell->isopen)) \
			&& **line && **line == '?')
		expand_exit_status(shell, dest, line, j);
	else if (((shell->separator == '"' && shell->isopen) \
			|| (!shell->separator && !shell->isopen)) \
			&& (ft_isalpha(**line) || **line == '_'))
		expanding_variables(shell, dest, line, j);
	else if (ft_isdigit(**line) || ft_strchr("$@*#-", **line))
		(*line)++;
	else
		(*dest)[(*j)++] = '$';
}

void	expanding_variables(t_shell *shell, char **dest, char **line, int *j)
{
	char	*str;
	int		i;

	i = 0;
	str = get_value(shell, line);
	if (!str)
		return ;
	while (str[i])
		(*dest)[(*j)++] = str[i++];
	free(str);
}
