/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:48:28 by esalim            #+#    #+#             */
/*   Updated: 2023/06/05 17:48:44 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, size_t n)
{
	char	*dest;
	size_t	i;

	i = -1;
	if (!str || !*str || n < 1)
		return (0);
	dest = malloc(n * sizeof(char));
	if (!dest)
		return (0);
	while (++i < n && str[i])
		dest[i] = str[i];
	dest[i] = 0;
	return (dest);
}
