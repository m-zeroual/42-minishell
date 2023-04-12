#include "../../../includes/minishell.h"
/*
int counter(char    *str, char  c)
{
    unsigned char   i;
    unsigned char   len;

    i = 0;
    len = 0;
    while (str[i])
    {
        if (str[i++] != c)
            break ;
        len++;
    }
    return (len);
}
*/
int get_number_of_pipe(char **commands)
{
    int number_of_pipes;
    int i;

    if (!commands || !*commands)
        return (0);
    number_of_pipes = 0;
    i = -1;
    while (commands[++i])
        if (commands[i][0] == PIPE)
            number_of_pipes++;
    return (number_of_pipes);
}

int get_number_of_commands(char **commands, int j)
{
    int i = 0;
    while (commands[j + i] && ft_strncmp(commands[j + i], "|", 2))
        i++;
    return (i);
}

char    ***split_into_pipes(char **commands)
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
    i = 0;
    j = 0;
    while (i <= pipes_len)
    {
        s = 0;
        pipes[i] = ft_calloc(get_number_of_commands(commands, j) + 1, sizeof(char *));
        while (commands[j])
        {
            if (commands[j] && commands[j][0] == PIPE && ++j)
                break;
            pipes[i][s++] = ft_strdup(commands[j]);
            //TODO: free commands[j]
            j++;
        }
        i++;
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
        p[i] = get_list_without_three(p[i], len);
        content->commands = p[i];
        ft_lstadd_back(&pipes, ft_lstnew(content));
        i++;
    }
    return (pipes);
}
