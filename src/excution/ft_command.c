#include "../../includes/minishell.h"

// void	exec_path_cmd(t_shell *_shell)
// {
// 	if (ft_strchr(_shell->cmd, '/'))
// 	{
// 		if (access(_shell->first_part_cmd_l, F_OK) == 0)
// 		{
// 			if (execve(_shell->first_part_cmd_l, _shell->pipes->content->commands, \
// 				_shell->ev) == -1)
// 				printf("Error in execve function\n");
// 		}
// 		printf("minishell: %s: No such file or directory\n" \
// 			, _shell->pipes->content->commands[0]);
// 		exit (127);
// 	}
// }

void	ft_exec_cmd(t_shell *_shell)
{
	int	p;
	int	status;

	p = fork();
	if (p == 0)
	{
		setup_all(_shell);
		if (_shell->command && execve(_shell->command, _shell->pipes->content->commands, _shell->env) == -1)
		{
			printf("Error in execve\n");
			exit(1);
		}
		printf("minishell: %s: command not found\n", _shell->pipes->content->commands[0]);
		exit(127);
	}
	// exit status of child
	wait(&status);
	if (WIFEXITED(status))
        _shell->status = WEXITSTATUS(status);
}
