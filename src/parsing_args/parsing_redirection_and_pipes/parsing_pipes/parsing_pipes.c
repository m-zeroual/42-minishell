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
	// if (!str[0])
	// {
	// 	print_error("", "Syntax Error\n");
	// 	free(str);
	// 	shell->status = 258;
	// 	return (NULL);
	// }
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

void    set_one_to_null_pointer(char **commands)
{
    int i;

	if (!commands)
		return ;
    i = -1;
    while (commands[++i])
        if (commands[i][0] == 1)
            commands[i][0] = 0;
}

void	free_pipe(char ***p)
{
	int	i;

	i = -1;
	while (p[++i])
		free_double_pointer(p[i]);
	free(p);
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
		return (NULL);
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
