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
        parsing_pipes(commands);
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
