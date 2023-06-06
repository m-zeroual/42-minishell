#include "../../../includes/minishell.h"

void	print(t_shell *_shell, int i, int check_dash_n)
{
	int	j;

	while (_shell->pipes->content->commands[i])
	{
		j = 0;
		while (_shell->pipes->content->commands[i][j])
		{
			printf("%c", _shell->pipes->content->commands[i][j]);
			j++;
		}
		if (_shell->pipes->content->commands[i + 1])
			printf(" ");
		i++;
	}
	if (!check_dash_n)
		printf("\n");
}

int	all_n(char *str)
{
	int	i;

	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_exe_echo(t_shell *_shell)
{
	int	i;
	int	n;
	int	pid;

	i = 1;
	n = 0;
	pid = fork();
	if (pid == 0)
	{
		setup_all(_shell);
		while (_shell->pipes->content->commands[i] \
		&& !ft_strncmp(_shell->pipes->content->commands[i], "-n", 2) \
		&& all_n(_shell->pipes->content->commands[i]) && ++n)
			i++;
		print(_shell, i, n);
		exit (0);
	}
}
