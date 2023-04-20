#include "../../includes/minishell.h"


void    ft_exe_echo(t_shell _shell)
{
    int i;
    char *str;
    int check;

    if (!ft_strncmp(_shell.cmd_split[1], "-n", 2))
    {
        i = 2;
        while (_shell.cmd_split[i])
        {
            str = _shell.cmd_split[i];
            check = ft_check_var_exist(_shell.env, str);
            if (check != 1)
                str = ft_getenv(_shell.env, str);
            printf("%s", str);
            if (check != 1)
                free(str);
            if (_shell.cmd_split[i + 1])
                printf(" ");
            i++;
        }
    }
    else
    {
        i = 1;
        while (_shell.cmd_split[i])
        {
            str = _shell.cmd_split[i];
            check = ft_check_var_exist(_shell.env, str);
            if (check != 1)
                str = ft_getenv(_shell.env, str);
            printf("%s", str);
            if (check != 1)
                free(str);
            if (_shell.cmd_split[i + 1])
                printf(" ");
            i++;
        }
        printf("\n");
    }
}