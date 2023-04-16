#include "../../../../includes/minishell.h"

char	**set_pipes(char **commands, int *j)
{
	char	**str;
	int		s;

	str = ft_calloc(get_number_of_commands(commands, *j) + 1, sizeof(char *));
	if (!str)
		return (NULL);
	s = 0;
	while (commands[*j])
	{
		if (commands[*j] && commands[*j][0] == PIPE && ++(*j))
			break ;
		str[s++] = ft_strdup(commands[*j]);
		free(commands[(*j)++]);
	}
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
			return (NULL);
	}
	return (pipes);
}

t_list	*parsing_pipes(char **commands)
{
	t_list		*pipes;
	t_content	*content;
	char		***p;
	int			i;
	int			len;

	if (!commands || !*commands)
		return (NULL);
	p = split_into_pipes(commands);
	if (!p)
		return (NULL);
	i = 0;
	pipes = NULL;
	while (p[i])
	{
		content = ft_calloc(1, sizeof(*content));
		if (!content)
			return (NULL);
		parsing_redirection(content, p[i]);
		len = get_lenght_of_list_without_three(p[i]);
		content->commands = get_list_without_three(p[i], len);
		ft_lstadd_back(&pipes, ft_lstnew(content));
		i++;
	}
	return (free(p), pipes);
}
