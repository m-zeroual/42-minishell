/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:15:25 by esalim            #+#    #+#             */
/*   Updated: 2023/04/29 12:37:00 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *get_command_path(char *command, char *full_path)
{
    char *path;
    char    **splited_path;
    int     i;
    char    *tmp;

    if (!command || !full_path)
        return (0);
    if (ft_strchr(command, '/') && !access(command, F_OK) )
        return (ft_strdup(command));
    splited_path = ft_split(full_path, ':');
    if (!splited_path)
        return (0);
    i = -1;
    while (splited_path[++i])
    {
        tmp = ft_strjoin(splited_path[i], "/");
        path = ft_strjoin(tmp, command);
        if (!path)
            continue ;
        free(tmp);
        if (!access(path, F_OK) && !access(path, X_OK))
        {
            free_double_pointer(splited_path);
            return (path);
        }
        free(path);
    }
    free_double_pointer(splited_path);
    return (0);
}


void    setup_all(t_content *content, int has_next, int i, int **pipe_fds)
{
    t_redirect  *output;
    t_redirect  *input;
    char        *str_here_doc;

    str_here_doc = NULL;
    output = create_output_files(content->output_redirections);
    input = get_input_file(content->input_redirections);
    if (!setup_output_redirections(output, pipe_fds, has_next, i) \
            || !setup_input_redirections(input, &str_here_doc, pipe_fds, i))
    {
        free_double_pointer(content->commands);
        free(content);
        exit(1);
    }
    if (str_here_doc)
        setup_here_doc(str_here_doc);
    free_t_redirect(input);
    free_t_redirect(output);
}



