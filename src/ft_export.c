#include "../includes/main.h"

void ft_display_export(char **env);
// void AddVarInTheEndOfExport(char **env, char *var, char *value);
char **add_var(char **env, char *var, char *value);

char *ft_string_join(char *a, char *b)
{
	char *str;
	char *s;

	str = ft_strjoin(a, "=");

	s = ft_strjoin(str, "\"");
	free(str);
	str = ft_strjoin(s, b);
	free(s);
	s = ft_strjoin(str, "\"");
	return (s);
}

char **ft_fill_env(char **env, int lines)
{
	int 	i;
	char 	**env_copy;
	// char 	**str;
	// char 	*s;

	i = -1;
	env_copy = malloc((lines + 1) * sizeof(char *));
	if (!env_copy)
		return (0);
	while (env[++i])
		env_copy[i] = ft_strdup(env[i]);
	env_copy[i] = 0;
	return (env_copy);
}

long ft_abs(long num)
{
	if (num > 0)
		return (num);
	else
		return (num * -1);
}

int	ft_check_var_exist(char **env, char *var)
{
	int		i;
	char	**str;
	int		j;

	j = 0;

	if (!env || !var)
		return (-1);
	i = 0;
	if (var[0] == '$')
		j++;
	while (env[i])
	{
		printf("|%s|\n", env[i]);
		str = ft_split(env[i], '=');
		if (!str)
			return (-1);
		if (!ft_strncmp(str[0], var + j,ft_strlen(var + j)))
			return (i);
		free_split(str);
		i++;
	}
	return (-1);
}

char *ft_getenv(char **env, char *var)
{

	int index;
	char **str;
	char *s;

	s = 0;
	index = ft_check_var_exist(env, var);
	str = ft_split(env[index], '=');
	s = ft_strdup(str[1]);
	free_split(str);
	return (s);
}

int ft_count_env(char **env)
{

	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int check_var_error(char *var)
{
	int i;
	
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

int edit_var(char **str, char *var, char *value, int check)
{
	int 	index_var;
	char 	*free_var;
	char	*join_equal;

	index_var = ft_check_var_exist(str, var);
	if (index_var != -1)
	{
		join_equal = ft_strjoin(var, "=");
		free_var = str[index_var];
		if (value)
			str[index_var] = ft_strjoin(join_equal, value);
		else
		{
			if (check == ENV)
				str[index_var] = ft_strdup(join_equal);
			else if (check == EXP)
				str[index_var] = ft_strdup(var);
		}

		free(free_var);
		free(join_equal);
		return (1);
	}
	return (0);
}

// int ft_edit_exp(char **exp, char *var, char *value)
// {
// 	int 	index_var;
// 	char 	*free_var;
// 	char	*join_equal;

// 	index_var = ft_check_var_exist(exp, var);
// 	if (index_var != -1)
// 	{
// 		join_equal = ft_strjoin(var, "=");
// 		free_var = exp[index_var];
// 		if (*value)
// 			exp[index_var] = ft_strjoin(join_equal, value);
// 		else
// 			exp[index_var] = var;

// 		free(free_var);
// 		free(join_equal);
// 		return (1);
// 	}
// 	return (0);
// }
// int	ft_edit_var(t_shell *_shell, char *var, char *value)
// {
// 	if (!ft_edit_exp(_shell->export, var, value) && !ft_edit_env(_shell->env, var, value))
// 		return (1);
// 	return (0);
// }



// void fill_env(t_shell *_shell, char *var, char *value)
// {
// 	if (ft_check_var_exist(_shell->env, value) == -1)
// 		_shell->env = add_var(_shell->env, var, value, ENV);
// 	if (ft_check_var_exist(_shell->export, value) == -1)
// 		_shell->env = add_var(_shell->env, var, value, ENV);
// 		_shell->export = add_var(_shell->export, var, value, EXP);
// }



char **add_var(char **env, char *var, char *value)
{
	char 		**add_line_env;
	char		*join_equal;
	int			i;
	int			lines;

	lines = ft_count_env(env);
	add_line_env = malloc((lines + 2) * sizeof(char *));

	i = -1;
	while (env[++i])
		add_line_env[i] = ft_strdup(env[i]);

	join_equal = ft_strjoin(var, "=");
	if (value)
		add_line_env[i] = ft_strjoin(join_equal, value);
	else
		add_line_env[i] = ft_strdup(join_equal);


	free(join_equal);
	add_line_env[i + 1] = 0;
	return (add_line_env);
}

void ft_var_error(t_shell _shell, char *var)
{
	if (ft_check_var_exist(_shell.env, var) != -1 && *var == '$')
		var = ft_getenv(_shell.env, var);
	if (!check_var_error(var))
	{
		printf("bash: %s: `%s\': not a valid identifier\n",\
			_shell.cmd_split[0], var);
	}

}

char *ft_getvar(char *str)
{
	int i;
	int j;
	char *s;

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

int ft_add_var(t_shell *_shell)
{
	char	*var;
	char	*value;
	int 	i;

	i = 1;
	value = 0;
	while (_shell->cmd_split[i])
	{
		var = ft_getvar(_shell->cmd_split[i]);
			printf("asdfdsgdfgdshfsghdfjfhfghdghj\n");
			printf("1var = {%s} %p\n", var, var);

		int s = 1;
		if (ft_check_var_exist(_shell->env, var) != -1 && *var == '$')
		{
			if (!s)
				var = ft_getenv(_shell->env, var);
			else
				var = _shell->cmd_split[i];
		}

			// printf("chr %s\n", ft_strchr(_shell->cmd_split[i], '='));
			printf("hello\n");

		if (_shell->cmd_split[i][1] != '\0' && ft_strchr(_shell->cmd_split[i], '='))
		{
			value = ft_strdup((ft_strchr(_shell->cmd_split[i], '=') + 1));
			if (ft_check_var_exist(_shell->env, value) != -1 && *value == '$')
				value = ft_getenv(_shell->env, value);
		}

		ft_var_error(*_shell, _shell->cmd_split[i]);
		printf("var |%s| index %d\n", var, i);
		printf("value |%s| address %p\n", value, value);
		// printf("value %s index %d\n", value);
		if (!edit_var(_shell->export, var, value, EXP))
			_shell->export = add_var(_shell->export, var, value);
			printf("herre\n");
		if (!edit_var(_shell->env, var, value, ENV) && value)
			_shell->env = add_var(_shell->env, var, value);
		free(value);
		free(var);
		printf("------------\n");
		i++;
	}
	return (1);
}

void ft_display_export(char **exp)
{
    int i;

    i = 0;
    while (exp[i])
        printf("declare -x %s\n", exp[i++]);
}

void ft_exe_export(t_shell *_shell)
{
	if (_shell->cmd_split[1])
		ft_add_var(_shell);
	else
	{
        ft_display_export(_shell->export);
	}
}
