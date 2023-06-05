/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_single_double_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:29:29 by esalim            #+#    #+#             */
/*   Updated: 2023/06/05 10:41:56 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing_single_double_quotes.h"

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

void	search_and_replace(char *src, char search, char replace)
{
	int	i;

	if (!src)
		return ;
	i = -1;
	while (src[++i])
		if (src[i] == search)
			src[i] = replace;
}

void	replace_chars(char	*str)
{
	search_and_replace(str, '"', -3);
	search_and_replace(str, '\'', -2);
	search_and_replace(str, '>', -4);
	search_and_replace(str, '<', -5);
	search_and_replace(str, '|', -6);
	search_and_replace(str, '$', -7);
}

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

int	check_conditions(t_shell *shell, char **dest, char **line)
{
	static int	isheredoc;
	static int	check;
	int			j;

	j = shell->index;
	if ((shell->separator == '"' || !shell->isopen) \
			&& **line == '$' && *((*line) + 1) && (*line)++)
	{
		if (check)
		{
			check = 0;
			if (isheredoc)
			{
				isheredoc = 0;
				(*dest)[j++] = '$';
				if (shell->separator && shell->isopen)
					(*dest)[j++] = -42;
			}
			else
			{
				(*dest)[j++] = '$';
				char	*var_name = get_variable_name(line);
				int	q = 0;
				while (var_name[q])
					(*dest)[j++] = var_name[q++];
				free(var_name);
				(*dest)[j++] = -22;
			}
		}
		else if (((shell->separator == '"' && shell->isopen) \
				|| (!shell->separator && !shell->isopen)) \
				&& **line && **line == '?')
		{
			char *str = ft_itoa(shell->status);
			(*line)++;
			int i = 0;
			while (str[i])
				(*dest)[j++] = str[i++];
			free(str);
		}
		else if (((shell->separator == '"' && shell->isopen) \
				|| (!shell->separator && !shell->isopen)) \
				&& (ft_isalpha(**line) || **line == '_'))
			expanding_variables(shell, dest, line, &j);
		else if (ft_isdigit(**line) || ft_strchr("$@*#-", **line))
			(*line)++;
		else
			(*dest)[j++] = '$';
	}
	else if (!shell->isopen && **line == '|' && (*line)++)
	{
		(*dest)[j++] = SEPARATOR;
		(*dest)[j++] = PIPE;
		(*dest)[j++] = SEPARATOR;
		isheredoc = 0;
		check = 0;
	}
	else if (!shell->isopen && **line == '<' && (*line)++)
	{
		(*dest)[j++] = SEPARATOR;
		(*dest)[j++] = INPUT_REDIRECT;
		(*dest)[j++] = SEPARATOR;
		if (**line == '<')
			isheredoc = 1;
		check = 1;
	}
	else if (!shell->isopen && **line == '>' && (*line)++)
	{
		(*dest)[j++] = SEPARATOR;
		(*dest)[j++] = OUTPUT_REDIRECT;
		(*dest)[j++] = SEPARATOR;
		check = 1;
		isheredoc = 0;
	}
	else if (!shell->isopen && (**line == ' ' || **line == '\t') && (*line)++)
		(*dest)[j++] = SEPARATOR;
	else
	{
		if (isheredoc && shell->separator && shell->isopen)
		{
			(*dest)[j++] = -42;
			isheredoc = 0;
			check = 0;
		}
		(*dest)[j++] = *((*line)++);
		if (**line)
		{
			isheredoc = 0;
			check = 0;
		}
	}
	return (j);
}

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

void	switch_a(char **line, int *a, char separator)
{
	if (**line && **line == separator && (*line)++)
		*a = !*a;
}

int		set_dest(t_shell *shell, char **dest, char **line, int *a)
{
	int		separ_index;
	char	separator;

	separ_index = get_separator(*line, &separator);
	while (separ_index-- > 0 && **line && **line != separator)
	{
		if (!*a && **line == ' ')
			(*dest)[shell->index++] = SEPARATOR;
		shell->separator = 0;
		shell->isopen = *a;
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
		shell->index = set_dest(shell, &dest, &line, &a);
	if (!a && !*line)
		dest[shell->index++] = SEPARATOR;
	if (a)
	{
		ft_printf("minishell: unexpected EOF while looking for matching\n");
		return (free(dest), shell->status = 2, NULL);
	}
	tmp = ft_strdup(dest);
	return (free(dest), a = 0, tmp);
}

void	replace_chars_rev(char *str)
{
	search_and_replace(str, -3, '"');
	search_and_replace(str, -2, '\'');
	search_and_replace(str, -4, '>');
	search_and_replace(str, -5, '<');
	search_and_replace(str, -6, '|');
	search_and_replace(str, -7, '$');
	search_and_replace(str, -9, ' ');
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
	line = ft_strtrim(args, " \t\n");
	if (!line)
		return (0);
	return (split_line(shell, line));
}
