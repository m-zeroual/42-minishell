#include "../includes/minishell.h"

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

void    child_process(t_content *content, int has_next, int i, int **pipe_fds)
{
    t_redirect  *output;
    t_redirect  *input;
    char        *str_here_doc;
    char        *path;

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
        setup_here_doc(str_here_doc);
    free_t_redirect(input);
    free_t_redirect(output);
    path = get_command_path(content->commands[0], getenv("PATH"));
    if (!path)
    {
        print_error(content->commands[0], ": Command not found\n");
        free_double_pointer(content->commands);
        free(content);
        exit(1);
    }
    if (execve(path, content->commands, NULL) == -1)
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
    int         **pipes_fds;
    int         i;
    int         j;

    while (1)
    {
        pipes = main_parsing(readline("minishell $> "));
        if (!pipes)
            continue ;
        int size = ft_lstsize(pipes);
		pipes_fds = create_pipes(size);
		if (!pipes_fds)
		{
			print_error(NULL, ": Pipes Error\n");
			continue ;
		}
        i = 0;
        close(pipes_fds[0][0]);
        while (pipes && ++i)
        {
            content = pipes->content;
            if (!content)
                break ;
            j = -1;
            while (content->commands[++j])
                printf("|%s|\n", content->commands[j]);
        	pid = fork();
        	if (!pid)
                child_process(content, (pipes->next != NULL), i, pipes_fds);
            wait(NULL);
            close(pipes_fds[i - 1][0]);
            tmp = pipes;
            pipes = pipes->next;
            free_double_pointer(content->commands);
            free(content);
            free(tmp);
       	}
		close_all_pipes(pipes_fds, size);
    }
}
