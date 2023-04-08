/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:38:08 by esalim            #+#    #+#             */
/*   Updated: 2023/04/08 23:23:41 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	size_t	len;

    if (!s1)
        return (0);
	len = ft_strlen((char *)s1) + 1;
	dest = (char *)malloc(len);
	if (!dest)
		return (0);
	ft_strlcpy(dest, (char *)s1, len);
	return (dest);
}
