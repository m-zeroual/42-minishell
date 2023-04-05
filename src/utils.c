#include "../includes/main.h"

void ft_str_to_lower(char **path)
{
	int i;
	int j;

	i = 0;
	while (path[i])
	{
		j = 0;
		while (path[i][j])
		{
			path[i][j] = ft_tolower(path[i][j]);
			j++;
		}
		i++;
	}
}

int ft_get_index_reverse(char *str, char c)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i)
	{
		if (str[i] == c)
			return (i);
		i--;
	}
	return (0);
}
int ft_get_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

void free_split(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
