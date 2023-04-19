#include "../includes/minishell.h"


char **ft_remove_var(char **env, char *var)
{
	int	i;
	int	j;
	int	count;

	char **s;
	char **str;

	i = 0;
	j = 0;
	count = ft_count_env(env);
	s = malloc(count * sizeof(char *));
	if (!s)
		return (0);
	while (env[i])
	{
		str = ft_split(env[i], '=');
		if (ft_strncmp(str[0], var, ft_strlen(var) + 1))
			s[j++] = ft_strdup(env[i]);
		free_split(str);
		i++;
	}
	s[j] = 0;
	free_split(env);
	return (s);
}


void ft_exe_unset(t_shell *_shell)
{

	char	*var;
	char	*value;
    int		index_var;
    int		index_export;
	int		i;

	i = 1;
	while (_shell->cmd_split[i])
	{
		ft_getvar_and_value(_shell->cmd_split[i], _shell->env, &var, &value);
		index_var = ft_check_var_exist(_shell->env, var);
		if (index_var != -1)
			_shell->env = ft_remove_var(_shell->env, var);
		
		index_export = ft_check_var_exist(_shell->export, var);
		if (index_export != -1)
			_shell->export = ft_remove_var(_shell->export, var);
		i++;
	}

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
