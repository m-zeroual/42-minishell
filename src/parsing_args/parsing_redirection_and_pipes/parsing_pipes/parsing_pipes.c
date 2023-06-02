/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:49:23 by esalim            #+#    #+#             */
/*   Updated: 2023/06/01 16:59:59 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	free_pipe(char ***p)
{
	int	i;

	if (!p)
		return ;
	i = -1;
	while (p[++i])
		free_double_pointer(p[i]);
	free(p);
}

char	**set_pipes(char **commands, int *j)
{
	char	**str;
	int		s;

	if (!commands)
		return (NULL);
	str = ft_calloc(get_number_of_commands(commands, *j) + 1, sizeof(char *));
	if (!str)
		return (NULL);
	s = 0;
	while (commands[*j])
	{
		if (commands[*j] && commands[*j][0] == PIPE && ++(*j))
			break ;
		str[s++] = ft_strdup(commands[(*j)++]);
	}
	str[s++] = 0;
	if (!str[0])
		return (free(str), NULL);
	return (str);
}

static char	***split_into_pipes(char **commands)
{
	char	***pipes;
	int		pipes_len;
	int		i;
	int		j;

	if (!commands)
		return (NULL);
	pipes_len = get_number_of_pipe(commands);
	pipes = ft_calloc(pipes_len + 2, sizeof(char **));
	if (!pipes)
		return (NULL);
	i = -1;
	j = 0;
	while (++i <= pipes_len)
	{
		pipes[i] = set_pipes(commands, &j);
		if (!pipes[i])
			return (free_pipe(pipes), NULL);
		if (pipes[i] && !pipes[i][0])
			return (free_pipe(pipes), NULL);
	}
	return (pipes);
}

void	set_one_to_null_pointer(char **commands)
{
	int	i;

	if (!commands)
		return ;
	i = -1;
	while (commands[++i])
		if (commands[i][0] == 1)
			commands[i][0] = 0;
}

t_list	*parsing_pipes(t_shell *shell, char **commands)
{
	t_list		*pipes;
	t_content	*content;
	char		***p;
	int			i;
	int			len;

	if (!commands)
		return (NULL);
	p = split_into_pipes(commands);
	if (!p)
	{
		ft_printf("minishell: syntax error 12\n");
		shell->status = 2;
		return (NULL);
	}
	i = 0;
	pipes = NULL;
	while (p[i])
	{
		content = ft_calloc(2, sizeof(*content));
		if (!content)
			return (free_pipe(p), NULL);
		if (!parsing_redirection(shell, content, p[i]))
			return (free_pipe(p), free(content), NULL);
		len = get_lenght_of_list_without_three(p[i]);
		content->commands = get_list_without_three(p[i], len);

		set_one_to_null_pointer(content->commands);
		ft_lstadd_back(&pipes, ft_lstnew(content));
		i++;
	}
	return (free(p), pipes);
}
