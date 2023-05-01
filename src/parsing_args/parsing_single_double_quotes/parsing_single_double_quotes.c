#include "../../../includes/parsing_single_double_quotes.h"

char *get_variable_name(char **line)
{
	// int i = 0;
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

void	expanding_variables(char **dest, char **line, int *a, int *j, char separator)
{
	char	*var;
	char	*str;
	int		i;

	if (((separator == '"' && *a) || (!separator && !*a)) && (ft_isalpha(**line) || **line == '_'))
	{
		var = get_variable_name(line);
		if (!var)
			return ;
		printf("|hello|\n");
		str = getenv(var);
		if (!str)
			return ;
		i = 0;
		while (str[i])
			(*dest)[(*j)++] = str[i++];
		return ;
	}
	return ;
}

int	check_conditions(char **dest, char **line, int *a, int j, char separator)
{
	if (**line == '$' && (*line)++)
		expanding_variables(dest, line, a, &j, separator);
    else if (!*a && **line == '|' && (*line)++)
    {
        (*dest)[j++] = SEPARATOR;
		(*dest)[j++] = PIPE;
        (*dest)[j++] = SEPARATOR;
    }
	else if (!*a && **line == '<' && (*line)++)
    {
        (*dest)[j++] = SEPARATOR;
		(*dest)[j++] = INPUT_REDIRECT;
        (*dest)[j++] = SEPARATOR;
    }
	else if (!*a && **line == '>' && (*line)++)
    {
        (*dest)[j++] = SEPARATOR;
		(*dest)[j++] = OUTPUT_REDIRECT;
        (*dest)[j++] = SEPARATOR;
    }
	else if (!*a && (**line == ' ' || **line == '\t') && (*line)++)
        (*dest)[j++] = SEPARATOR;
    else
		(*dest)[j++] = *((*line)++);
	return (j);
}

int	set_dest(char **dest, char **line, int *a, int j)
{
	int		separ_index;
	char	separator;

	separ_index = get_separator(*line, &separator);
	while (separ_index-- > 0 && **line)
	{
		if (!*a && **line == ' ')
			(*dest)[j++] = SEPARATOR;
		j = check_conditions(dest, line, a, j, 0);
		if (!*a && *(*line - 1) == ' ' && **line != ' ')
			(*dest)[j++] = SEPARATOR;
	}
	if (**line && **line == separator && (*line)++)
		*a = !*a;
    if (**line && **line == separator && (*((*line) - 1)) == separator \
		&& ((*((*line) + 1)) == separator || !(*((*line) + 1))) \
		&& ((*((*line) - 2)) == ' ' || ((*((*line) - 2)) == 0)))
        (*dest)[j++] = 1;
	while (**line && **line != separator)
	{
		if (!*a && **line == ' ')
			(*dest)[j++] = SEPARATOR;
		j = check_conditions(dest, line, a, j, separator);
		if (!*a && **(line - 1) == ' ' && **line != ' ')
            (*dest)[j++] = SEPARATOR;
	}
	if (**line && **line == separator && (*line)++)
		*a = !*a;
	return (j);
}

char	*handle_line(char *line)
{
	char	*dest;
	int		j;
	int		a;
	char	*tmp;

	if (!line || !*line)
		return (0);
	dest = ft_calloc((ft_strlen(line) * 100) + 1, sizeof(*dest));
	if (!dest)
		return (NULL);
	tmp = line;
	j = 0;
	a = 0;
	dest[j++] = SEPARATOR;
	while (*line)
		j = set_dest(&dest, &line, &a, j);
	if (!a && !*line)
		dest[j++] = SEPARATOR;
	if (a)
		ft_putstr_fd("Error : you messing a separator\n", 2);
	dest[j] = 0;
	free(tmp);
	tmp = ft_strdup(dest);
	free(dest);
	return (tmp);
}

char	**split_line(char *line)
{
	char	*line_after_handling;
	char	**str;

	line_after_handling = handle_line(line);
	if (!line_after_handling)
		return (0);
	str = ft_split(line_after_handling, SEPARATOR);
	free(line_after_handling);
	if (!str)
		return (0);
	return (str);
}

char	**parsing_single_double_quotes(char *args)
{
	char	*line;

	if (!args || !*args)
		return (0);
	line = ft_strtrim(args, " \t\n");
	if (!line)
		return (0);
	return (split_line(line));
}
