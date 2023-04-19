#include "../../includes/errors.h"

void    print_error(char *file, char *message)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(file, 2);
    ft_putstr_fd(message, 2);
}

void    p_error(char *str)
{
    static int  i;
    char        *text;

    text = "minishell: syntax error near unexpected token `";
    if (!i)
    {
        ft_putstr_fd(text, 2);
        i = 1;
    }
    ft_putstr_fd(str, 2);
    if (str[0] == '\'')
        i = 0;
}
