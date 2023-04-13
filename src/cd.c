#include "../includes/main.h"

void cd_home(t_shell *_shell)
{
	if (!chdir(getenv("HOME")))
			ch_pwd(_shell);
		else
			printf("bash: %s: %s: %s\n", _shell->cmd_split[0], _shell->cmd_split[1], strerror(errno));
}

// void cd_root(t_shell *_shell)
// {
// 	if (!chdir(_shell->cmd_split[1]))
// 			ch_pwd(_shell);
// 		else
// 			printf("bash: %s: %s: %s\n", _shell->cmd_split[0], _shell->cmd_split[1], strerror(errno));
// }

// void cd_2dots(t_shell *_shell)
// {
// 	if (!chdir(_shell->cmd_split[1]))
// 			ch_pwd(_shell);
// 		else
// 			printf("bash: %s: %s: %s\n", _shell->cmd_split[0], _shell->cmd_split[1], strerror(errno));
// }
void cd_path(t_shell *_shell)
{

	if (!chdir(_shell->cmd_split[1]))
		ch_pwd(_shell);
	else
		printf("bash: %s: %s: %s\n", _shell->cmd_split[0], _shell->cmd_split[1], strerror(errno));
}