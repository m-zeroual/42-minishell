#include "../../../includes/minishell.h"

int is_acceptable(char c)
{
    return (c < 32 || c > 126);
}

void    print_error(char *str)
{
    static int i;
    char    *text;

    text = "bash: syntax error near unexpected token `";
    if (!i)
    {
        ft_putstr_fd(text, 2);
        i = 1;
    }
    ft_putstr_fd(str, 2);
    if (ft_strchr(str, '\''))
        i = 0;
}

t_redirect  *get_redirections(char   **commands, int *j)
{
    t_redirect      *redirection;
    unsigned char   input_len;
    unsigned char   output_len;
    int             i;

    redirection = ft_calloc(100, sizeof(*redirection));
    if (!redirection)
        return (0);
    i = 0;
    while (commands[*j] && (commands[*j][0] == INPUT_REDIRECT || commands[*j][0] == OUTPUT_REDIRECT))
    {
        input_len = 0;
        output_len = 0;
        while (commands[*j] && commands[*j][0] == INPUT_REDIRECT)
        {
            input_len++;
            if (input_len > 3)
                print_error("<");
            ft_memset(commands[*j], 3, ft_strlen(commands[*j]));
            (*j)++;
        }
        if (!commands[*j] && input_len)
        {
            print_error("newline");
            input_len = 4;
        }
        if (input_len > 3)
        {
            print_error("'\n");
            return (0);
        }
        while (input_len != 0 && is_acceptable(commands[*j][0]))
        {
            if (commands[*j][0] == OUTPUT_REDIRECT || commands[*j][0] == 3)
                print_error(">");
            else if (commands[*j][0] == PIPE)
                print_error("|");
            else
                print_error(commands[*j]);
            (*j)++;
            input_len = 200;
        }
        if (input_len == 200)
        {
            print_error("'\n");
            return (0);
        }
        if (input_len != 0 && commands[*j][0] != OUTPUT_REDIRECT)
        {
            redirection[i].file = ft_strdup(commands[*j]);
            ft_memset(commands[*j], 3, ft_strlen(commands[*j]));
            redirection[i].is_input = 1;
            redirection[i].is_here_doc = 0;
            if (input_len == 2)
                redirection[i].is_here_doc = 1;
            redirection[i].is_append = 0;
            redirection[i].is_output = 0;
            redirection[i].number_of_arrow = input_len;
            i++;
            (*j)++;
        }
        while (commands[*j] && commands[*j][0] == OUTPUT_REDIRECT)
        {
            output_len++;
            if (output_len > 2)
                print_error(">");
            ft_memset(commands[*j], 3, ft_strlen(commands[*j]));
            (*j)++;
        }
        if (!commands[*j] && output_len)
        {
            print_error("newline");
            output_len = 4;
        }
        if (output_len > 2)
        {
            print_error("'\n");
            return (0);
        }
        while (output_len != 0 && is_acceptable(commands[*j][0]))
        {
            if (commands[*j][0] == INPUT_REDIRECT || commands[*j][0] == 3)
                print_error("<");
            else if (commands[*j][0] == PIPE)
                print_error("|");
            else
                print_error(commands[*j]);
            (*j)++;
            output_len = 200;
        }
        if (output_len == 200)
        {
            print_error("'\n");
            return (0);
        }
        if (output_len != 0 && commands[*j][0] != INPUT_REDIRECT)
        {
            redirection[i].file = ft_strdup(commands[*j]);
            ft_memset(commands[*j], 3, ft_strlen(commands[*j]));
            redirection[i].is_input = 0;
            redirection[i].is_append = 0;
            if (output_len == 2)
                redirection[i].is_append = 1;
            redirection[i].is_here_doc = 0;
            redirection[i].is_output = 1;
            redirection[i].number_of_arrow = output_len;
            i++;
            (*j)++;
        }
    }
    return (redirection);
}
/*
int get_number_of_redirection(char  *string)
{
    char    *start = ft_strchr()
    while ()
}
*/
int parsing_redirection(char **redirections, int *j)
{
    t_redirect *redirect;

    redirect = get_redirections(redirections, j);
    if (!redirect)
        return (0);
    int i = 0;
    while (redirect[i].file)
    {
        printf("file_name = |%s|\tis_append = |%d|\tis_here_doc = |%d|\tis_input = |%d|\tis_output = |%d|\tnumber_of_arrow = |%d|\n", redirect[i].file, redirect[i].is_append, redirect[i].is_here_doc,redirect[i].is_input, redirect[i].is_output, redirect[i].number_of_arrow);
        i++;
    }
    return (0);
}
