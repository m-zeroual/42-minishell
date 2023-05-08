#include "../../includes/minishell.h"

int	check_var_error(char *var)
{
	int	i;

	i = 0;
	if (!var)
		return (0);
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (0);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_display_export(char **exp)
{
	int		i;
	int		j;
	// char	**str;

	i = 0;
	while (exp[i])
	{
		if (ft_strchr(exp[i], '='))
		{
			j = 0;
			printf("declare -x ");
			while (exp[i][j])
			{
				if (exp[i][j] != '=')
					printf("%c", exp[i][j++]);
				else
					break ;
			}
			printf("=\"");
			j++;
			while (exp[i][j])
			{
				if (exp[i][j] == '$' || exp[i][j] == '"')
					printf("\\");
				printf("%c", exp[i][j++]);
			}
			printf("\"");
		}
		else
		{
			j = 0;
			printf("declare -x ");
			while (exp[i][j])
			{
				if (exp[i][j] != '=')
					printf("%c", exp[i][j++]);
				else
					break ;
			}
		}
		printf("\n");
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
		if (ft_var_error(_shell, var))
		{
			if (!edit_var(_shell->env, var, value, equal))
				_shell->env = add_var(_shell->env, var, value, equal);
		}
		free(var);
		free(value);
		i++;
	}
	return (0);
}

void	ft_exe_export(t_shell *_shell)
{
	int pid;
	int status;

	// pid = -1;
	// while (_shell->pipes->content->commands[++pid])
	// 	printf("|%s|\n", _shell->pipes->content->commands[pid]);

	if (_shell->pipes->content->commands[1])
		ft_add_var(_shell);
	else
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			setup_all(_shell);
			ft_display_export(_shell->env);
			exit(0);
		}
		wait(&status);
		if (WIFEXITED(status))
			_shell->status = WEXITSTATUS(status);
	}
}
