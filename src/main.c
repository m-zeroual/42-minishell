#include "../includes/main.h"
/*
char **ft_split_path(t_shell _shell)
{
	return(ft_split(_shell.path, ':'));
}

char **ft_split_cmd(t_shell _shell)
{
	return(ft_split(_shell.cmd, ' '));
}

int count_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

char *ft_args(char **cmd)
{
	int i;
	int j;
	int k;
	int len = 0;
	char *args;
	int num_of_args;

	i = 1;
	k = 0;
	while (cmd[i])
	{
		len += ft_strlen(cmd[i]);
		i++;
	}
	i = 1;
	num_of_args = count_args(cmd);
	args = malloc(sizeof (char) * (num_of_args + len) + 1);

	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
			args[k++] = cmd[i][j++];
		args[k++] = ' ';
		i++;
	}
	args[k] = 0;
	return (args);
}
*/
void ft_exec_cmd(t_shell _shell)
{
	int i;
	int p;

	i = 0;
	p = fork();
	if (p == 0)
	{
		while (_shell.path_split[i])
		{
			
			if (access(_shell.path_split[i], F_OK) == 0)
			{
				if (execve(_shell.path_split[i], _shell.cmd_split, _shell.ev) == -1)
					printf("Error in execve function\n");
			}
			i++;
		}
		printf("%s: commond not found\n", _shell.cmd);	
	}
	wait(0);
}

void ft_join(t_shell _shell, char **path)
{
	int i;
	char *help_for_free;
	// char *help_for_free_cmd_split;
	// char *path;

	i = 0;
	while(path[i])
	{
		help_for_free = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = help_for_free;

		help_for_free = ft_strjoin(path[i], _shell.cmd_split[0]);
		free(path[i]);
		path[i] = help_for_free;

		i++;
	}
}

// char	*ft_pwd(int print)
// {
// 	char s[1024];
// 	char *pwd;

// 	pwd = getcwd(s, sizeof(s));
// 	if (print == 1)
// 		printf("%s\n", pwd);
// 	return (pwd);
// }

void ft_exe_pwd(t_shell _shell, char **path)
{
	char s[1024];
	char *pwd;

	(void )path;
	if (_shell.cmd_split[0][0] == '/')
	{
		if (!ft_strncmp(&_shell.cmd_split[0][ft_get_index_reverse(_shell.cmd_split[0], '/') + 1], PWD, 3))
		{
			pwd = getcwd(s, sizeof(s));
			printf("%s\n", pwd);
		}
			// ft_pwd(1);        // is freed
	}
	else if (!ft_strncmp(&_shell.cmd_split[0][ft_get_index_reverse(_shell.cmd_split[0], '/')], PWD, 3))
	{
		pwd = getcwd(s, sizeof(s));
		printf("%s\n", pwd);
	}
		// ft_pwd(1);
}


void ft_exe_cd(t_shell _shell)
{
	char *pwd;
	char *pwd_free;

	if (_shell.cmd_split[1] == NULL || !ft_strncmp(_shell.cmd_split[1], "~\0", 2))
	{
		if (chdir(getenv("HOME")))
			printf("Error cd with no args.\n");
	}
	else if ( _shell.cmd_split[1][0] == '/')
	{
		if (chdir(_shell.cmd_split[1]))
			printf("bash: %s: %s: %s.\n", "cd", _shell.cmd_split[1], strerror(errno));
	}
	else if (_shell.cmd_split[1])
	{
		pwd = getcwd(NULL, 1024);
		pwd = ft_strjoin(pwd, "/");
		pwd_free = pwd;
		pwd = ft_strjoin(pwd, _shell.cmd_split[1]);
		free(pwd_free);
		if (chdir(pwd))
			printf("bash: %s: %s: %s.\n", "cd", _shell.cmd_split[1], strerror(errno));
	}
}




int	ft_check_v(t_shell _shell, char *var)
{
	int		i;
	
	char	**str;

	i = 0;
	if (var[0] == '$')
		var++;
	else
		return (0);
	while (_shell.ev[i])
	{
		str = ft_split(_shell.ev[i], '=');
		if (!ft_strncmp(str[0], var,ft_strlen(var)))
			return (1);
		free_split(str);
		i++;
	}
	return (0);
}




