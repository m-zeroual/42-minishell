# include "../../includes/minishell.h"

int setup_input_redirections(t_redirect *input, char **str, int pipe_fds[2], int has_prev)
{
    int     fd;
    int     i;
    (void)pipe_fds;
    (void)has_prev;
    if (!input || !input[0].file)
    {
        if (has_prev)
            dup2(pipe_fds[0], 0);
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

int setup_output_redirections(t_redirect *output, int pipe_fds[2], int has_next)
{
    int fd;
    (void)pipe_fds;
    (void)has_next;
    if (!output || !output[0].file)
    {
        if (has_next)
            dup2(pipe_fds[1], 1);
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

char    *get_random_name(int len)
{
    char *str;
    int i = 0;

    str = malloc(len + 1);
    str[i] = '.';
    while (++i < len)
        str[i] = (len + i) % 29 + 2;
    str[i] = 0;
    return (str);
}

void    setup_here_doc(char *filename, char *string)
{
    int fd;

    fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    ft_putstr_fd(string, fd);
    ft_putstr_fd("\n", fd);
    close(fd);
    fd = open(filename, O_RDONLY);
    dup2(fd, 0);
    close(fd);
    free(string);
}

t_list  *main_parsing(char   *getLine)
{
    char    **commands;
    t_list      *pipes;

    if (!getLine || !*getLine)
        return (NULL);
    commands = parsing_single_double_quotes(getLine);
    if (!commands)
        return (NULL);
    pipes = parsing_pipes(commands);
    if (!pipes)
        return (NULL);
    free(commands);
    free(getLine);
    return (pipes);
}
