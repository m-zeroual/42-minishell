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

void    create_pipes(t_list *pipes)
{
    while (pipes)
    {
        pipe(pipes->content->pipe_fds);
        if (pipes->next)
            pipes->content->prev_pipe_fds = pipes->content->pipe_fds;
        pipes = pipes->next;
    }
}

void    close_all_pipes(t_content *content)
{
    close(content->pipe_fds[0]);
    close(content->pipe_fds[1]);
    free(content->pipe_fds);
}
