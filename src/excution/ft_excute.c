#include "../includes/minishell.h"

char *ft(char *str)
{
	if (ft_strchr(str, '/'))
		str = ft_strdup(str + (ft_get_index_reverse(str, '/', 1) + 1));
	else
		return (str);
	return (ft_strdup(str));
}

void	ft_exe_command(t_shell *_shell)
{
	char *cmd;
	
	cmd = ft(_shell->cmd_split[0]);
	if (!ft_strncmp(cmd, PWD, 4))
		ft_exe_pwd(*_shell);

	else if (!ft_strncmp(cmd, EN, 4))
		ft_exe_env(*_shell);

	else if (!ft_strncmp(cmd, CD, 3))
		ft_exe_cd(_shell);

	else if (!ft_strncmp(cmd, EX, 7))
		ft_exe_export(_shell);

	else if (!ft_strncmp(cmd, UNS, 5))
		ft_exe_unset(_shell);

	else
		ft_exec_cmd(_shell);
}

void	ft_join_cmd(t_shell *_shell)
{
	int		i;
	char	*help_for_free;

	i = 0;
	if (!ft_strchr(_shell->cmd_split[0], '/'))
	{
		while (_shell->path[i])
		{
			help_for_free = ft_strjoin(_shell->path[i], "/");
			free(_shell->path[i]);
			_shell->path[i] = ft_strjoin(help_for_free, _shell->cmd_split[0]);
			free(help_for_free);
			i++;
		}
	}
}

int	ft_init(t_shell *_shell)
{
	_shell->path = ft_split(getenv("PATH"), ':');
	_shell->cmd = readline("minishell>$ ");
	if (*_shell->cmd == 0)
		return (0);
	if (_shell->cmd == 0)
		exit (1);
	add_history(_shell->cmd);
	_shell->cmd_split = parsing_args(_shell->cmd);

	_shell->first_part_cmd_l = ft_str_tolower(_shell->cmd_split[0]);
	return (1);
}

void	ft_exe(t_shell *_shell)
{
	if (!ft_init(_shell))
		return ;
	ft_join_cmd(_shell);
	printf();
	// ft_exe_command(_shell);
	free_split(_shell->path);
	free_split(_shell->cmd_split);
	free(_shell->first_part_cmd_l);
	free(_shell->cmd);
}
