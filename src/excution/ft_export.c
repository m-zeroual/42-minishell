#include "../../includes/minishell.h"

int	check_var_error(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (0);
	while (var[i])
	{
		if (!ft_isalpha(var[i]) && !ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_display_export(char **exp)
{
	int		i;
	char	**str;

	i = 0;
	while (exp[i])
	{
		str = ft_split(exp[i], '=');
		if (ft_strchr(exp[i], '='))
		{
			if (str[1] && str[1][0] != '"')
				printf("declare -x %s=\"%s\"\n", str[0], str[1]);
			else
				printf("declare -x %s=\"\"\n", str[0]);
		}
		else
			printf("declare -x %s\n", str[0]);
		free_split(str);
		i++;
	}
}

int	ft_add_var(t_shell *_shell)
{
	char	*var;
	char	*value;
	int		i;
	int		equal;

	i = 1;
	while (_shell->pipes->content->commands[i])
	{
		var = 0;
		value = 0;
		ft_getvar_and_value(_shell->pipes->content->commands[i], _shell->env, &var, &value);
		if (ft_strchr(_shell->pipes->content->commands[i], '='))
			equal = 1;
		else
			equal = 0;
		if (ft_var_error(*_shell, var))
		{
			if (!edit_var(_shell->env, var, value, equal))
				_shell->env = add_var(_shell->env, var, value, equal);
		}
		i++;
	}
	return (1);
}

void	ft_exe_export(t_shell *_shell)
{
	if (_shell->pipes->content->commands[1])
		ft_add_var(_shell);
	else
	{
		ft_display_export(_shell->env);
	}
}
