/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:27:41 by esalim            #+#    #+#             */
/*   Updated: 2023/06/05 17:39:40 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	create_file(t_shell *shell, t_redirect *file)
{
	if (!check_output_ambiguous(shell, file))
		return (0);
	if (file->is_append && !access(file->file, F_OK))
	{
		if (!check_permissions(shell, file->file, "0010"))
			return (0);
		return (close(open(file->file, O_CREAT | O_APPEND, 0644)), 1);
	}
	else if (access(file->file, F_OK) \
		|| check_permissions(shell, file->file, "0010"))
		return (close(open(file->file, O_CREAT | O_TRUNC, 0644)), 1);
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
	init_t_redirect(last_file, output + (i - 1));
	free_t_redirect(output);
	return (last_file);
}

int	check_input_ambiguous(t_shell *shell, t_redirect *inputs, char *err, int i)
{
	char	*tmpfile;

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
		if (!inputs[i].file || !*inputs[i].file \
				|| ft_strchr(inputs[i].file, ' '))
		{
			*err = 2;
			ft_printf("minishell: ambiguous redirect\n");
			shell->status = 1;
			free_t_redirect(inputs);
			return (0);
		}
	}
	return (1);
}

int	inputs_len(t_redirect *inputs, int *len)
{
	int	index;

	index = 0;
	while (inputs[++(*len)].file)
		if (inputs[(*len)].is_here_doc)
			index++;
	return (index);
}

int	ft_while(t_shell *shell, t_redirect *input, t_redirect	*lastf, char *err)
{
	int	i;
	int	index;

	i = -1;
	index = 0;
	while (++i < shell->index && input[i].file)
	{
		if (!check_input_ambiguous(shell, input, err, i))
			return (0);
		if (!input[i].is_here_doc)
		{
			if (input[i].file && access(input[i].file, F_OK))
				*err = 3;
			if (input[i].file && !access(input[i].file, F_OK) \
				&& access(input[i].file, R_OK))
				*err = 4;
			if (i < shell->index - 1)
				continue ;
		}
		init_t_redirect(lastf + index, input + i);
		index++;
	}
	return (1);
}
