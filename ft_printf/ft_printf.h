/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:41:24 by esalim            #+#    #+#             */
/*   Updated: 2022/10/18 18:11:28 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

char	*ft_strchr(const char *str, int c);
void	ft_putchar(char c, int *count);
void	ft_putstr(char *str, int *count);
void	ft_putnbr(long nbr, int isunsigned, int *count);
void	ft_putnbr_base(long nbr, char *base, int islong, int *count);
int		ft_printf(const char *str, ...);

#endif
