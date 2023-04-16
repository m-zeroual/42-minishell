#include "../includes/minishell.h"

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
		printf("declare -x %s=\"%s\"\n", str[0], str[1]);
		free_split(str);
		i++;
	}
}

int	ft_add_var(t_shell *_shell)
{
	char	*var;
	char	*value;
	int		i;

	i = 1;
	var = 0;
	value = 0;
	while (_shell->cmd_split[i])
	{
		ft_getvar_and_value(_shell->cmd_split[i], _shell->env, &var, &value);
		if (ft_var_error(*_shell, var))
		{
			if (!edit_var(_shell->export, var, value, EXP))
				_shell->export = add_var(_shell->export, var, value);
			if (!edit_var(_shell->env, var, value, ENV) && value)
				_shell->env = add_var(_shell->env, var, value);
		}
		i++;
	}
	return (1);
}

void	ft_exe_export(t_shell *_shell)
{
	if (_shell->cmd_split[1])
		ft_add_var(_shell);
	else
	{
		ft_display_export(_shell->export);
	}
}
