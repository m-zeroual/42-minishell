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
		// str = ft_split(env[i], '=');
		// if (ft_strncmp(str[0], var, ft_strlen(var) + 1))
			s[j++] = ft_strdup(env[i++]);
		// free_split(str);
		// i++;
	}
	free_split(env);
	return (s);
}


void ft_exe_unset(t_shell *_shell)
{
	printf("i'm in unset\n");
	char	*var;
	// char	*value;
    int		index_var;
    // int		index_export;
	int		i;

	i = 1;
	while (_shell->pipes->content->commands[i])
	{
		// ft_getvar_and_value(_shell->pipes->content->commands[i], _shell->env, &var, &value);
		var = _shell->pipes->content->commands[i];
		index_var = ft_check_var_exist(_shell->env, var);
		if (index_var != -1)
			_shell->env = ft_remove_var(_shell->env, index_var);
		else
			ft_var_error(*_shell, var);
		// index_export = ft_check_var_exist(_shell->export, var);
		// if (index_export != -1)
		// 	_shell->export = ft_remove_var(_shell->export, var);
		i++;
	}
	_shell->status = 0;

	// if (index_var != -1 && *var)
	// {
	// 	join_equal = ft_strjoin(var, "=");
	// 	free_var = str[index_var];
	// 	if (value)
	// 		str[index_var] = ft_strjoin(join_equal, value);
	// 	else
	// 	{
	// 		if (check == ENV)
	// 			str[index_var] = ft_strdup(join_equal);
	// 		if (check == EXP && ft_strchr(str[index_var], '='))
	// 			str[index_var] = ft_strdup(join_equal);
	// 		else
	// 			str[index_var] = ft_strdup(var);
	// 	}
	// 	free(free_var);
	// 	free(join_equal);
	// 	return (1);
	// }
	// return (0);
    

}
