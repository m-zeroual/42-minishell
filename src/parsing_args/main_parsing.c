/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:20:54 by esalim            #+#    #+#             */
/*   Updated: 2023/06/06 22:59:19 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	setup_input_redirections(t_shell *_shell)
{
	t_content	*content;
	int			fd;
	int			i;

	content = _shell->pipes->content;
	if (!content->input_redirections)
	{
		if (_shell->i > 1)
			dup2(_shell->pipes->content->pipe_fds[0], 0);
		return (1);
	}
	i = -1;
	while (content->input_redirections[++i].file)
	{
		if (!content->input_redirections[i + 1].file \
			&& !content->input_redirections[i].is_here_doc)
		{
			fd = open(content->input_redirections[i].file, O_RDONLY, 0644);
			if (fd == -1 || dup2(fd, 0) == -1)
				return (close(fd), 0);
			close(fd);
			return (1);
		}
	}
	return (1);
}

int	setup_output_redirections(t_list *pipe)
{
	int			fd;
	t_content	*content;

	content = pipe->content;
	if (!content->output_redirections)
	{
		if (pipe->next)
			dup2(pipe->next->content->pipe_fds[1], 1);
		return (1);
	}
	if (content->output_redirections[0].is_append)
		fd = open(content->output_redirections[0].file, \
			O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fd = open(content->output_redirections[0].file, \
			O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1 || dup2(fd, 1) == -1)
		return (close(fd), 0);
	close(fd);
	return (1);
}

void	setup_here_doc(char *string)
{
	int	fds[2];

	pipe(fds);
	ft_putstr_fd(string, fds[1]);
	ft_putstr_fd("\n", fds[1]);
	close(fds[1]);
	dup2(fds[0], 0);
	close(fds[0]);
	free(string);
}

t_list	*main_parsing(t_shell *shell, char	*getLine)
{
	t_list	*pipes;
	char	**commands;
	char	*tmp;

	if (!getLine || !*getLine)
	{
		free(getLine);
		return (NULL);
	}
	tmp = getLine;
	shell->line = getLine;
	commands = parsing_single_double_quotes(shell, getLine);
	free(tmp);
	if (!commands)
		return (NULL);
	pipes = parsing_pipes(shell, commands);
	free_double_pointer(commands);
	if (!pipes)
		return (NULL);
	return (pipes);
}
