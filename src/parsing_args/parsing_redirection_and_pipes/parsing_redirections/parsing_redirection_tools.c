#include "../../../../includes/minishell.h"

int skip_commands(char **commands, int *j)
{
    while (commands[*j] && commands[*j][0] != INPUT_REDIRECT && commands[*j][0] != OUTPUT_REDIRECT)
    {
        if (commands[*j][0] == PIPE)
            return (1);
        (*j)++;
    }
    return (0);
}

int redirect_len(char **commands, int *j, char c)
{
    int len;
    int two;

    len = 0;
    two = 0;
    while (commands[*j] && commands[*j][0] == c)
    {
        len++;
        if (len > 3 && two < 2 && ++two)
            p_error("<");
        ft_memset(commands[*j], 3, ft_strlen(commands[*j]));
        (*j)++;
    }
    if (!commands[*j] && len && len < 4)
    {
        p_error("newline");
        len = 4;
    }
    return (len);
}

int check_redirection_error(char **cmds, int *j, int len, int swap)
{
    int two;

    two = 0;
    while (len != 0 && cmds[(*j)] && cmds[(*j)][0] < 32 && two++ < 2)
    {
        if (swap && (cmds[(*j)][0] == OUTPUT_REDIRECT || cmds[(*j)][0] == 3))
            p_error(">");
        else if (swap && cmds[(*j)][0] == INPUT_REDIRECT)
            p_error("<");
        else if (!swap && (cmds[(*j)][0] == INPUT_REDIRECT || cmds[(*j)][0] == 3))
            p_error("<");
        else if (!swap && cmds[(*j)][0] == OUTPUT_REDIRECT)
            p_error(">");
        else if (cmds[(*j)][0] == PIPE && ++two)
            p_error("|");
        else
            p_error(cmds[(*j)]);
        (*j)++;
        len = 200;
    }
    if (len == 200)
        return (200);
    return (0);
}

int    for_each_command(t_redirect *redirection, char **commands, int *i, int *j)
{
    int input_len;
    int output_len;

    input_len = 0;
    output_len = 0;
    if (skip_commands(commands, j))
        return (2);
    input_len = redirect_len(commands, j, INPUT_REDIRECT);
    if (input_len > 3 || check_redirection_error(commands, j, input_len, 1))
        return (p_error("'\n"), 0);
    if (input_len != 0 && commands[*j] && commands[*j][0] != OUTPUT_REDIRECT)
        set_redirections(&redirection[(*i)++], commands[(*j)++], 1, input_len);
    output_len = redirect_len(commands, j, OUTPUT_REDIRECT);
    if (output_len > 2 || check_redirection_error(commands, j, output_len, 0))
        return (p_error("'\n"), 0);
    if (output_len != 0 && commands[*j] && commands[*j][0] != INPUT_REDIRECT)
        set_redirections(&redirection[(*i)++], commands[(*j)++], 0, output_len);
    return (1);
}

void    init_t_redirect(t_redirect *dest, t_redirect *src)
{
    dest->file = ft_strdup(src->file);
    dest->is_input = src->is_input;
    dest->is_output = src->is_output;
    dest->is_here_doc = src->is_here_doc;
    dest->is_append = src->is_append;
}
