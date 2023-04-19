#include "../includes/minishell.h"

void    child_process(t_content *content, char *tmpfile, int has_next, int has_prev, int pipe_fds[2])
{
    t_redirect  *output;
    t_redirect  *input;
    char        *str_here_doc;

    str_here_doc = NULL;
    /*
    if (has_next)
        dup2(pipe_fds[1], 1);
    if (has_prev)
        dup2(pipe_fds[0], 0);
        */
    output = create_output_files(content->output_redirections);
    input = get_input_file(content->input_redirections);
    if (!setup_output_redirections(output, pipe_fds, has_next) \
            || !setup_input_redirections(input, &str_here_doc, pipe_fds, has_prev))
        return ;
    if (str_here_doc)
        setup_here_doc(tmpfile, str_here_doc);
    free_t_redirect(input);
    free_t_redirect(output);
    if (execve(content->commands[0], content->commands, NULL) == -1)
    {
        printf("Execve error");
        exit(1);
    }
}

int main()
{
    t_content   *content;
    int         pid;
    t_list      *pipes;
    t_list      *tmp;
    char        *tmpfile;
    int         pipe_fds[2];
    int         i;

    while (1)
    {
        pipes = main_parsing(readline("minishell $> "));
        tmpfile = get_random_name(14);
        if (!pipes)
            continue ;
        i = 0;
        while (pipes)
        {
            content = pipes->content;
            printf("%s\n", content->commands[0]);
    //        if(pipes->next)
      //          dup2(pipe_fds[0], STDIN_FILENO);
            pipe(pipe_fds);
        	pid = fork();
        	if (!pid)
                child_process(content, tmpfile, (pipes->next != NULL), i, pipe_fds);
            close(pipe_fds[0]);
            close(pipe_fds[1]);
            wait(NULL);
            if (!access(tmpfile, F_OK))
                unlink(tmpfile);
            free_double_pointer(content->commands);
            free(content);
            tmp = pipes;
            pipes = pipes->next;
            i++;
            free(tmp);
       	}
        free(tmpfile);
    }
}
