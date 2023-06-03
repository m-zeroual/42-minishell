/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:38:55 by esalim            #+#    #+#             */
/*   Updated: 2023/06/03 16:43:20 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	replace_symbols(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		if (ft_strchr(" \"'><|", str[i]))
			str[i] -= 127;
}

void	replace_symbols_rev(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		if (str[i] < 0)
			str[i] += 127;
}

int	check_character(char	*str, int c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

void	remove_character(char *str)
{
	char	*dest;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (str[i])
		if (ft_isprint(str[i++]))
			len++;
	dest = ft_calloc(len + 1, 1);
	if (!dest)
		return ;
	i = -1;
	len = 0;
	while (str[++i])
		if (ft_isprint(str[i]))
			dest[len++] = str[i];
	len = ft_strlen(str);
	ft_bzero(str, len);
	ft_strlcpy(str, dest, len + 1);
	free(dest);
}

char	*get_file_name(t_shell *shell, char *file_name)
{
	char	*name;
	char	*tmp;
	int		i = 0;

	tmp = file_name;
	name = ft_calloc(ft_strlen(file_name) * 100, 1);
	if (!name)
		return (NULL);
	while (*file_name)
	{
		if (*file_name == '$')
		{
			file_name++;
			char	*variable = get_variable_name(&file_name);
			if (!variable)
				continue ;
			int		j = 0;
			char	*value = ft_getenv(shell->env, variable);
			free(variable);
			if (!value)
				continue ;
			while (value[j])
				name[i++] = value[j++];
			free(value);
			continue;
		}
		name[i++] = *file_name++;
	}
	free(tmp);
	tmp = ft_strdup(name);
	free(name);
	return (tmp);
}

int	check_permissions(t_shell *shell, char *filename, char *permissions)
{
	if (permissions[0] == '1' && access(filename, F_OK))
	{
		print_error(filename, ": No such file or directory\n");
		// ft_printf("minishell: No such file or directory\n");
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
	i = -1;
	while (redirect[++i].file)
		free(redirect[i].file);
	ft_bzero(redirect, sizeof(*redirect));
	free(redirect);
}

int	create_file(t_shell *shell, t_redirect *file)
{
	char	*tmp;
	int		fd;

	if (check_character(file->file, -22))
	{
		file->file = get_file_name(shell, file->file);
		if (file->file)
		{
			if (!file->file[0])
				file->file[0] = 11;
			remove_character(file->file);
			tmp = ft_strtrim(file->file, " ");
			free(file->file);
			file->file = tmp;
		}
		if (!file->file || !*file->file || ft_strchr(file->file, ' '))
		{
			ft_printf("minishell: ambiguous redirect\n");
			shell->status = 1;
			return (0);
		}
	}
	if (file->is_append && !access(file->file, F_OK))
	{
		if (!check_permissions(shell, file->file, "0010"))
			return (0);
		fd = open(file->file, O_CREAT | O_APPEND, 0644);
		close(fd);
		return (1);
	}
	else if (access(file->file, F_OK) \
		|| check_permissions(shell, file->file, "0010"))
	{
		fd = open(file->file, O_CREAT | O_TRUNC, 0644);
		close(fd);
		return (1);
	}
	return (0);
}

t_redirect	*create_output_files(t_shell *shell, t_redirect *output, char *err)
{
	t_redirect	*last_file;
	int			i;

	i = -1;
	if (!output)
		return (NULL);
	last_file = ft_calloc(2, sizeof(*last_file));
	if (!last_file)
		return (free_t_redirect(output), NULL);
	while (output[++i].file)
	{
		if (!create_file(shell, &output[i]))
		{
			*err = 1;
			return (free_t_redirect(output), free_t_redirect(last_file), NULL);
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
	char		*tmpfile;
	int			index;
	int			len;
	int			i;

	i = -1;
	index = 0;
	len = -1;
	if (!inputs)
		return (NULL);
	while (inputs[++len].file)
		if (inputs[len].is_here_doc)
			index++;
	last_file = ft_calloc(index + 2, sizeof(*last_file));
	if (!last_file)
		return (free_t_redirect(inputs), NULL);
	index = 0;
	while (++i < len && inputs[i].file)
	{
		if (!inputs[i].is_here_doc && check_character(inputs[i].file, -22))
		{
			inputs[i].file = get_file_name(shell, inputs[i].file);
			if (inputs[i].file)
			{
				if (!inputs[i].file[0])
					inputs[i].file[0] = 11;
				remove_character(inputs[i].file);
				tmpfile = inputs[i].file;
				inputs[i].file = ft_strtrim(inputs[i].file, " ");
				free(tmpfile);
			}
			if (!inputs[i].file || !*inputs[i].file || ft_strchr(inputs[i].file, ' '))
			{
				*error = 2;
				ft_printf("minishell: ambiguous redirect\n");
				shell->status = 1;
				return (free_t_redirect(inputs), free_t_redirect(last_file), NULL);
			}
		}
		if (!inputs[i].is_here_doc)
		{
    		if (inputs[i].file && access(inputs[i].file, F_OK))
    	    	*error = 3;
			if (inputs[i].file && !access(inputs[i].file, F_OK) && access(inputs[i].file, R_OK))
				*error = 4;
			if (i < len - 1)
				continue ;
		}
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

int	is_here_doc(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == -42)
			return (1);
	return (0);
}

char	*get_here_doc_content(t_shell *_shell, char	*delimiter)
{
	int		len;
	char	*string;
	char	*line;
	char	*tmp;
	char	check;

	(void)_shell;
	if (!delimiter)
		return (ft_strdup(""));
	check = is_here_doc(delimiter);
	remove_character(delimiter);
	len = ft_strlen(delimiter);
	string = ft_calloc(3, 1);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, delimiter, len + 1))
		{
			len = ft_strlen(string);
			if (len)
				string[len - 1] = 0;
			free(line);
			return (string);
		}
		if (!check)
		{
			replace_symbols(line);
			search_and_replace(line, ' ', -9);
			tmp = handle_line(_shell, line);
			free(line);
			if (!tmp)
				tmp = ft_strdup("");
			line = ft_strtrim(tmp, "\004\004");
			free(tmp);
			replace_symbols_rev(line);
			search_and_replace(line, -9, ' ');
		}
		tmp = ft_strjoin(string, line);
		free(string);
		free(line);
		string = ft_strjoin(tmp, "\n");
		free(tmp);
	}
	return (string);
}
