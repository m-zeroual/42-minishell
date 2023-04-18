#include "../includes/minishell.h"

int	ft_getvar_and_value(char *command, char **env, char **var, char **value)
{
	char	*s;
	char	*s1;

	s = 0;
	s1 = 0;
	*var = ft_getvar(command);
	if (ft_check_var_exist(env, *var) != -1 && **var == '$')
	{
		s = ft_getenv(env, *var);
		free(*var);
		*var = s;
	}
	if (command[1] != '\0' && ft_strchr(command, '='))
	{
		*value = ft_strdup((ft_strchr(command, '=') + 1));
		if (ft_check_var_exist(env, *value) != -1 && **value == '$')
		{
			s1 = ft_getenv(env, *value);
			free(*value);
			*value = s1;
		}
		return (1);
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
	while (str[i] && str[i] != '=')
		i++;
	s = malloc(sizeof(char) * (i + 1));
	if (!s)
		return (0);
	j = -1;
	while (++j < i)
		s[j] = str[j];
	s[j] = 0;
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
		if (!str)
			return (-1);
		if (!ft_strncmp(str[0], var + j, ft_strlen(var + j)))
			return (i);
		free_split(str);
		i++;
	}
	return (-1);
}

char	*ft_getenv(char **env, char *var)
{
	int		index;
	char	**str;
	char	*s;

	s = 0;
	index = ft_check_var_exist(env, var);
	str = ft_split(env[index], '=');
	s = ft_strdup(str[1]);
	free_split(str);
	return (s);
}

int	ft_var_error(t_shell _shell, char *var)
{
	if (*var == 0)
	{
		printf("bash: %s: `%s\': not a valid identifier\n", \
			_shell.cmd_split[0], "=");
		return (0);
	}
	if (!check_var_error(var))
	{
		printf("bash: %s: `%s\': not a valid identifier\n", \
			_shell.cmd_split[0], var);
		return (0);
	}
	return (1);
}
