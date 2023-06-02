/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:38:44 by esalim            #+#    #+#             */
/*   Updated: 2023/06/02 16:07:01 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	set_redirections(t_redirect *red, char *str, char is_input, int len)
{
	red->file = ft_strtrim(str, " \t");
	ft_printf("red->file ==> [%p]\n", red->file);
	search_and_replace(red->file, -99, ' ');
	ft_memset(str, 3, ft_strlen(str));
	if (is_input)
	{
		red->is_input = 1;
		red->is_here_doc = 0;
		if (len == 2)
			red->is_here_doc = 1;
		red->is_append = 0;
		red->is_output = 0;
	}
	else
	{
		red->is_input = 0;
		red->is_here_doc = 0;
		red->is_append = 0;
		if (len == 2)
			red->is_append = 1;
		red->is_output = 1;
	}
}

t_redirect	*get_redirections(t_shell *shell, char **commands)
{
	t_redirect	*redirection;
	int			i;
	int			len;
	int			j;
	int			res;

	if (!commands)
		return (NULL);
	i = -1;
	len = 0;
	while (commands[++i])
		if (commands[i][0] == INPUT_REDIRECT || commands[i][0] == OUTPUT_REDIRECT)
			len++;
	redirection = ft_calloc(len + 1, sizeof(*redirection));
	if (!redirection)
		return (NULL);
	i = 0;
	j = 0;
	while (commands[j])
	{
		res = for_each_command(redirection, commands, &i, &j);
		if (!res || res == 4)
		{
			free(redirection);
			shell->status = 2;
			if (res == 4)
				shell->status = 1;
			return (NULL);
		}
		if (res == 2)
			break ;
	}
	return (redirection);
}

t_redirect	*get_input_redirections(t_redirect *redirections)
{
	unsigned char	i;
	t_redirect		*input;
	unsigned char	len;

	i = 0;
	len = 0;
	if (!redirections)
		return (NULL);
	while (redirections[i].file)
		if (redirections[i++].is_input == 1)
			len++;
	if (!len)
		return (NULL);
	input = ft_calloc(len + 1, sizeof(*input));
	if (!input)
		return (0);
	i = -1;
	len = 0;
	ft_printf("input ==> [%p]\n", input);
	while (redirections[++i].file)
		if (redirections[i].is_input == 1)
			init_t_redirect(&input[len++], &redirections[i]);
	return (input);
}

t_redirect	*get_output_redirections(t_redirect *redirections)
{
	unsigned char	i;
	t_redirect		*output;
	unsigned char	len;

	i = 0;
	len = 0;
	if (!redirections)
		return (NULL);
	while (redirections[i].file)
		if (redirections[i++].is_output == 1)
			len++;
	if (!len)
		return (NULL);
	output = ft_calloc(len + 1, sizeof(*output));
	if (!output)
		return (0);
	
	i = -1;
	len = 0;
	while (redirections[++i].file)
		if (redirections[i].is_output == 1)
			init_t_redirect(&output[len++], &redirections[i]);
	return (output);
}

int	parsing_redirection(t_shell *shell, t_content *content, char **redirections)
{
	t_redirect	*redirect;

	if (!redirections)
		return (0);
	redirect = get_redirections(shell, redirections);
	if (!redirect)
		return (0);
	content->output_redirections = get_output_redirections(redirect);
	ft_printf("content->output_redirections ==> [%p]\n", content->output_redirections);
	content->input_redirections = get_input_redirections(redirect);
	ft_printf("content->input_redirections ==> [%p]\n", content->input_redirections);
	free_t_redirect_2(redirect);
	return (1);
}
