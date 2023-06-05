/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_single_double_quotes_tools.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:01:26 by esalim            #+#    #+#             */
/*   Updated: 2023/06/05 12:05:05 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing_single_double_quotes.h"

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

void	switch_a(char **line, int *a, char separator)
{
	if (**line && **line == separator && (*line)++)
		*a = !*a;
}
