/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:55:02 by esalim            #+#    #+#             */
/*   Updated: 2023/06/05 11:57:41 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/expanding.h"

char	*get_value(t_shell *shell, char **line)
{
	char	*val;
	char	*str;
	char	*tmp;

	tmp = *line;
	val = get_variable_name(line);
	if (!val)
		return (0);
	str = ft_getenv(shell->env, val);
	free(val);
	if (!str)
	{
		if (ft_check_var_exist(shell->env, val) == -1)
			return (0);
		str = ft_strdup("");
	}
	replace_chars(str);
	if ((shell->separator == '"' && shell->isopen) || ft_isalnum(*(tmp - 2)))
		search_and_replace(str, ' ', -9);
	val = handle_line(shell, str);
	free(str);
	str = ft_strtrim(val, " \004\004");
	free(val);
	return (str);
}

char	*get_variable_name(char **line)
{
	int		j;
	char	*var;
	char	*tmp;

	j = 0;
	while ((*line)[j] && (ft_isalnum((*line)[j]) || (*line)[j] == '_'))
		j++;
	var = ft_calloc(j + 1, sizeof(*var));
	if (!var)
		return (0);
	j = 0;
	while (**line && (ft_isalnum(**line) || **line == '_'))
		var[j++] = *((*line)++);
	if (!*var)
		return (free(var), NULL);
	tmp = ft_strdup(var);
	free(var);
	return (tmp);
}
