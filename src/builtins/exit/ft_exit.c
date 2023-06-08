/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:00:27 by mzeroual          #+#    #+#             */
/*   Updated: 2023/06/08 21:55:01 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <inttypes.h>

int	ft_chr_to_int(const char *str, int *print)
{
	int				i;
	__int128		result;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-' )
			sign *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		result = (result * 10) + str[i] - 48;
		if (result > 9223372036854775807)
			return (*print = 1, 255);
		i++;
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (*print = 1, 255);
	return (result * sign);
}

int	exit_with_args(char **command)
{
	int	print_error;
	int	num;
	int	j;

	print_error = 0;
	j = -1;
	if (!command[2])
	{
		num = ft_chr_to_int(command[1], &print_error);
		if (print_error)
			return (ft_printf("minishell: %s: %s: numeric argument required\n" \
, command[0], command[1]), 255);
		else
			return (num % 256);
	}
	else
	{
		while (command[1][++j])
		{
			if (!ft_isdigit(command[1][j]))
				return (ft_printf("minishell: %s: %s: \
numeric argument required\n", command[0], command[1]), 255);
		}
		return (ft_printf("minishell: %s: too many arguments\n", command[0]), 1);
	}
}

int	ft_exit(t_shell *_shell)
{
	ft_printf("exit\n");
	if (!_shell->pipes->content->commands[1])
		return (_shell->status);
	else
		return (exit_with_args(_shell->pipes->content->commands));
}
