#include "../includes/minishell.h"




// char	*get_pid()
// {
// 	int	pid;
// 	int	fds[2];
//     char *str[] = {"bash", "-c", "pgrep minishell", 0};

// 	pipe(fds);
// 	pid = fork();
// 	if (!pid)
// 	{

// 		close(fds[0]);
// 		dup2(fds[1], 1);
// 		close(fds[1]);
// 		if (execve("/bin/bash", str, 0) == -1)
// 			ft_printf("hello\n");
// 		exit(0);
// 	}
// 	wait(NULL);
// 	// close(fds[1]);
// 	char str2[50];// = ft_calloc(17, 1);
// 	read(fds[0], str2, 7);
// 	return (ft_strdup(str2));
// }

void sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
        // rl_replace_line("", 0);
        rl_redisplay();	
	}
}

int	main(int ac, char *av[], char *ev[])
{
	t_shell	_shell;
	
	(void)ac;
	(void)av;
	signal(SIGINT, sig_handler);
	_shell.env = ft_fill_env(ev, ft_count_env(ev));
	_shell.status = 0;
	while (1)
		minishel(&_shell);
	return (0);
}