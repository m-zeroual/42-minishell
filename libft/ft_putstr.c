/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 22:21:57 by esalim            #+#    #+#             */
/*   Updated: 2023/06/05 21:40:03 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char *s, int *count)
{
	int	i;

	i = 0;
	while (s[i])
		write(2, &s[i++], 1);
	*count += i;
}
