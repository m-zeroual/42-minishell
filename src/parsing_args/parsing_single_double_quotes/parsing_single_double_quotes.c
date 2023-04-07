#include "../../../includes/parsing_single_double_quotes.h"

/**
 *  just checking the conditions
 */
int	check_conditions(char **dest, char **line, int *a, int j)
{
	if (!*a && **line == '|' && (*line)++)
		(*dest)[j++] = PIPE;
	else if (!*a && **line == '<' && (*line)++)
		(*dest)[j++] = INPUT_REDIRECT;
	else if (!*a && **line == '>' && (*line)++)
		(*dest)[j++] = OUTPUT_REDIRECT;
	else
		(*dest)[j++] = *((*line)++);
	return (j);
}

/**
 *  this function takes dest and line as argemments and fill if using line 
 *  return j index of dest.
 */
int	set_dest(char **dest, char **line, int *a, int j)
{
	int		separ_index;
	char	separator;

	separ_index = get_separator(*line, &separator);
	while (separ_index-- > 0 && **line)
	{
		if (!*a && **line == ' ')
			(*dest)[j++] = SEPARATOR;
		j = check_conditions(dest, line, a, j);
		if (!*a && *(*line - 1) == ' ' && **line != ' ')
			(*dest)[j++] = SEPARATOR;
	}
	if (**line && **line == separator && (*line)++)
		*a = !*a;
	while (**line && **line != separator)
	{
		if (!*a && **line == ' ')
			(*dest)[j++] = SEPARATOR;
		j = check_conditions(dest, line, a, j);
		if (!*a && **(line - 1) == ' ' && **line != ' ')
			(*dest)[j++] = SEPARATOR;
	}
	if (**line && **line == separator && (*line)++)
		*a = !*a;
	return (j);
}

/**
 *  hundle the line by removing double and single quotes and return string
 *  separed by 3 ascii characher using set_dest() function. 
 *  EXAMPLE:
 *      "p""w"'d'  ==> "`pwd`"
 *      ""l's' "-a" '-l' ""-R  =>  "`ls` `-a` `-l` `-R`"
 */
char	*hundle_line(char *line)
{
	char	*dest;
	int		j;
	int		a;
	char	*tmp;

	if (!line || !*line)
		return (0);
	dest = ft_calloc((ft_strlen(line) * 2) + 1, sizeof(*dest));
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
		printf("Error : you messing a separator\n");
	dest[j] = 0;
	free(tmp);
	tmp = ft_strdup(dest);
	free(dest);
	return (tmp);
}

/**
 *  split the string returned by hundle_line() function using 3 ascii character
 *  and trim all space in right and left side of each string and retun double
 *  pointer that pointing to the first string.
 *  ft_split(str, 3);
 *  ft_strtrim(str, " \t\n");
 *  EXAMPLE:
 *      "`ls` `-a` `-l` `-R`"  =>  {"ls", "-a", "-l", "-R"}
 */
char	**split_line(char *line)
{
	char	*line_after_hundling;
	char	*tmp;
	char	**str;
	int		i;
	int		len;

	line_after_hundling = hundle_line(line);
	if (!line_after_hundling)
		return (0);
	str = ft_split(line_after_hundling, SEPARATOR);
	free(line_after_hundling);
	if (!str)
		return (0);
	i = -1;
	len = 0;
	while (str[++i])
	{
		tmp = ft_strtrim(str[i], " \t\n");
		if (tmp)
		{
			len++;
			free(tmp);
		}
	}
	return (get_list_without_spaces(str, len));
}

/**
 *  the function will remove all extra space in left and right of args and
 *  after that spliting him by using split_line() function, and return the
 *  result of last funtion.
 *  `   "ls" "-a" "-l" -R   ` ==> `"ls" "-a" "-l" -R`
 */
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
