#include "../../../includes/minishell.h"

char	*curr_path(t_shell _shell)
{
	char	**str;
	char	*pwd;
	int		i;

	i = 0;
	while (_shell.env[i])
	{
		str = ft_split(_shell.env[i], '=');
		if (!ft_strncmp(str[0], "PWD", 3))
		{
			pwd = ft_strdup(str[1]);
			free_split(str);
			return (pwd);
		}
		free_split(str);
		i++;
	}
	return (0);
}

void	ft_exe_pwd(t_shell *_shell)
{
	char	*str;
	int		pid;
	int		status;

	str = 0;
	pid = fork ();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		setup_all(_shell);
		str = getcwd(NULL, 1024);
		printf("%s\n", str);
		free(str);
		exit (0);
	}
	wait(&status);
	if (WIFEXITED(status))
		_shell->status = WEXITSTATUS(status);
}

void	ch_pwd(t_shell *_shell)
{
	int		i;
	char	**str;

	i = 0;
	while (_shell->env[i])
	{
		str = ft_split(_shell->env[i], '=');
		if (!ft_strncmp(str[0], "PWD", 3))
		{
			free(_shell->env[i]);
			_shell->env[i] = ft_strjoin("PWD=", getcwd(NULL, 1024));
		}
		free_split(str);
		i++;
	}
}
