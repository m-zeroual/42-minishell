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
/*
char    **split_redirections(char **commands)
{
    int i;

    i = 0;
    while ()
}
*/
void    parsing_pipes(char  **commands)
{
    
    t_list *pipes;
    int     number_of_pipes;
    int     i;
    int     j;
    
    if (!commands || !*commands)
        return ;
    number_of_pipes = get_number_of_pipe(commands);
    i = 0;
    j = 0;
    pipes = NULL;
    while (i <=  number_of_pipes)
    {
        t_content *content = ft_calloc(2, sizeof(*content));
        while (commands[j])
        {
            if (commands[j][0] == PIPE)
            {
                i++;
                break;
            }
            if (commands[j][0] == INPUT_REDIRECT || commands[j][0] == OUTPUT_REDIRECT)
            {
                parsing_redirection(commands, &j);
                i = number_of_pipes;
                break ;
            }
            j++;
        }
        i++;
    }
//    ft_printf("|%d|\n", get_number_of_pipe(commands));
}
