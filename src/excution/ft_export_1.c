#include "../../includes/minishell.h"

int	ft_getvar_and_value(char *command, char **env, char **var, char **value)
{
	char	*s;
	char	*s1;
	(void)env;

	s = 0;
	s1 = 0;

	*var = ft_getvar(command);
		
	// if (*var[0] == '$' && ft_check_var_exist(env, *var) != -1)
	// 	*var = ft_getenv(env, *var);
	if (ft_strchr(command, '='))
	{
		*value = ft_strdup((ft_strchr(command, '=') + 1));
		// printf("value |%s|\n", *value);

		// if (*value && *value[0] == '$' && ft_check_var_exist(env, *value) != -1)
		// 	*value = ft_getenv(env, *value);
	}
	return (0);
}

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
	s = ft_calloc(sizeof(char) , (i + 1));
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
	char		**str;
	char		*s;

	if (!var)
		return (0);
	s = 0;
	index = ft_check_var_exist(env, var);
	if (index != -1)
	{
		str = ft_split(env[index], '=');
		s = ft_strdup(str[1]);
		free_split(str);
	}
	return (s);
}

int	ft_var_error(t_shell _shell, char *var)
{
	// if (*var == 0)
	// {
	// 	printf("bash: %s: `%s\': not a valid identifier\n", \
	// 		_shell.cmd_split[0], "=");
	// 	return (0);
	// }
	if (!check_var_error(var))
	{
		printf("minishel: %s: `%s\': not a valid identifier\n", \
			_shell.pipes->content->commands[0], var);
		return (0);
	}
	return (1);
}
