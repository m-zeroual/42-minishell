#include "../../includes/minishell.h"

void	ft_exe_env(t_shell *_shell)
{
	// int	i;
	int	j;
	int	status;
	int	pid;
	char **str;

	j = 0;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		while (_shell->env[j])
		{
			str = ft_split(_shell->env[j], '=');
			if (ft_strchr(_shell->env[j], '='))
				printf("%s\n", _shell->env[j]);
			free_split(str);
			j++;
		}
		exit (0);
	}
	wait(&status);
	if (WIFEXITED(status))
        _shell->status = WEXITSTATUS(status);
}

