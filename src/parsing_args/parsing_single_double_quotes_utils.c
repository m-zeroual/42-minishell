#include "parsing_single_double_quotes.h"

/**
 *  this function will be free the double pointer that you giving to him.
 */
void	free_double_pointer(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
}

/**
 *  this function return the index of the first (single | double)
 *  quotes character in the string and set separ to this character.
 *  EXAMPLE:
 *      str = `ls -"'a'" -'l'`  ==> separ = `"` | return 4
 */
int	get_separator(char *str, char *separ)
{
	int	i;

	i = -1;
	if (!str || !*str)
		return (0);
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			*separ = str[i];
			return (i);
		}
	}
	return (i);
}

/**
 *  this function takes double pointer and trim all strings from it,
 *	and return a double pointer without any Extra spaces.
 *  EXAMPLE:
 *    {"ls", "  ", "-a", "   -l  ", "-R ", " "}  ==>  {"ls", "-a", "-l", "-R"}
 *
 */
char	**get_list_without_spaces(char **dpointer, int len)
{
	char	**result;
	char	*tmp;
	int		i;
	int		j;

	if (!dpointer || !*dpointer)
		return (0);
	result = ft_calloc(len + 1, sizeof(*result));
	if (!result)
		return (free_double_pointer(dpointer), NULL);
	j = 0;
	i = -1;
	while (dpointer[++i])
	{
		tmp = ft_strtrim(dpointer[i], " \t\n");
		if (tmp)
		{
			result[j++] = ft_strdup(tmp);
			free(tmp);
		}
	}
	return (free_double_pointer(dpointer), result);
}
