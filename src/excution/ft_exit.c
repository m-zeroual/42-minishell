#include "../../includes/minishell.h"
#include <inttypes.h>

int	ft_chr_to_int(const char *str, int *print)
{
	int				i;
	__int128		result;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-' )
			sign *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		result = (result * 10) + str[i] - 48;
		if (result > 9223372036854775807)
        {
            *print = 1;   
			return (255);
        }
		i++;
	}
	if (!ft_isdigit(str[i]) && str[i])
    {
        *print = 1;
		return (255);
    }
	return (result * sign);
}

int ft_exit(t_shell *_shell)
{
    int print_error;
    int num;

    print_error = 0;
    if (!_shell->pipes->content->commands[1])
        return (_shell->status);
    else
    {
        if (!_shell->pipes->content->commands[2])
        {
            num = ft_chr_to_int(_shell->pipes->content->commands[1], &print_error);
            if (num == 255)
            {
                if (print_error)
                    printf("minishell: %s: %s: numeric argument required\n", \
                _shell->pipes->content->commands[0], _shell->pipes->content->commands[1]);
                return (255);
            }
            else if (num >= 256 || num > 0)
                return (num % 256);
            else
                return (num);
        }
        else
        {
            if (ft_isalpha(_shell->pipes->content->commands[1][0]))
                return (printf("minishell: %s: %s: numeric argument required\n", \
                _shell->pipes->content->commands[0], _shell->pipes->content->commands[1]), 255);
            else
                return (printf("minishell: %s: too many arguments\n", _shell->pipes->content->commands[0]), 1);
        }
    }
}