/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeroual <mzeroual@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:40:22 by mzeroual          #+#    #+#             */
/*   Updated: 2023/06/07 19:40:39 by mzeroual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_get_index_reverse(char *str, char c, int count)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i && count)
	{
		if (str[i] == c)
			count--;
		if (count == 0)
			return (i);
		i--;
	}
	return (0);
}

char	*ft_getvar_(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
			break ;
	}
	return (ft_substr(str, 0, i));
}

void	free_struct(t_shell *_shell, t_list *tmp)
{
	if (_shell->command_with_path)
	{
		free(_shell->command_with_path);
		_shell->command_with_path = NULL;
	}
	if (!tmp)
		return ;
	free_double_pointer(tmp->content->commands);
	free_t_redirect(tmp->content->output_redirections);
	free_t_redirect(tmp->content->input_redirections);
	free(tmp->content->here_doc_string);
	free(tmp->content);
	free(tmp);
}

void	del_content(void *cont)
{
	t_content	*content;

	content = (t_content *)cont;
	free_double_pointer(content->commands);
	free_t_redirect(content->output_redirections);
	free_t_redirect(content->input_redirections);
	free(content);
	return ;
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
