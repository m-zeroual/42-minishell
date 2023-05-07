#include "../../includes/minishell.h"


char **ft_remove_var(char **env, int index_to_remove)
{
	int	i;
	int	j;
	int	count;

	char **s;
	// (void)var;
	// (void)env;
	// char **str;

	i = 0;
	j = 0;
	count = ft_count_env(env);
	s = ft_calloc(count, sizeof(char *));
	if (!s)
		return (0);
	while (env[i])
	{
		if (i == index_to_remove)
			i++;
		s[j++] = ft_strdup(env[i++]);
	}
	free_split(env);
	return (s);
}


void ft_exe_unset(t_shell *_shell)
{
	char	*var;
    int		index_var;
	int		i;

	i = 1;
	while (_shell->pipes->content->commands[i])
	{
		var = _shell->pipes->content->commands[i];
		index_var = ft_check_var_exist(_shell->env, var);
		if (index_var != -1)
		{
			_shell->env = ft_remove_var(_shell->env, index_var);
			_shell->status = 0;
		}
		else
			ft_var_error(_shell, var);
		i++;
	}
}
