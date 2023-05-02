# include "../../includes/minishell.h"

int setup_input_redirections(t_redirect *input, char **str, int **pipe_fds, int has_prev)
{
    int     fd;
    int     i;

    if (!input || !input[0].file)
    {
        if (has_prev)
        {
            close(pipe_fds[has_prev - 1][1]);
            dup2(pipe_fds[has_prev - 1][0], 0);
            close(pipe_fds[has_prev - 1][0]);
            // return (0);
        }
        return (1);
    }
    i = -1;
    while (input[++i].file)
    {
        if (!input[i + 1].file && input[i].is_here_doc)
        {
            *str = get_here_doc_content(input[i].file);
            return (1);
        }
        else if (!input[i + 1].file && !input[i].is_here_doc)
        {
            fd = open(input[i].file, O_RDONLY, 0644);
            if (fd == -1 || dup2(fd, 0) == -1)
                return (0);
            close(fd);
            return (1);
       }
        if (input[i].is_here_doc)
           free(get_here_doc_content(input[i].file));
    }
    return (1);
}

int setup_output_redirections(t_redirect *output, int **pipe_fds, int has_next, int has_prev)
{
    int fd;

    if (!output || !output[0].file)
    {
        if (has_next)
        {
            close(pipe_fds[has_prev][0]);
            dup2(pipe_fds[has_prev][1], 1);
            close(pipe_fds[has_prev][1]);
        }
        return (1);
    }
    if (output[0].is_append)
        fd = open(output[0].file, O_CREAT | O_APPEND | O_WRONLY, 0644);
    else
        fd = open(output[0].file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd == -1)
    {
        print_error(output[0].file, ": Not such file or directory\n");
        exit(1);
    }
    if (dup2(fd, 1) == -1)
    {
        close(fd);
        return (0);
    }
    close(fd);
    return (1);
}

void    setup_here_doc(char *string)
{
    int fds[2];

    pipe(fds);
    ft_putstr_fd(string, fds[1]);
    ft_putstr_fd("\n", fds[1]);
    close(fds[1]);
    dup2(fds[0], 0);
    close(fds[0]);
    free(string);
}

t_list  *main_parsing(char   *getLine)
{
    char    **commands;
    char    *tmp;
    t_list      *pipes;

    if (!getLine || !*getLine)
    {
        free(getLine);
        return (NULL);
    }
    tmp = getLine;
    commands = parsing_single_double_quotes(getLine);
    free(tmp);
    if (!commands)
        return (NULL);
    pipes = parsing_pipes(commands);
    if (!pipes)
        return (NULL);
    free(commands);
    return (pipes);
}
