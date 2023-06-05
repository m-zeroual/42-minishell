/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:10:59 by esalim            #+#    #+#             */
/*   Updated: 2023/06/05 12:11:56 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing_single_double_quotes.h"

void	check_errors(char **dest, char **line, int *index)
{
	if ((*index == 1 && ((!ft_strncmp((*line) - 1, "\"\"\0", 3) \
		|| !ft_strncmp((*line) - 1, "''", 3)) \
		|| (!ft_strncmp((*line) - 1, "\"\" ", 3) \
		|| !ft_strncmp((*line) - 1, "'' ", 3)))) \
		|| !ft_strncmp((*line) - 2, " \"\" ", 4) \
		|| !ft_strncmp((*line) - 2, " '' ", 4) \
		|| !ft_strncmp((*line) - 2, " \"\"", 4) \
		|| !ft_strncmp((*line) - 2, " ''", 4))
		(*dest)[(*index)++] = 1;
}

int	check_conditions(t_shell *shell, char **dest, char **line)
{
	int			j;

	j = shell->index;
	if ((shell->separator == '"' || !shell->isopen) \
			&& **line == '$' && *((*line) + 1) && (*line)++)
		expanding(shell, dest, line, &j);
	else if (!shell->isopen && ft_strchr("|<>", **line))
		check_pipe_redir(shell, line, dest, &j);
	else if (!shell->isopen && (**line == ' ' || **line == '\t') && (*line)++)
		(*dest)[j++] = SEPARATOR;
	else
		append_to_dest(shell, dest, line, &j);
	return (j);
}

void	check_pipe_redir(t_shell *shell, char	**line, char **dest, int *j)
{
	if (!shell->isopen && **line == '|' && (*line)++)
	{
		(*dest)[(*j)++] = SEPARATOR;
		(*dest)[(*j)++] = PIPE;
		(*dest)[(*j)++] = SEPARATOR;
		shell->isheredoc = 0;
		shell->check = 0;
	}
	else if (!shell->isopen && **line == '<' && (*line)++)
	{
		(*dest)[(*j)++] = SEPARATOR;
		(*dest)[(*j)++] = INPUT_REDIRECT;
		(*dest)[(*j)++] = SEPARATOR;
		if (**line == '<')
			shell->isheredoc = 1;
		shell->check = 1;
	}
	else if (!shell->isopen && **line == '>' && (*line)++)
	{
		(*dest)[(*j)++] = SEPARATOR;
		(*dest)[(*j)++] = OUTPUT_REDIRECT;
		(*dest)[(*j)++] = SEPARATOR;
		shell->check = 1;
		shell->isheredoc = 0;
	}
}
