/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:20:15 by esalim            #+#    #+#             */
/*   Updated: 2023/06/05 17:39:40 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	expand_file_name(t_shell *shell, char *name, char *file_name, int i)
{
	char	*variable;
	char	*value;
	int		j;

	while (*file_name)
	{
		if (*file_name == '$')
		{
			file_name++;
			variable = get_variable_name(&file_name);
			if (!variable)
				continue ;
			j = 0;
			value = ft_getenv(shell->env, variable);
			free(variable);
			if (!value)
				continue ;
			while (value[j])
				name[i++] = value[j++];
			free(value);
			continue ;
		}
		name[i++] = *file_name++;
	}
}

char	*get_file_name(t_shell *shell, char *file_name)
{
	char	*name;
	char	*tmp;
	int		i;

	tmp = file_name;
	name = ft_calloc(ft_strlen(file_name) * 100, 1);
	if (!name)
		return (NULL);
	i = 0;
	expand_file_name(shell, name, file_name, i);
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
		shell->status = 1;
		return (0);
	}
	if ((permissions[1] == '1' && access(filename, R_OK)) \
			|| (permissions[2] == '1' && access(filename, W_OK)) \
			|| (permissions[3] == '1' && access(filename, X_OK)))
	{
		print_error(filename, ": Permission denied\n");
		shell->status = 1;
		if (permissions[3] == '1' && access(filename, X_OK))
			shell->status = 126;
		return (0);
	}
	return (1);
}

int	check_output_ambiguous(t_shell *shell, t_redirect *file)
{
	char	*tmp;

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
	return (1);
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
