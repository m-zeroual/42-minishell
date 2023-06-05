/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_single_double_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:29:29 by esalim            #+#    #+#             */
/*   Updated: 2023/06/05 12:16:05 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing_single_double_quotes.h"

void	append_to_dest(t_shell *shell, char **dest, char **line, int *j)
{
	if (shell->isheredoc && shell->separator && shell->isopen)
	{
		(*dest)[(*j)++] = -42;
		shell->isheredoc = 0;
		shell->check = 0;
	}
	(*dest)[(*j)++] = *((*line)++);
	if (**line)
	{
		shell->isheredoc = 0;
		shell->check = 0;
	}
}

int	set_dest(t_shell *shell, char **dest, char **line, int *a)
{
	int		separ_index;
	char	separator;

	separ_index = get_separator(*line, &separator);
	while (separ_index-- > 0 && **line && **line != separator)
	{
		if (!*a && **line == ' ')
			(*dest)[shell->index++] = SEPARATOR;
		shell->index = check_conditions(shell, dest, line);
		if (!*a && *(*line - 1) == ' ' && **line != ' ')
			(*dest)[shell->index++] = SEPARATOR;
	}
	switch_a(line, a, separator);
	check_errors(dest, line, &shell->index);
	while (**line && **line != separator)
	{
		if (!*a && **line == ' ')
			(*dest)[shell->index++] = SEPARATOR;
		shell->separator = separator;
		shell->isopen = *a;
		shell->index = check_conditions(shell, dest, line);
		if (!*a && **(line - 1) == ' ' && **line != ' ')
			(*dest)[shell->index++] = SEPARATOR;
	}
	return (switch_a(line, a, separator), shell->index);
}

char	*handle_line(t_shell *shell, char *line)
{
	char	*dest;
	int		a;
	char	*tmp;

	if (!line || !*line)
		return (0);
	dest = ft_calloc((ft_strlen(line) * 100) + 1, sizeof(*dest));
	if (!dest)
		return (NULL);
	shell->index = 0;
	a = 0;
	dest[shell->index++] = SEPARATOR;
	while (*line)
	{
		shell->separator = 0;
		shell->isopen = a;
		shell->index = set_dest(shell, &dest, &line, &a);
	}
	if (!a && !*line)
		dest[shell->index++] = SEPARATOR;
	if (a && print_error("", "unexpected EOF while looking for matching\n"))
		return (free(dest), shell->status = 2, NULL);
	return (tmp = ft_strdup(dest), free(dest), a = 0, tmp);
}

char	**split_line(t_shell *shell, char *line)
{
	char	*line_after_handling;
	char	**str;
	char	*tmp_line;

	tmp_line = line;
	line_after_handling = handle_line(shell, line);
	free(tmp_line);
	if (!line_after_handling)
		return (0);
	replace_chars_rev(line_after_handling);
	str = ft_split(line_after_handling, SEPARATOR);
	free(line_after_handling);
	if (!str)
		return (0);
	return (str);
}

char	**parsing_single_double_quotes(t_shell *shell, char *args)
{
	char	*line;

	if (!args)
		return (0);
	shell->isheredoc = 0;
	shell->check = 0;
	line = ft_strtrim(args, " \t\n");
	if (!line)
		return (0);
	return (split_line(shell, line));
}
