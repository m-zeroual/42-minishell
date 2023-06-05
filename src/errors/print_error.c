/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:19:50 by esalim            #+#    #+#             */
/*   Updated: 2023/06/05 17:39:40 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/errors.h"

int	print_error(char *file, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(message, 2);
	return (1);
}
