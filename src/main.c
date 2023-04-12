#include "../includes/minishell.h"

int main()
{
    while (1)
    {
        char    *getLine = readline("minishell $> ");
        char    **commands = parsing_single_double_quotes(getLine);
        if (!commands)
            continue ;
/*        int i = -1;
        while (commands[++i])
            ft_printf("|%s|\n", commands[i]);*/
        t_list *pipes = parsing_pipes(commands);
        if (!pipes)
            continue ;
        while (pipes)
        {
            t_content *content = pipes->content;
            int o = 0;
            while (content->commands[o])
                ft_printf("|%s|\n", content->commands[o++]);
            if (content->input_redirections)
                ft_printf("%s\n", content->input_redirections->file);
            if (content->output_redirections)
                ft_printf("%s\n", content->output_redirections->file);
            pipes = pipes->next;
        }
        /*
        int i = -1;
        while (commands[++i])
            ft_printf("|%s|\n", commands[i]);
        int len = get_lenght_of_list_without_three(commands);
        char    **str = get_list_without_three(commands, len);
        if (!str)
            continue ;
        i = -1;
        while (str[++i] && str[i][0] != 3)
            ft_printf("|%s|\n", str[i]);
        str[i] = NULL;
        int pid = fork();
        if (pid == 0)
            if (execve(str[0], str, NULL) == -1)
                ft_printf("Execve Error\n");
        wait(NULL);*/
        free(getLine);
    }
}
