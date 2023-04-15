#include "../../../../includes/minishell.h"

static char    ***split_into_pipes(char **commands)
{
    char    ***pipes;
    int     pipes_len;
    int     i;
    int     j;
    int     s;

    if (!commands)
        return (NULL);
    pipes_len = get_number_of_pipe(commands);
    pipes = ft_calloc(pipes_len + 2, sizeof(char **));
    if (!pipes)
        return (NULL);
    i = -1;
    j = 0;
    while (++i <= pipes_len)
    {
        s = 0;
        pipes[i] = ft_calloc(get_number_of_commands(commands, j) + 1, sizeof(char *));
        if (!pipes[i])
            return (NULL);
        while (commands[j])
        {
            if (commands[j] && commands[j][0] == PIPE && ++j)
                break;
            pipes[i][s++] = ft_strdup(commands[j]);
            free(commands[j++]);
        }
    }
    return (pipes);
}

t_list    *parsing_pipes(char  **commands)
{
    
    t_list *pipes;
    char    ***p;
    int     i;
    int     len;

    if (!commands || !*commands)
        return (NULL);
    p = split_into_pipes(commands);
    if (!p)
        return (NULL);
    i = 0;
    pipes = NULL;
    while (p[i])
    {
        t_content *content = ft_calloc(1, sizeof(*content));
        if (!content)
            return (NULL);
        parsing_redirection(content, p[i]);
        len = get_lenght_of_list_without_three(p[i]);
        content->commands = get_list_without_three(p[i], len);
        ft_lstadd_back(&pipes, ft_lstnew(content));
        i++;
    }
    free(p);
    return (pipes);
}
