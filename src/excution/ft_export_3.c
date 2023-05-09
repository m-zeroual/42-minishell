#include "../../includes/minishell.h"

char	**ft_fill_env(char **env, int lines)
{
	int		i;
	char	**env_copy;

	i = -1;
	env_copy = ft_calloc((lines + 1), sizeof(char *));
	if (!env_copy)
		return (0);
	while (env[++i])
		env_copy[i] = ft_strdup(env[i]);
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
