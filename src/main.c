#include "../includes/minishell.h"

int main()
{
    while (1)
    {
        char    *getLine = readline("minishell $> ");
        char    **commands = parsing_single_double_quotes(getLine);
        int i = 0;
        while (commands[i])
            ft_printf("|%s|\n", commands[i++]);
    }
}
