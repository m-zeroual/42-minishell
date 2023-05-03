#include "../includes/minishell.h"

<<<<<<< HEAD:src/salimmain.c
char    *get_command_path(char *command, char *full_path)
{
    char *path;
    char    **splited_path;
    int     i;
    char    *tmp;

    if (!command || !*command || !full_path)
        return (0);
    if (ft_strchr(command, '/') && !access(command, F_OK) )
        return (ft_strdup(command));
    splited_path = ft_split(full_path, ':');
    if (!splited_path)
        return (0);
    i = -1;
    while (splited_path[++i])
    {
        tmp = ft_strjoin(splited_path[i], "/");
        path = ft_strjoin(tmp, command);
        if (!path)
            continue ;
        free(tmp);
        if (!access(path, F_OK) && !access(path, X_OK))
        {
            free_double_pointer(splited_path);
            return (path);
        }
        free(path);
    }
    free_double_pointer(splited_path);

    return (0);
}

void    child_process(t_list *pipe)
=======
void    child_process(t_content *content, int has_next, int i, int **pipe_fds)
>>>>>>> v1.2.0E:src/extra_main.c
{
    char        *str_here_doc;
    char        *path;

    str_here_doc = NULL;
    if (!setup_output_redirections(pipe) || !setup_input_redirections(pipe, &str_here_doc))
    {
        free_double_pointer(pipe->content->commands);
        free(pipe->content);
        exit(1);
    }
    if (str_here_doc)
        setup_here_doc(str_here_doc);
<<<<<<< HEAD:src/salimmain.c
    path = get_command_path(pipe->content->commands[0], getenv("PATH"));
    if (!path)
    {
        print_error(pipe->content->commands[0], ": Command not found\n");
        free_double_pointer(pipe->content->commands);
        free(pipe->content);
        exit(1);
    }
    if (execve(path, pipe->content->commands, NULL) == -1)
    {
        printf("Execve error\n");
        free_double_pointer(pipe->content->commands);
        free(pipe->content);
        exit(1);
    }
=======
    free_t_redirect(input);
    free_t_redirect(output);
    // path = get_command_path(content->commands[0], getenv("PATH"));
    // if (!path)
    // {
    //     print_error(content->commands[0], ": Command not found\n");
    //     free_double_pointer(content->commands);
    //     free(content);
    //     exit(1);
    // }
>>>>>>> v1.2.0E:src/extra_main.c
}

int main()
{
    t_content   *content;
    int         pid;
    t_list      *pipes;
    t_list      *tmp;
    int         i;
    char        error;

    while (1)
    {
        pipes = main_parsing(readline("minishell $> "));
        if (!pipes)
            continue ;
        create_pipes(pipes);
        i = 0;
        close(pipes->content->pipe_fds[0]);
        while (pipes && ++i)
        {
           content  = pipes->content;
            if (!content)
                break ;
            error = 0;
            content->output_redirections = create_output_files(content->output_redirections, &error);
            if (error == 1)
                break ;
            content->input_redirections = get_input_file(content->input_redirections, &error);
            if (error == 1)
                break ;
        	pid = fork();
        	if (!pid)
                child_process(pipes);
            wait(NULL);

            tmp = pipes;
            pipes = pipes->next;
            free_double_pointer(content->commands);
            free_t_redirect(content->output_redirections);
            free_t_redirect(content->input_redirections);
            free(content);
            free(tmp);
       	}
    }
}
