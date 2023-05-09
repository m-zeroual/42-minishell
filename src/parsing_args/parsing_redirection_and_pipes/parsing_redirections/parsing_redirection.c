#include "../../../../includes/minishell.h"

void	set_redirections(t_redirect *red, char *str, char is_input, int len)
{
	red->file = ft_strdup(str);
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
	int			j;
	int			res;

	i = -1;
	while (commands[++i])
		;
	redirection = ft_calloc(i + 1, sizeof(*redirection));
	if (!redirection)
		return (NULL);
	i = 0;
	j = 0;
	while (commands[j])
	{
		res = for_each_command(redirection, commands, &i, &j);
		if (!res)
		{
			// free(redirection);
			shell->status = 2;
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
	input = ft_calloc(len + 1, sizeof(*input));
	if (!input)
		return (0);
	i = -1;
	len = 0;
	while (redirections[++i].file)
		if (redirections[i].is_input == 1)
			init_t_redirect(&input[len++], &redirections[i]);
	if (!len)
		return (free(input), NULL);
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
	output = ft_calloc(len + 1, sizeof(*output));
	if (!output)
		return (0);
	i = -1;
	len = 0;
	while (redirections[++i].file)
		if (redirections[i].is_output == 1)
			init_t_redirect(&output[len++], &redirections[i]);
	if (!len)
		return (free(output), NULL);
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
	content->input_redirections = get_input_redirections(redirect);
	free_t_redirect(redirect);
	return (1);
}
