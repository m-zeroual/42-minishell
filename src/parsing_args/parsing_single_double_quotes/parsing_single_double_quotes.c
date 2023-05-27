#include "../../../includes/parsing_single_double_quotes.h"

char	*get_variable_name(char **line)
{
	int j;
	char *var;
	char *tmp;

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

char	*ft_strendtrim(char const *s1)
{
	size_t	i;

	i = ft_strlen(s1);
	while (i && ft_strchr("  ", s1[i]))
		i--;
	return (ft_substr(s1, 0, i + 1));
}

char	*get_value(t_shell *shell, char **line, char separ, int *a)
{
	char	*val;
	char	*str;
	char	*tmp;

	tmp = *line;
	(void)a;
	(void)separ;
	val = get_variable_name(line);
	if (!val)
		return (0);
	str = ft_getenv(shell->env, val);
	// free(val);
	if (!str)
	{
		if (ft_check_var_exist(shell->env, val) == -1)
			return (0);
		str = ft_strdup("");
	}
	// else if (!str[0])
	// 	str[0] = -10;
	// if (separ == '"' && *a)
		// search_and_replace(str, ' ', -99);
	search_and_replace(str, '"', -3);
	search_and_replace(str, '\'', -2);
	search_and_replace(str, '>', -4);
	search_and_replace(str, '<', -5);
	search_and_replace(str, '|', -6);
	search_and_replace(str, '$', -7);
	// LEAKS HERE STR
	// str = ft_strendtrim(str);
	// printf("");
	// if ((separ == '"' && *a) || ft_isalnum(*(tmp - 2)))
		search_and_replace(str, ' ', -9);
	val = handle_line(shell, str);
	// free(str);
	str = ft_strtrim(val, "\004\004");
	// free(val);
	if (!str)
		return (0);
	return (str);
}

void	expanding_variables(t_shell *shell, char **dest, char **line, int *j, char separ, int *a)
{
	char	*str;
	int		i;

	i = 0;
	str = get_value(shell, line, separ, a);
	if (!str)
		return ;
	while (str[i])
		(*dest)[(*j)++] = str[i++];
	free(str);
}

char*	get_rediretion_name(char **line)
{
	char	*dest;
	int		i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] != ' ')
			break;
		i++;
	}
	while ((*line)[i] && (*line)[i] != ' ')
		i++;
	dest = ft_calloc(i + 1, sizeof(*dest));
	if (!dest)
		return (0);
	i = 0;
	while (**line)
	{
		if (**line != ' ')
			break;
		(*line)++;
	}
	i = 0;
	while (**line && **line != ' ')
		dest[i++] = *((*line)++);
	return (dest);
}

int		is_a_redirct(char *dest, int j)
{
	while (dest[--j])
	{
		if (dest[j] == INPUT_REDIRECT || dest[j] == OUTPUT_REDIRECT)
			return (1);
		else if (dest[j] != SEPARATOR)
			return (0);
	}
	return (0);
}

