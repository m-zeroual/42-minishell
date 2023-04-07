#include "../includes/minishell.h"

int main()
{
    while (1)
    {
        char    *getLine = readline("minishell $> ");
        parsing_args(getline);
    }
}
