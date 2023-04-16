#include "../includes/minishell.h"

void ft_exe_env(t_shell _shell)
{
	int i;
	int j;

	i = 0;
	while (_shell.path[i])
	{
		if (access(_shell.path[i], F_OK) == 0)
		{
			j = 0;
			while (_shell.env[j])
				printf("%s\n", _shell.env[j++]);
			return ;
		}
		i++;
	}
	printf("bash: %s: %s\n", _shell.cmd, strerror(errno));
}