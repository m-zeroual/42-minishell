#include "../../includes/minishell.h"

char* ft_getvar_(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
			break ;
	}
	return (ft_substr(str, 0, i));
}

int print(char *str, int status)
{
	int i;

	(void)status;

	i = 0;
 	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?' && ++i)
			printf("%d", status);
		else
			printf("%c", str[i]);
		i++;
	}
	return (0);
}

int all_n(char *str)
{
	int i;

	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void    ft_exe_echo(t_shell *_shell)
{
	int i;
	int n;
	int pid;
	int status;

	i = 1;
	n = 1;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		while (_shell->pipes->content->commands[i] && !ft_strncmp(_shell->pipes->content->commands[i], "-n", 2) && all_n(_shell->pipes->content->commands[i]) && n++)
			i++;
		if (n != 1)
		{
			while (_shell->pipes->content->commands[i])
			{	
				if (!print(_shell->pipes->content->commands[i], _shell->status))
					if (_shell->pipes->content->commands[i + 1] != 0)
						printf(" ");
				i++;
			}
		}
		else
		{
			while (_shell->pipes->content->commands[i])
			{
				if (!print(_shell->pipes->content->commands[i], _shell->status))
					if (_shell->pipes->content->commands[i + 1] != 0)
						printf(" ");
				i++;
			}
			printf("\n");
		}
		exit (0);
	}
	wait(&status);
	if (WIFEXITED(status))
        _shell->status = WEXITSTATUS(status);
}