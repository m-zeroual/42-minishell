#include "../../../includes/minishell.h"

char	*ft_getvar(char *str)
{
	int		i;
	int		j;
	char	*s;

	if (!str)
		return (0);
	i = 0;
	if (!str)
		return (0);
	if (str[0] == '=')
		return (ft_strdup(str));
	while (str[i] && str[i] != '=')
		i++;
	s = ft_calloc(sizeof(char), (i + 1));
	if (!s)
		return (0);
	j = -1;
	while (++j < i)
		s[j] = str[j];
	return (s);
}

int	ft_check_var_exist(char **env, char *var)
{
	int		i;
	char	**str;
	int		j;

	j = 0;
	i = 0;
	if (var[0] == '$')
		j++;
	while (env[i])
	{
		str = ft_split(env[i], '=');
		// if (!str)
		// 	return (-1);
		if (!ft_strncmp(str[0], var + j, ft_strlen(var + j) + 1))
		{
			free_split(str);
			return (i);
		}
		free_split(str);
		i++;
	}
	return (-1);
}

char	*ft_getenv(char **env, char *var)
{
	int			index;
	char		*str;
	char		*s;

	if (!var)
		return (0);
	s = 0;
	index = ft_check_var_exist(env, var);
	if (index != -1)
	{
		str = ft_strchr(env[index], '=');
		if (str)
			s = ft_strdup(str + 1);
		// free_split(str);
	}
	return (s);
}

int	edit_var(char **env, char *var, char *value, int equal)
{
	int		index_var;
	char	*free_var;
	char	*join_equal;

	index_var = ft_check_var_exist(env, var);
	// printf("N =>%d\n", index_var);
	if (index_var != -1 && *var && equal)
	{
		join_equal = ft_strjoin(var, "=");
		free_var = env[index_var];
		if (value)
			env[index_var] = ft_strjoin(join_equal, value);
		else
			env[index_var] = ft_strdup(join_equal);
		free(free_var);
		free(join_equal);
	}
	if (index_var != -1)
		return (1);
	return (0);
}

char	**add_var(char **env, char *var, char *value, int equal)
{
	char	**add_line_env;
	char	*join_equal;
	int		i;
	int		lines;

	lines = ft_count_env(env);
	add_line_env = ft_calloc((lines + 2), sizeof(char *));
	if (!add_line_env)
		return (0);
	i = -1;
	while (env[++i])
		add_line_env[i] = ft_strdup(env[i]);
	join_equal = ft_strjoin(var, "=");
	if (value)
		add_line_env[i] = ft_strjoin(join_equal, value);
	else if (equal)
		add_line_env[i] = ft_strdup(join_equal);
	else
		add_line_env[i] = ft_strdup(var);
	free(join_equal);
	free_split(env);
	// add_line_env[i + 1] = 0;
	return (add_line_env);
}
