/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeroual <mzeroual@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:07:05 by mzeroual          #+#    #+#             */
/*   Updated: 2023/06/07 15:07:07 by mzeroual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	print_var(char **exp, int i, int *j)
{
	while (exp[i][*j])
	{
		if (exp[i][*j] != '=')
			printf("%c", exp[i][(*j)++]);
		else
			break ;
	}
}

static void	print_value(char **exp, int i, int *j)
{
	while (exp[i][*j])
	{
		if (exp[i][*j] == '$' || exp[i][*j] == '"')
			printf("\\");
		printf("%c", exp[i][(*j)++]);
	}
}

void	ft_display_export(char **exp)
{
	int		i;
	int		j;

	i = 0;
	while (exp[i])
	{
		j = 0;
		printf("declare -x ");
		if (ft_strchr(exp[i], '='))
		{
			print_var(exp, i, &j);
			printf("%c\"", exp[i][j++]);
			print_value(exp, i, &j);
			printf("\"");
		}
		else
			print_var(exp, i, &j);
		printf("\n");
		i++;
	}
}
