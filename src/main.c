#include "../includes/minishell.h"

int setup_input_redirections(t_redirect *input, char **str)
{
    int     fd;
    int     i;
    char    *str_here_doc;
    int     len;

    if (!input || !input[0].file)
        return (1);
    len = -1;
    i = -1;
    while (input[++len].file);
    len--;
    while (input[++i].file)
    {
        if (i == len && input[i].is_here_doc)
        {
            *str = get_here_doc_content(input[i].file);
            return (1);
        }
        else if (i == len && !input[i].is_here_doc)
        {
            fd = open(input[i].file, O_RDONLY, 0644);
            if (fd == -1 || dup2(fd, 0) == -1)
            {
                close(fd);
                return (0);
            }
            close(fd);
            return (1);
        }
        if (input[i].is_here_doc)
        {
           str_here_doc = get_here_doc_content(input[i].file);
           free(str_here_doc);
        }
    }
    return (1);
}

int setup_output_redirections(t_redirect *output)
{
    int fd;

    if (!output || !output[0].file)
        return (1);
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


int main()
{
    char    *getLine;
    char    **commands;
    t_content   *content;
    t_redirect  *output;
    t_redirect  *input;
    int     pid;
    t_list      *pipes;
    t_list      *tmp;
    char        *str_here_doc;

    while (1)
    {
        getLine = readline("minishell $> ");
        commands = parsing_single_double_quotes(getLine);
        if (!commands)
            continue ;
        pipes = parsing_pipes(commands);
        if (!pipes)
            exit(0);
        while (pipes)
        {
            content = pipes->content;
            str_here_doc = NULL;
            output = create_output_files(content->output_redirections);
            input = get_input_file(content->input_redirections);
        	pid = fork();
        	if (pid == 0)
       	    {
                if (!setup_input_redirections(input, &str_here_doc) \
                        || !setup_output_redirections(output))
                    return (1);
                if (str_here_doc)
                {
                    ft_putstr_fd(str_here_doc, 1);
                    ft_putstr_fd("\n", 1);
                    free(str_here_doc);
                    exit(0);
                }
                free_t_redirect(input);
                free_t_redirect(output);
       	        if (execve(content->commands[0], content->commands, NULL) == -1)
                {
       	            print_error(commands[0], ": Execve Error\n");
                    exit(1);
                }
            }
            wait(NULL);
            free_t_redirect(input);
            free_t_redirect(output);
            free_double_pointer(content->commands);
            free(content);
            tmp = pipes;
            pipes = pipes->next;
            free(tmp);
       	}
        free(commands);
        free(getLine);
    }
}
