/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:18:30 by esalim            #+#    #+#             */
/*   Updated: 2022/10/18 17:47:19 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_base(long nbr, char *base, int islong, int *count)
{
	unsigned long	nb1;
	unsigned int	nb2;

	if (islong)
	{
		nb1 = nbr;
		if (nb1 >= 0 && nb1 < 16)
			ft_putchar(base[nb1], count);
		if (nb1 >= 16)
		{
			ft_putnbr_base(nb1 / 16, base, islong, count);
			ft_putnbr_base(nb1 % 16, base, islong, count);
		}
	}
	else
	{
		nb2 = nbr;
		if (nb2 >= 0 && nb2 < 16)
			ft_putchar(base[nb2], count);
		if (nb2 >= 16)
		{
			ft_putnbr_base(nb2 / 16, base, islong, count);
			ft_putnbr_base(nb2 % 16, base, islong, count);
		}
	}
}
