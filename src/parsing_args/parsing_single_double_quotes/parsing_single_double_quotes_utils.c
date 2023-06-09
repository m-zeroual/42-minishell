/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_single_double_quotes_utils.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:30:40 by esalim            #+#    #+#             */
/*   Updated: 2023/06/05 17:39:40 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing_single_double_quotes.h"

void	free_double_pointer(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
}

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

int	is_only_three(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != 3)
			return (0);
	return (1);
}

int	get_lenght_of_list_without_three(char **str)
{
	int	len;
	int	i;

	i = -1;
	len = 0;
	while (str[++i])
		if (!is_only_three(str[i]))
			len++;
	return (len);
}

char	**get_list_without_three(char **dpointer, int len)
{
	char	**result;
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
		if (!is_only_three(dpointer[i]))
			result[j++] = ft_strdup(dpointer[i]);
	free_double_pointer(dpointer);
	if (!j)
		return (free(result), NULL);
	return (result);
}
