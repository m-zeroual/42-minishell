#include "../../../../includes/minishell.h"

int	check_permissions(char *filename, char *permissions)
{
	if (permissions[0] == '1' && access(filename, F_OK))
	{
		print_error(filename, ": No such file or directory\n");
		return (0);
	}
	if ((permissions[1] == '1' && access(filename, R_OK)) \
			|| (permissions[2] == '1' && access(filename, W_OK)) \
			|| (permissions[3] == '1' && access(filename, X_OK)))
	{
		print_error(filename, ": Permission denied\n");
		return 0;
	}
	return (1);
}

void	free_t_redirect(t_redirect *redirect)
{
	unsigned char	i;

	if (!redirect)
		return ;
	i = 0;
	while (redirect[i].file)
		free(redirect[i++].file);
	ft_bzero(redirect, sizeof(*redirect));
	free(redirect);
}

int		create_file(t_redirect *file)
{
	int	fd;

	if (file->is_append \
			&& !access(file->file, F_OK) \
			&& check_permissions(file->file, "0010"))
		fd = open(file->file, O_CREAT | O_APPEND, 0644);
	else
		fd = open(file->file, O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

t_redirect	*create_output_files(t_redirect *output)
{
	t_redirect	*last_file;
	int			i;

	i = 0;
	if (!output || !output[i].file)
		return (NULL);
	last_file = ft_calloc(2, sizeof(*last_file));
	if (!last_file || !create_file(&output[0]))
		return (NULL);
	while (output[++i].file)
		if (!create_file(&output[i]))
			return (NULL);
	last_file->file = ft_strdup(output[i - 1].file);
	last_file->is_append = output[i - 1].is_append;
	last_file->is_output = output[i - 1].is_output;
	last_file->is_input = 0;
	last_file->is_here_doc = 0;
	free_t_redirect(output);
	return (last_file);
}

t_redirect	*get_input_file(t_redirect *inputs)
{
	t_redirect	*last_file;
	int			index;
	int			len;
	int			i;

	i = -1;
	index = 0;
	len = 0;
	if (!inputs || !inputs[0].file)
		return (NULL);
	while (inputs[len].file)
		len++;
	last_file = ft_calloc(len + 1, sizeof(*last_file));
	if (!last_file)
		return (NULL);
	while (++i < len && inputs[i].file)
	{
		if (!inputs[i].is_here_doc \
			&& !check_permissions(inputs[i].file, "1100"))
			return (NULL);
		if (!inputs[i].is_here_doc && i < len - 1)
			continue ;
		last_file[index].file = ft_strdup(inputs[i].file);
		last_file[index].is_here_doc = inputs[i].is_here_doc;
		last_file[index].is_input = inputs[i].is_input;
		last_file[index].is_output = 0;
		last_file[index].is_append = 0;
		index++;
	}
	free_t_redirect(inputs);
	return (last_file);
}

char	*get_here_doc_content(char	*eol)
{
	int		len;
	char	*string;
	char	*line;
	char	*tmp;

	if (!eol)
		return (ft_strdup(""));
	len = ft_strlen(eol);
	string = ft_calloc(2, sizeof(*string));
	if (!string)
		return (ft_strdup(""));
	while (1)
	{
		line = readline("> ");
		if (!line)
			continue ;
		if (!ft_strncmp(line, eol, len + 1))
		{
			len = ft_strlen(string);
			if (len)
				string[len - 1] = 0;
			break ;
		}
		tmp = ft_strjoin(string, line);
		free(string);
		string = ft_strjoin(tmp, "\n");
		free(tmp);
		free(line);
	}
	return (string);
}
