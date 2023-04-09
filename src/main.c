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
        int len = get_lenght_of_list_without_three(commands);
        get_list_without_three(commands, len);
        free(getLine);
    }
}
