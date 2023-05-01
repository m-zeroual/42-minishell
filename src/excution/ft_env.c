#include "../../includes/minishell.h"

void	ft_exe_env(t_shell _shell)
{
	// int	i;
	int	j;
	char **str;

	j = 0;
	while (_shell.env[j])
	{
		str = ft_split(_shell.env[j], '=');
		if (ft_strchr(_shell.env[j], '='))
			printf("%s\n", _shell.env[j]);
		free_split(str);
		j++;
	}
}

