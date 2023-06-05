/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:14:59 by esalim            #+#    #+#             */
/*   Updated: 2023/06/05 15:18:26 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	replace_symbols(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		if (ft_strchr(" \"'><|", str[i]))
			str[i] -= 127;
}

void	replace_symbols_rev(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		if (str[i] < 0)
			str[i] += 127;
}

int	check_character(char *str, int c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

void	remove_character(char *str)
{
	char	*dest;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (str[i])
		if (ft_isprint(str[i++]))
			len++;
	dest = ft_calloc(len + 1, 1);
	if (!dest)
		return ;
	i = -1;
	len = 0;
	while (str[++i])
		if (ft_isprint(str[i]))
			dest[len++] = str[i];
	len = ft_strlen(str);
	ft_bzero(str, len);
	ft_strlcpy(str, dest, len + 1);
	free(dest);
}

void	free_t_redirect(t_redirect *redirect)
{
	unsigned char	i;

	if (!redirect)
		return ;
	i = -1;
	while (redirect[++i].file)
		free(redirect[i].file);
	ft_bzero(redirect, sizeof(*redirect));
	free(redirect);
}
