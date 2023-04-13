#include "../includes/main.h"


char *curr_path(t_shell _shell)
{
	char **str;
	char *pwd;
	int i;

	i = 0;
	while (_shell.ev[i])
	{
		str = ft_split(_shell.ev[i], '=');
		if (!ft_strncmp(str[0], "PWD",3))
			pwd = ft_strdup(str[1]);
		free_split(str);
		i++;
	}
	return (pwd);
}

void ft_exe_pwd(t_shell _shell)
{
	if (ft_strchr(_shell.cmd_split[0], '/'))
	{
		if (access(_shell.cmd_split[0], F_OK) == 0)
			printf("%s\n", curr_path(_shell));
		else
			printf("bash: %s: %s\n", _shell.cmd_split[0], strerror(errno));
	}
	else if (!ft_strncmp(_shell.first_part_cmd_l, PWD, 3))
		printf("%s\n", curr_path(_shell));
	else
		printf("bash: %s: %s\n", _shell.cmd_split[0], strerror(errno));
}


// char *skip_double_slash(char *arg)
// {
// 	int i;
// 	int j;
// 	char *str;

// 	str = malloc(ft_strlen(arg));
// 	i = 0;
// 	j = 0;
// 	while (arg[i])
// 	{
// 		if (arg[i] != '/' || ((arg[i] == '/' && arg[i + 1] != '/') || i == 0))
// 			str[j++] = arg[i];
// 		i++;
// 	}
// 	str[j] = 0;
// 	return (str);
// }

// int how_many_2dots(char *arg)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (arg[i])
// 	{
// 		if (arg[i] == '.' && arg[i + 1] == '.')
// 			j++;
// 		i++;
// 	}
// 	return (j);
// }



void ch_pwd(t_shell *_shell)
{
	int i;
	char **str;
	
	i = 0;
	while (_shell->ev[i])
	{
		str = ft_split(_shell->ev[i], '=');
		if (!ft_strncmp(str[0], "PWD",3))
			_shell->ev[i] = ft_strjoin("PWD=", getcwd(NULL, 1024));
		free_split(str);
		i++;
	}
}
