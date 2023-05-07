/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:15:25 by esalim            #+#    #+#             */
/*   Updated: 2023/05/07 15:44:27 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    setup_all(t_shell *_shell)
{
    char        *str_here_doc;

    str_here_doc = NULL;
    if (!setup_output_redirections(_shell->pipes) \
        || !setup_input_redirections(_shell, &str_here_doc))
    {
        free_double_pointer(_shell->pipes->content->commands);
        free(_shell->pipes->content);
        exit(1);
    }
    close(_shell->pipes->content->pipe_fds[0]);
    close(_shell->pipes->content->pipe_fds[1]);
    if (str_here_doc)
        setup_here_doc(str_here_doc);
}



