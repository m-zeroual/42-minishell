/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:07:06 by esalim            #+#    #+#             */
/*   Updated: 2023/04/18 23:07:06 by mzeroual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strtrim(char const *s, char const *set)
{
	char    *dest;
	size_t  i;
    size_t  len;

    i = -1;
	if (!s || !*s)
		return (0);
	while (ft_strchr((char *)set, *s))
		s++;
	len = ft_strlen(s);
	while (ft_strchr((char *)set, s[len]))
		len--;
    if (len < 1)
        return (0);
	dest = ft_calloc(len + 1, sizeof *dest);
	if (!dest)
		return (0);
	while (++i <= len)
		dest[i] = s[i];
	return (dest);
}

