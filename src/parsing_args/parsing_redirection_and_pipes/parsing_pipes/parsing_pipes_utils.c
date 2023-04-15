#include "../../../../includes/minishell.h"

int get_number_of_commands(char **commands, int j)
{
    int i;

    i = 0;
    while (commands[j + i] && ft_strncmp(commands[j + i], "|", 2))
        i++;
    return (i);
}

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

