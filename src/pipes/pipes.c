#include "../../includes/minishell.h"

// int **get_pipes(int size)
// {
//     int **pipes;
//     int i;

//     pipes = ft_calloc(size, sizeof(*pipes));
//     if (!pipes)
//         return (0);
//     i = -1;
//     while (++i < size)
//     {
//         pipes[i] = ft_calloc(3, sizeof(*pipes[i]));
//         if (!pipes[i])
//             return (0);
//         pipe(pipes[i]);
//     }
//     return (pipes);
// }

int **create_pipes(int size)
{
    int i;
    int **pipes_fds;

    pipes_fds = ft_calloc(size + 1, sizeof(int*));
    if (!pipes_fds)
        return (0);
    i = -1;
    while (++i <= size)
    {
        pipes_fds[i] = ft_calloc(3, sizeof(int));
        if (!pipes_fds[i])
            return (0);
        pipe(pipes_fds[i]);
    }
    return (pipes_fds);
}

void    close_all_pipes(int **pipes, int size)
{
    int i;

    i = -1;
    while (++i < size)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        free(pipes[i]);
    }
    free(pipes);
}
