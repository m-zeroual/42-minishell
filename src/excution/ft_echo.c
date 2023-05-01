#include "../../includes/minishell.h"

char* ft_getvar_(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
			break ;
	}
	return (ft_substr(str, 0, i));
}

int print(char **env, char *str, int status)
{
	int i;
	char *value;
	char *s;
	(void )env;

	i = 0;
	// int k = 0;

	// if (str[0] == 2)
	// {
		// while (s[i])
		// {
		// 	if (ft_dolar_in_string(s[i]))
		// 	{
		// 		j = 0;
		// 		while (s[i][j])
		// 		{
		// 			if (s[i][j] != '$')
		// 				printf("%c", s[i][j]);
		// 			else
		// 			{
		// 				value = ft_getenv(env, (s[i] + j));
		// 				printf("%s", value);
		// 				free(value);
		// 				break ;
		// 			}
		// 			j++;
		// 		}
		// 	}
		// 	else
		// 		printf("%s", s[i]);
		// 	if (s[i + 1])
		// 		printf(" ");


 		while (str[i])
		{
			if (str[i] != '$')
				printf("%c", str[i]);
			else
			{
				if (str[i + 1] == '?')
				{
					printf("%d", status);
					i++;
				}
				else
				{
					s = ft_getvar_(&str[i + 1]);
					value = ft_getenv(env, s);
					// printf("#%s#\n", value);
					if (value)
						printf("%s", value);
					i += ft_strlen(s);
					free(value);
					free(s);
				}
			}
			i++;
		}







			// if (s[i][0] == '$')
			// {
			// 	j = 0;
			// 	expand = 0;
			// 	value = 0;
			// 	i++;
			// 	j = i;
			// 	while (str[i] && str[i] != ' ' && str[i] != '$')
			// 		i++;
			// 	expand = ft_substr(str + j, 0, i - j);
			// 	if (ft_check_var_exist(env, expand) != -1)
			// 		value = ft_getenv(env, expand);
			// 	if (value)
			// 	{
			// 		printf("%s", value);
			// 		return (1);
			// 	}
			// }
			// else
			// {
			// 	printf("%s", s[i]);
			// 	if (s[i + 1])
			// 		printf(" ");
			// 	i++;
			// }
		// 	i++;
		// }
	// }
	// else
	// 	printf("%s", str);
	return (0);
}

int all_n(char *str)
{
	int i;

	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void    ft_exe_echo(t_shell _shell)
{
	int i;
	int n;

	i = 1;
	n = 1;
	while (_shell.cmd_split[i] && !ft_strncmp(_shell.cmd_split[i], "-n", 2) && all_n(_shell.cmd_split[i]) && n++)
		i++;
	if (n != 1)
	{
		while (_shell.cmd_split[i])
		{	
			if (!print(_shell.env, _shell.cmd_split[i], _shell.status))
				if (_shell.cmd_split[i + 1] != 0)
					printf(" ");
			i++;
		}
	}
	else
	{
		while (_shell.cmd_split[i])
		{
			print(_shell.env, _shell.cmd_split[i], _shell.status);
			if (_shell.cmd_split[i + 1] != 0)
				printf(" ");
			i++;
		}
		printf("\n");
	}
}