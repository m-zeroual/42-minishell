#include "../../includes/minishell.h"

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
		printf("minishell: %s: No such file or directory\n", _shell->cmd_split[0]);
		exit (127);
	}
}

void	ft_exec_cmd(t_shell *_shell)
{
	int	i;
	int	p;
	int check;

	i = 0;
	check = 0;
	while (_shell->path[i])
	{
		if (access(_shell->path[i], F_OK) == 0)
		{
			check = 1;
			p = fork();
			if (p == 0)
			{
				if (execve(_shell->path[i], _shell->cmd_split, \
					_shell->ev) == -1)
					printf("Error in execve\n");
			}
		}

		i++;
	}
	if (!check)
		printf("minishell: %s: command not found\n", \
			_shell->cmd_split[0]);
	wait(0);
}
