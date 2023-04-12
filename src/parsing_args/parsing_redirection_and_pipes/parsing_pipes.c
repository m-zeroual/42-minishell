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

char    ***split_into_pipes(char **commands)
{
    char    ***pipes;
    int     pipes_len;
    int     i;
    int     j;
    int     s;

    if (!commands)
        exit(5);
    pipes_len = get_number_of_pipe(commands);
    pipes = ft_calloc(pipes_len + 1, sizeof(char **));
    if (!pipes)
        return (NULL);
    i = 0;
    j = 0;
    while (i < pipes_len - 1)
    {
        s = 0;
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

/*
char    **split_redirections(char **commands)
{
    int i;

    i = 0;
    while ()
}
*/
t_list    *parsing_pipes(char  **commands)
{
    
//    t_list *pipes;
//    int     number_of_pipes;
    int     i;
    int     j;

    char    ***p = split_into_pipes(commands);
    if (!p)
        exit(5);
    i = -1;
    while (p[++i])
    {
        j = -1;
        while (p[i][++j])
            ft_printf("|%s|\n", p[i][j]);
        ft_printf("==================================\n");
    }

   /* 
    if (!commands || !*commands)
        return (NULL);
    number_of_pipes = get_number_of_pipe(commands);
    i = 0;
    j = 0;
    pipes = NULL;
    while (i <=  number_of_pipes)
    {
        t_content *content = ft_calloc(2, sizeof(*content));
        parsing_redirection(content, commands, &j);
        if (commands[j] && commands[j][0] == PIPE)
            j++;
        ft_lstadd_front(&pipes, ft_lstnew(content));
        i++;
    }
//    ft_printf("|%d|\n", get_number_of_pipe(commands));*/
    return (NULL);
}
