#include "../../includes/errors.h"

void    print_error(char *file, char *message)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(file, 2);
    ft_putstr_fd(message, 2);
}
