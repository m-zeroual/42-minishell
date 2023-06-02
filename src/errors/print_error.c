/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:19:50 by esalim            #+#    #+#             */
/*   Updated: 2023/05/30 18:44:37 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/errors.h"

void	print_error(char *file, char *message)
{
	(void)file;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(message, 2);
}

void	p_error(char *str)
{
	(void)str;
	ft_printf("minishell: syntax error\n");
	// static int  i;
	// char        *text;
	// text = "minishell: syntax error near unexpected token `";
	// if (!i)
	// {
	//     ft_putstr_fd(text, 2);
	//     i = 1;
	// }
	// ft_putstr_fd(str, 2);
	// if (str[0] == '\'')
	//     i = 0;
}
