#include "../../includes/minishell.h"

static void	ft_chdir(t_shell *_shell, char *str)
{
	if (!chdir(str))
		ch_pwd(_shell);
	else
		printf("bash: %s: %s: %s\n", _shell->cmd_split[0], \
			_shell->cmd_split[1], strerror(errno));
}

void	ft_exe_cd(t_shell *_shell)
{
	char	*str;

	if (_shell->cmd_split[1] == NULL
		|| !ft_strncmp(_shell->cmd_split[1], "~", 1))
	{
		str = ft_getenv(_shell->env, "HOME");
		ft_chdir(_shell, str);
		free(str);
	}	
	else
		ft_chdir(_shell, _shell->cmd_split[1]);
}
