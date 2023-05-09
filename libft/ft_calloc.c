/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:02:23 by esalim            #+#    #+#             */
/*   Updated: 2023/05/09 16:35:34 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*dest;

	dest = (char *)malloc(count * size);
	if (!dest)
		return (0);
	ft_bzero(dest, count * size);
	return (dest);
}
