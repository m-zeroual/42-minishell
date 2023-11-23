/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:42:47 by esalim            #+#    #+#             */
/*   Updated: 2022/10/18 17:43:53 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(long nb, int isunsigned, int *count)
{
	unsigned int	ui;

	if (!isunsigned)
	{
		if (nb < 0)
		{
			ft_putchar('-', count);
			nb *= -1;
		}
		if (nb > 9)
			ft_putnbr(nb / 10, isunsigned, count);
		ft_putchar(nb % 10 + 48, count);
	}
	else
	{
		ui = nb;
		if (ui > 9)
			ft_putnbr(ui / 10, isunsigned, count);
		ft_putchar(ui % 10 + 48, count);
	}
}
