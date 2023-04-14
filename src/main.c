#include "../includes/minishell.h"

int setup_input_redirections(t_redirect *input)
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
            str_here_doc = get_here_doc_content(input[i].file);
            ft_putstr_fd(str_here_doc, 0);
            ft_putstr_fd("\n", 0);
            exit(0);
        }
        else if (i == len && !input[i].is_here_doc)
        {
            fd = open(input[i].file, O_RDONLY, 0644);
            if (fd == -1 || dup2(fd, 0) == -1)
                return (0);
            return (1);
        }
        if (input[i].is_here_doc)
            get_here_doc_content(input[i].file);
    }
    return (1);
}


int setup_output_redirections(t_redirect *output)
{
    int fd;
    int     i;

    if (!output || !output[0].file)
        return (1);
    i = -1;
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
        return (0);
    return (1);
}

int main()
{
    while (1)
    {
        char    *getLine = readline("minishell $> ");
        char    **commands = parsing_single_double_quotes(getLine);
        if (!commands)
            continue ;
        /*int i = -1;
        while (commands[++i])
            ft_printf("|%s|\n", commands[i]);
        */
        t_list *pipes = parsing_pipes(commands);
        if (!pipes)
            exit(0);
        while (pipes)
        {
            t_content *content = pipes->content;
            int i = -1;
            while (content->commands[++i])
                ft_printf("|%s|\n", commands[i]);
            pipes = pipes->next;
        }
        /*
        while (pipes)
        {
            t_content *content = pipes->content;
        	int pid = fork();
        	if (pid == 0)
       	    {
                t_redirect *output = create_output_files(content->output_redirections);
                t_redirect *input = get_input_file(content->input_redirections);
                if (!setup_input_redirections(input) || !setup_output_redirections(output))
                    exit(1);
       	        if (execve(content->commands[0], content->commands, NULL) == -1)
       	            ft_printf("Execve Error\n");
            }
            wait(NULL);
            pipes = pipes->next;
       	}*/
        free(getLine);
    }
}
