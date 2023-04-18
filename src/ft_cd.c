#include "../includes/minishell.h"

void	cd_path(t_shell *_shell)
{
	if (!chdir(_shell->cmd_split[1]))
		ch_pwd(_shell);
	else
		printf("bash: %s: %s: %s\n", _shell->cmd_split[0], \
			_shell->cmd_split[1], strerror(errno));
}

void	cd_home(t_shell *_shell)
{
	char	*str;

	str = ft_getenv(_shell->env, "HOME");
	if (!chdir(str))
		ch_pwd(_shell);
	else
		printf("bash: %s: %s: %s\n", _shell->cmd_split[0], \
			_shell->cmd_split[1], strerror(errno));
	free(str);
}

void	ft_exe_cd(t_shell _shell)
{
	if (_shell.cmd_split[1] == NULL || !ft_strncmp(_shell.cmd_split[1], "~", 1))
		cd_home(&_shell);
	else
		cd_path(&_shell);
}
