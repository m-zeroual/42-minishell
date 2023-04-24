#include "../includes/minishell.h"

void    child_process(t_content *content, int has_next, int i, int *pipe_fds)
{
    t_redirect  *output;
    t_redirect  *input;
    char        *str_here_doc;
    int         fd_here_doc[2];

    str_here_doc = NULL;
    output = create_output_files(content->output_redirections);
    input = get_input_file(content->input_redirections);
    if (!setup_output_redirections(output, pipe_fds, has_next, i) \
            || !setup_input_redirections(input, &str_here_doc, pipe_fds, i))
    {
        free_double_pointer(content->commands);
        free(content);
        exit(1);
    }
    if (str_here_doc)
    {
        pipe(fd_here_doc);
        setup_here_doc(str_here_doc, fd_here_doc);
    }
    free_t_redirect(input);
    free_t_redirect(output);
    if (execve(content->commands[0], content->commands, NULL) == -1)
    {
        printf("Execve error\n");
        free_double_pointer(content->commands);
        free(content);
        exit(1);
    }
}

int main()
{
    t_content   *content;
    int         pid;
    t_list      *pipes;
    t_list      *tmp;
    int         *pipes_fds;
    int         i;

    while (1)
    {
        pipes = main_parsing(readline("minishell $> "));
        if (!pipes)
            continue ;
        int size = ft_lstsize(pipes);

        pipes_fds = ft_calloc((size + 1) * 2, sizeof(int));
        i = -1;
        while (++i <= size)
            pipe(pipes_fds + (i * 2));
        i = -1;
        while (pipes && ++i > -1)
        {
            content = pipes->content;
            if (!content)
                break ;
        	pid = fork();
        	if (!pid)
                child_process(content, (pipes->next != NULL), i, pipes_fds);
            wait(NULL);
            if (size > 1)
                close(pipes_fds[(i * 2) + 1]);
            tmp = pipes;
            pipes = pipes->next;
            free_double_pointer(content->commands);
            free(content);
            free(tmp);
       	}
        i = 0;
        while (i <= size * 2)
            close(pipes_fds[i++]);
        free(pipes_fds);
    }
}
