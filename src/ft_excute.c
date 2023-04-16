#include "../includes/minishell.h"

void ft_exe_command(t_shell *_shell)
{
	if (!ft_strncmp(_shell->first_part_cmd_l, PWD, 4)
		|| !ft_strncmp(_shell->first_part_cmd_l + (ft_get_index_reverse(_shell->first_part_cmd_l, '/', 1) + 1), PWD, 4))
		ft_exe_pwd(*_shell);
	else if (!ft_strncmp(_shell->first_part_cmd_l, EN, 4)
		|| !ft_strncmp(_shell->first_part_cmd_l + (ft_get_index_reverse(_shell->first_part_cmd_l, '/', 1) + 1), EN, 4))
		ft_exe_env(*_shell);
	else if (!ft_strncmp(_shell->first_part_cmd_l, CD, 3)
		|| !ft_strncmp(_shell->first_part_cmd_l + (ft_get_index_reverse(_shell->first_part_cmd_l, '/', 1) + 1), CD, 3))
		ft_exe_cd(*_shell);
	else if ((!ft_strncmp(_shell->first_part_cmd_l, EX, 7)
		|| !ft_strncmp(_shell->first_part_cmd_l + (ft_get_index_reverse(_shell->first_part_cmd_l, '/', 1) + 1), EX, 7)))
		ft_exe_export(_shell);
	// else if (!ft_strncmp(_shell->first_part_cmd_l, EXP, 7))
	// 	ft_exe_export(_shell);
	else
		ft_exec_cmd(_shell);
}
void ft_join_cmd(t_shell *_shell)
{
	int i;
	char *help_for_free;
	i = 0;
	while(_shell->path[i])
	{
		help_for_free = ft_strjoin(_shell->path[i], "/");
		free(_shell->path[i]);
		// _shell->path[i] = help_for_free;
		_shell->path[i] = ft_strjoin(help_for_free, _shell->cmd_split[0]);
		free(help_for_free);

		i++;
	}
}
int ft_init(t_shell *_shell)
{
	_shell->path = ft_split(getenv("PATH"), ':');

	_shell->cmd = readline("minishell:$ ");
	if (*_shell->cmd == 0)
		return (0);
	if (_shell->cmd == 0)
		exit (1);
	add_history(_shell->cmd);
	_shell->cmd_split = ft_split(_shell->cmd, ' ');
	_shell->first_part_cmd_l = ft_str_tolower(_shell->cmd_split[0]);
	_shell->second_part = _shell->cmd_split[1];
	return (1);
}

void ft_exe(t_shell *_shell)
{
	if (!ft_init(_shell))
		return ;
	ft_join_cmd(_shell);       // is freed
	ft_exe_command(_shell);

}

