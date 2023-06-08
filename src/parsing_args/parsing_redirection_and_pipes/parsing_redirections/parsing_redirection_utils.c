/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:38:55 by esalim            #+#    #+#             */
/*   Updated: 2023/06/08 20:16:43 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

t_redirect	*get_input_file(t_shell *shell, t_redirect *inputs, char *error)
{
	t_redirect	*last_file;
	int			len;
	int			i;

	i = -1;
	len = -1;
	if (!inputs)
		return (NULL);
	last_file = ft_calloc(inputs_len(inputs, &len) + 2, sizeof(*last_file));
	if (!last_file)
		return (free_t_redirect(inputs), NULL);
	shell->index = len;
	if (!ft_while(shell, inputs, last_file, error))
		return (free_t_redirect(last_file), NULL);
	return (free_t_redirect(inputs), last_file);
}

void	ft_swap_strings(char *string, char *line)
{
	char	*tmp;

	tmp = ft_strjoin(string, line);
	free(string);
	free(line);
	string = ft_strjoin(tmp, "\n");
	free(tmp);
}

void	edit_line(t_shell *shell, char **line, char **string, int check)
{
	char	*tmp;

	if (!check)
	{
		replace_symbols(*line);
		search_and_replace(*line, ' ', -9);
		tmp = handle_line(shell, *line);
		if (!tmp)
			tmp = ft_strdup("");
		free(*line);
		*line = ft_strtrim(tmp, "\004\004");
		free(tmp);
		replace_symbols_rev(*line);
		search_and_replace(*line, -9, ' ');
	}
	tmp = ft_strjoin(*string, *line);
	free(*string);
	free(*line);
	*string = ft_strjoin(tmp, "\n");
	free(tmp);
}

char	*get_string(t_shell *shell, char *string, char *delimiter, char check)
{
	char	*line;
	int		len;

	len = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, delimiter, len + 1))
		{
			len = ft_strlen(string);
			if (len)
				string[len - 1] = 0;
			return (free(line), string);
		}
		edit_line(shell, &line, &string, check);
	}
	return (string);
}

char	*get_here_doc_content(t_shell *_shell, char	*delimiter)
{
	char	*result;
	char	*string;
	char	check;
	int		fd;

	if (!delimiter)
		return (ft_strdup(""));
	check = is_here_doc(delimiter);
	remove_character(delimiter);
	string = ft_calloc(3, 1);
	if (!string)
		return (NULL);
	result = get_string(_shell, string, delimiter, check);
	fd = dup(0);
	if (fd == -1)
		return (free(result), NULL);
	close(fd);
	return (result);
}
