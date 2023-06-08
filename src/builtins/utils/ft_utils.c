/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:40:22 by mzeroual          #+#    #+#             */
/*   Updated: 2023/06/08 22:08:17 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
