#include "../../../../includes/minishell.h"

int	check_permissions(t_shell *shell, char *filename, char *permissions) //
{
	if (permissions[0] == '1' && access(filename, F_OK))
	{
		// print_error(filename, ": No such file or directory\n");
		ft_printf("minishell: No such file or directory\n");
		// exit status
		shell->status = 1;
		return (0);
	}
	if ((permissions[1] == '1' && access(filename, R_OK)) \
			|| (permissions[2] == '1' && access(filename, W_OK)) \
			|| (permissions[3] == '1' && access(filename, X_OK)))
	{
		// ft_printf("minishell: Permission denied\n");
		print_error(filename, ": Permission denied\n");
		shell->status = 1;
		if (permissions[3] == '1' && access(filename, X_OK))
			shell->status = 126;
		// exit status
		return (0);
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
	// ft_bzero(redirect, sizeof(*redirect));
	free(redirect);
}

int		create_file(t_shell *shell, t_redirect *file)
{
	int	fd;
//														//	
//	// printf("[%s]\n", file->file);					//			
//	if (!file->file || ft_strchr(file->file, ' '))		//	
//	{													//		this part added by m-zeroual
//		ft_printf("minishell: ambiguous redirect\n");	//		
//		shell->status = 1;								//					
//		return (0);										//				
//	}													//

	if (file->is_append && !access(file->file, F_OK))
	{
		if (!check_permissions(shell, file->file, "0010"))
			return (0);
		fd = open(file->file, O_CREAT | O_APPEND, 0644);
		close(fd);
		return (1);
	}
	else if (access(file->file, F_OK) || check_permissions(shell, file->file, "0010"))
	{
		fd = open(file->file, O_CREAT | O_TRUNC, 0644);
		close(fd);
		return (1);
	}
	return (0);
}

t_redirect	*create_output_files(t_shell *shell, t_redirect *output, char *error)
{
	t_redirect	*last_file;
	int			i;

	i = -1;
	if (!output)
		return (NULL);
	last_file = ft_calloc(2, sizeof(*last_file));
	if (!last_file)
	{
		free_t_redirect(output);
		return (NULL);
	}
	while (output[++i].file)
	{
		if (!create_file(shell, &output[i]))
		{
			*error = 1;
			free_t_redirect(output);
			free(last_file);
			return (NULL);
		}
	}
	last_file->file = ft_strdup(output[i - 1].file);
	last_file->is_append = output[i - 1].is_append;
	last_file->is_output = output[i - 1].is_output;
	last_file->is_input = 0;
	last_file->is_here_doc = 0;
	free_t_redirect(output);
	return (last_file);
}

t_redirect	*get_input_file(t_shell *shell, t_redirect *inputs, char *error)
{
	t_redirect	*last_file;
	int			index;
	int			len;
	int			i;

	i = -1;
	index = 0;
	len = -1;
	(void)shell;
	(void)error;
	if (!inputs)
		return (NULL);
	while (inputs[++len].file)
		if (inputs[len].is_here_doc)
			index++;
	last_file = ft_calloc(index + 2, sizeof(*last_file));
	if (!last_file)
		return (NULL);
	index = 0;
	while (++i < len && inputs[i].file)
	{
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

char	*remove_garbage_value(char *str)
{
	int	len = 0;
	int	i = 0;
	while (str[i])
		if (ft_isprint(str[i++]))
			len++;
	char *dest = ft_calloc(len + 1, 1);
	if (!dest)
		return (0);
	i = -1;
	len = 0;
	while (str[++i])
		if (ft_isprint(str[i]))
			dest[len++] = str[i];
	return (dest);
}

int	is_here_doc(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == -42)
			return (1);
	return (0);
}

char	*get_here_doc_content(t_shell *_shell, char	*eol)
{
	int		len;
	char	*string;
	char	*line;
	char	*tmp;
	char	check;

	if (!eol)
		return (ft_strdup(""));
	check = is_here_doc(eol);
	eol = remove_garbage_value(eol);
	len = ft_strlen(eol);
	string = ft_calloc(2, sizeof(*string));
	if (!string)
		return (ft_strdup(""));
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			len = ft_strlen(string);
			if (len)
				string[len - 1] = 0;
			break ;
		}
		// ft_printf("delimiter ==> |%s|\n", eol);
		if (!ft_strncmp(line, eol, len + 1))
		{
			len = ft_strlen(string);
			if (len)
				string[len - 1] = 0;
			break ;
		}
		if (!check)
		{
			search_and_replace(line, '"', -3);
			search_and_replace(line, '\'', -2);
			search_and_replace(line, '>', -4);
			search_and_replace(line, '<', -5);
			search_and_replace(line, '|', -6);
			search_and_replace(line, ' ', -9);
			tmp = handle_line(_shell, line);
			// free(line);
			line = ft_strtrim(tmp, "\004\004");
			// free(tmp);
			search_and_replace(line, -3, '"');
			search_and_replace(line, -2, '\'');
			search_and_replace(line, -4, '>');
			search_and_replace(line, -5, '<');
			search_and_replace(line, -6, '|');
			search_and_replace(line, -9, ' ');
		}
		tmp = ft_strjoin(string, line);
		// free(string);
		string = ft_strjoin(tmp, "\n");
		// free(tmp);
		// if (line)
		// 	free(line);
	}
	return (string);
}
