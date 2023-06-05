/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection_tools.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:46:23 by esalim            #+#    #+#             */
/*   Updated: 2023/06/05 17:39:40 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	skip_commands(char **commands, int *j)
{
	while (commands[*j] && commands[*j][0] != INPUT_REDIRECT \
		&& commands[*j][0] != OUTPUT_REDIRECT)
	{
		if (commands[*j][0] && commands[*j][0] == PIPE)
			return (1);
		(*j)++;
	}
	return (0);
}

int	redirect_len(char **commands, int *j, char c, char *print_c)
{
	int	len;
	int	two;
	int	max;

	len = 0;
	two = 0;
	max = 3;
	if (print_c && print_c[0] == '<')
		max = 4;
	while (commands[*j] && commands[*j][0] == c)
	{
		len++;
		if (len > max && two < max - 1 && ++two)
			ft_printf("minishell: syntax error\n");
		ft_memset(commands[*j], 3, ft_strlen(commands[*j]));
		(*j)++;
	}
	if (!commands[*j] && len && len < 4)
	{
		ft_printf("minishell: syntax error\n");
		len = 4;
	}
	return (len);
}

int	check_redirection_error(char **cmds, int *j, int len)
{
	int	two;

	two = 0;
	if (len != 0 && cmds[(*j)] && cmds[(*j)][0] < 32 \
		&& cmds[*j][0] > 1 && two++ < 2)
	{
		len = 200;
		ft_printf("minishell: syntax error\n");
		(*j)++;
	}
	if (len == 200)
		return (200);
	return (0);
}

int	for_each_command(t_redirect *redirection, char **commands, int *i, int *j)
{
	int	input_len;
	int	output_len;

	input_len = 0;
	output_len = 0;
	if (skip_commands(commands, j))
		return (2);
	input_len = redirect_len(commands, j, INPUT_REDIRECT, "<");
	if (input_len > 3 || check_redirection_error(commands, j, input_len))
		return (0);
	if (input_len < 4 && commands[*j] && commands[*j][0] == 1)
		return (print_error("", "No such file or directory\n"), 4);
	if (input_len != 0 && commands[*j] && commands[*j][0] != OUTPUT_REDIRECT)
		set_redirections(&redirection[(*i)++], commands[(*j)++], 1, input_len);
	output_len = redirect_len(commands, j, OUTPUT_REDIRECT, ">");
	if (output_len < 3 && commands[*j] && commands[*j][0] == 1)
		return (print_error("", "No such file or directory\n"), 4);
	if (output_len > 2 || check_redirection_error(commands, j, output_len))
		return (0);
	if (output_len != 0 && commands[*j] && commands[*j][0] != INPUT_REDIRECT)
		set_redirections(&redirection[(*i)++], commands[(*j)++], 0, output_len);
	return (1);
}

void	init_t_redirect(t_redirect *dest, t_redirect *src)
{
	dest->file = ft_strdup(src->file);
	dest->is_input = src->is_input;
	dest->is_output = src->is_output;
	dest->is_here_doc = src->is_here_doc;
	dest->is_append = src->is_append;
}
