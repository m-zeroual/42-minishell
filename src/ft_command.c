#include "../includes/minishell.h"

void	exec_path_cmd(t_shell *_shell)
{
	if (ft_strchr(_shell->cmd, '/'))
	{
		if (access(_shell->first_part_cmd_l, F_OK) == 0)
		{
			if (execve(_shell->first_part_cmd_l, _shell->cmd_split, \
				_shell->ev) == -1)
				printf("Error in execve function\n");
		}
		printf("bash: %s: No such file or directory\n", _shell->cmd_split[0]);
		exit (127);
	}
}

void	ft_exec_cmd(t_shell *_shell)
{
	int	i;
	int	p;

	i = 0;
	while (_shell->path[i])
	{
		if (access(_shell->path[i], F_OK) == 0)
		{
			p = fork();
			if (p == 0)
			{
				if (execve(_shell->path[i], _shell->cmd_split, \
					_shell->ev) == -1)
					printf("bash: %s: command not found\n", \
					_shell->cmd_split[0]);
			}
		}
		i++;
	}
	wait(0);
}
