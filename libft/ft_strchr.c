/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:53:18 by esalim            #+#    #+#             */
/*   Updated: 2023/04/05 23:15:43 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

    i = -1;
    if (!str || !*str)
        return (0);
	while (str[++i])
		if (str[i] == (unsigned char)c)
			return ((char *)str + i);
	return (0);
}