int		check_conditions(t_shell *shell, char **dest, char **line, int *a, int j, char separator)
{
	static int isheredoc;
	static int check;

	if ((separator == '"' || !*a) && **line == '$' && *((*line) + 1) && (*line)++)
	{
		if (check)
		{
			check = 0;
			if (isheredoc)
			{
				isheredoc = 0;
				(*dest)[j++] = '$';
				if (separator && *a)
					(*dest)[j++] = -42;
			}
			else
			{
				(*dest)[j++] = '$';
				(*dest)[j++] = -22;
			}
		}
		else if (((separator == '"' && *a) || (!separator && !*a)) && **line && **line == '?')
		{
			char *str = ft_itoa(shell->status);
			(*line)++;
			int i = 0;
			while (str[i])
				(*dest)[j++] = str[i++];
			free(str);
		}
		else if (((separator == '"' && *a) || (!separator && !*a)) && (ft_isalpha(**line) || **line == '_'))
			expanding_variables(shell, dest, line, &j, separator, a);
		else if (ft_isdigit(**line) || ft_strchr("$@*#-", **line))
			(*line)++;
		else
			(*dest)[j++] = '$';
	}
    else if (!*a && **line == '|' && (*line)++)
    {
        (*dest)[j++] = SEPARATOR;
		(*dest)[j++] = PIPE;
        (*dest)[j++] = SEPARATOR;
		isheredoc = 0;
		check = 0;
    }
	else if (!*a && **line == '<' && (*line)++)
    {
        (*dest)[j++] = SEPARATOR;
		(*dest)[j++] = INPUT_REDIRECT;
        (*dest)[j++] = SEPARATOR;
		if (**line == '<')
			isheredoc = 1;
		check = 1;
    }
	else if (!*a && **line == '>' && (*line)++)
    {
        (*dest)[j++] = SEPARATOR;
		(*dest)[j++] = OUTPUT_REDIRECT;
        (*dest)[j++] = SEPARATOR;
		check = 1;
		isheredoc = 0;
    }
	else if (!*a && (**line == ' ' || **line == '\t') && (*line)++)
        (*dest)[j++] = SEPARATOR;
    else
	{
		if (isheredoc && separator && *a)
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

int		set_dest(t_shell *shell, char **dest, char **line, int *a, int j)
{
	int		separ_index;
	char	separator;

	separ_index = get_separator(*line, &separator);
	while (separ_index-- > 0 && **line && **line != separator)
	{
		if (!*a && **line == ' ')
			(*dest)[j++] = SEPARATOR;
		j = check_conditions(shell, dest, line, a, j, 0);
		if (!*a && *(*line - 1) == ' ' && **line != ' ')
			(*dest)[j++] = SEPARATOR;
	}
	if (**line && **line == separator && (*line)++)
		*a = !*a;
	if ((j == 1 && ((!ft_strncmp((*line) - 1, "\"\"\0", 3) || !ft_strncmp((*line) - 1, "''", 3)) \
		||	(!ft_strncmp((*line) - 1, "\"\" ", 3) || !ft_strncmp((*line) - 1, "'' ", 3)))) \
		|| !ft_strncmp((*line) - 2, " \"\" ", 4) || !ft_strncmp((*line) - 2, " '' ", 4) \
		|| !ft_strncmp((*line) - 2, " \"\"", 4) || !ft_strncmp((*line) - 2, " ''", 4))
        (*dest)[j++] = 1;
	while (**line && **line != separator)
	{
		if (!*a && **line == ' ')
			(*dest)[j++] = SEPARATOR;
		j = check_conditions(shell, dest, line, a, j, separator);
		if (!*a && **(line - 1) == ' ' && **line != ' ')
            (*dest)[j++] = SEPARATOR;
	}
	if (**line && **line == separator && (*line)++)
		*a = !*a;
	return (j);
}

char	*handle_line(t_shell *shell, char *line)
{
	char	*dest;
	int		j;
	int		a;
	char	*tmp;

	if (!line || !*line)
		return (0);
	// expected error
	dest = ft_calloc((ft_strlen(line) * 100) + 1, sizeof(*dest));
	if (!dest)
		return (NULL);
	j = 0;
	a = 0;
	dest[j++] = SEPARATOR;
	while (*line)
		j = set_dest(shell, &dest, &line, &a, j);
	if (!a && !*line)
		dest[j++] = SEPARATOR;
	if (a)
	{
		ft_printf("minishell: unexpected EOF while looking for matching\n");
		free(dest);
		shell->status = 2;
		return (0);
	}
	tmp = ft_strdup(dest);
	free(dest);
	return (tmp);
}

char	**split_line(t_shell *shell, char *line)
{
	char	*line_after_handling;
	char	**str;
	char	*tmp_line;

	tmp_line = line;
	line_after_handling = handle_line(shell, line);
	// printf("|%s|\n", line_after_handling);
	free(tmp_line);
	if (!line_after_handling)
		return (0);
	search_and_replace(line_after_handling, -3, '"');
	search_and_replace(line_after_handling, -2, '\'');
	search_and_replace(line_after_handling, -4, '>');
	search_and_replace(line_after_handling, -5, '<');
	search_and_replace(line_after_handling, -6, '|');
	search_and_replace(line_after_handling, -7, '$');
	search_and_replace(line_after_handling, -9, ' ');
	search_and_replace(line_after_handling, -10, 0);
	str = ft_split(line_after_handling, SEPARATOR);
	free(line_after_handling);
	if (!str)
		return (0);
	return (str);
}

char	**parsing_single_double_quotes(t_shell *shell, char *args)
{
	char	*line;

	if (!args || !*args)
		return (0);
	line = ft_strtrim(args, " \t\n");
	if (!line)
		return (0);
	return (split_line(shell, line));
}
