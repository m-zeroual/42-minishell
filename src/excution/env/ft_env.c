#include "../../../includes/minishell.h"

char	**ft_fill_env(char **env, int lines)
{
	int		i;
	char	**env_copy;

	i = -1;
	env_copy = ft_calloc((lines + 2), sizeof(char *));
	if (!env_copy)
		return (0);
	while (env[++i])
	{
		env_copy[i] = ft_strdup(env[i]);
		// printf("%s\n", env[i]);
	}
	// env_copy[i] = ft_strdup("OLDPWD");
	// env_copy[i] = 0;
	return (env_copy);
}

int	ft_count_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

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
		setup_all(_shell);
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