void ft_exe_echo(t_shell _shell)
{
	int i;
	char *help_for_free_cmd_split;

	//str_trim = NULL;
	i = 1;
	if (!ft_strncmp(_shell.cmd_split[1], "-n\0", 3) && _shell.cmd_split[2] != 0)
	{
		while (_shell.cmd_split[++i])
		{
			if (_shell.cmd_split[i][0] == '\'')
			{
				help_for_free_cmd_split = ft_strtrim(_shell.cmd_split[i], "\'");
				free(_shell.cmd_split[i]);
				_shell.cmd_split[i] = help_for_free_cmd_split;
				printf("%s", _shell.cmd_split[i]);
				if (_shell.cmd_split[i + 1])
					printf(" ");
			}
			else
			{
				help_for_free_cmd_split = ft_strtrim(_shell.cmd_split[i], "\"");
				free(_shell.cmd_split[i]);
				_shell.cmd_split[i] = help_for_free_cmd_split;
				if (_shell.cmd_split[i][0] == '$')
				{
					printf("%s", getenv(++_shell.cmd_split[i]));
					if (_shell.cmd_split[i + 1])
						printf(" ");
				}
				else 
				{
					printf("%s", _shell.cmd_split[i]);
					if (_shell.cmd_split[i + 1])
						printf(" ");
				}
			}
		}
	}
	else
	{
		while (_shell.cmd_split[i])
		{
			if (_shell.cmd_split[i][0] == '\'')
			{
				help_for_free_cmd_split = ft_strtrim(_shell.cmd_split[i], "\'");
				free(_shell.cmd_split[i]);
				_shell.cmd_split[i] = help_for_free_cmd_split;
				printf("%s", _shell.cmd_split[i]);
				if (_shell.cmd_split[i + 1])
					printf(" ");
			}
			else
			{
				help_for_free_cmd_split = ft_strtrim(_shell.cmd_split[i], "\"");
				free(_shell.cmd_split[i]);
				_shell.cmd_split[i] = help_for_free_cmd_split;
				if (_shell.cmd_split[i][0] == '$')
				{
					printf("%s", getenv(++_shell.cmd_split[i]));
					if (_shell.cmd_split[i + 1])
						printf(" ");
				}
				else 
				{
					printf("%s", _shell.cmd_split[i]);
					if (_shell.cmd_split[i + 1])
						printf(" ");
				}
			}
			i++;
		}
		printf("\n");
	}
}

void ft_exe_env(t_shell _shell)
{
	int i;

	i = 0;
	while (_shell.ev[i])
		printf("%s\n", _shell.ev[i++]);
}

/*
void ft_exe_export(t_shell *_shell)
{
	// check for variable existe


}
*/
void sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
        //rl_replace_line("", 0);
        rl_redisplay();
	}
}



void ft_exe_command(t_shell _shell, char **path)
{
	int i;

	i = 0;
	(void )path;
	ft_str_to_lower(&_shell.cmd_split[0]);
	printf("%s\n", path[0]);
	if (!ft_strncmp(&_shell.cmd_split[0][ft_get_index_reverse(_shell.cmd_split[0], '/') + 1], PWD, 3)
		|| !ft_strncmp(&_shell.cmd_split[0][ft_get_index_reverse(_shell.cmd_split[0], '/')], PWD, 3))
		printf("pwd\n");
	// ft_exe_pwd(_shell, path);
	// ft_exe_cd(_shell);
	// ft_exec_cmd(*_shell);

	// if (_shell.cmd_split[0][0] == '/')
	// {
	// 	if (!ft_strncmp(&_shell.cmd_split[0][ft_get_index_reverse(_shell.cmd_split[0], '/') + 1], PWD, 3))
	// 		ft_pwd(1);        // is freed
	// }
	// else if (!ft_strncmp(&_shell.cmd_split[0][ft_get_index_reverse(_shell.cmd_split[0], '/')], PWD, 3))
	// 	ft_pwd(1);        // is freed


	// while (_shell.cmd_split[i])
	// {

	// 	if (path[i])
	// }
	// if (!ft_strncmp(_shell->cmd_split[0], PWD, 3))
	// else if (!ft_strncmp(_shell->cmd_split[0], "echo", 4))
	// 	ft_exe_echo(*_shell);
	// else if (!ft_strncmp(_shell->cmd_split[0], CD, 2))
	// 	ft_exe_cd(*_shell);
	// else if (!ft_strncmp(_shell->cmd_split[0], ENV, 3))
	// 	ft_exe_env(*_shell);
	// else if (!ft_strncmp(_shell->cmd_split[0], EXIT, 4))
	// 	exit (0);
	// //else if (!ft_strncmp(_shell->cmd_split[0], "export", 6))
	// //	ft_exe_export(_shell)
	// else
	// 	ft_exec_cmd(*_shell);
}
void ft_exe(t_shell *_shell)
{
	char **path;

	_shell->path = getenv("PATH");
	_shell->path_split = ft_split(_shell->path, ':');
	path = ft_split(_shell->path, ':');

	_shell->cmd = readline("minishell:$ ");
	if (_shell->cmd)
		add_history(_shell->cmd);
	if (_shell->cmd == 0)
		exit (1);
	if (*_shell->cmd == 0)
		return ;
	_shell->cmd_split = ft_split(_shell->cmd, ' ');

	ft_join(*_shell, path);       // is freed
	ft_exe_command(*_shell, path);

	// if (!ft_strncmp(_shell->cmd_split[0], PWD, 3))
	// 	ft_pwd(1);        // is freed
	// else if (!ft_strncmp(_shell->cmd_split[0], "echo", 4))
	// 	ft_exe_echo(*_shell);
	// else if (!ft_strncmp(_shell->cmd_split[0], CD, 2))
	// 	ft_exe_cd(*_shell);
	// else if (!ft_strncmp(_shell->cmd_split[0], ENV, 3))
	// 	ft_exe_env(*_shell);
	// else if (!ft_strncmp(_shell->cmd_split[0], EXIT, 4))
	// 	exit (0);
	// //else if (!ft_strncmp(_shell->cmd_split[0], "export", 6))
	// //	ft_exe_export(_shell)
	// else
	// 	ft_exec_cmd(*_shell);
}

int main(int ac, char *av[], char *ev[])
{
	t_shell _shell;

	signal(SIGINT, sig_handler);

	_shell.ac = ac;
	_shell.av = av;
	_shell.ev = ev;
	while (1)
		ft_exe(&_shell);

	return (0);
}
