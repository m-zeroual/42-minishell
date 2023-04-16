#include "../includes/minishell.h"

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

int main(int ac, char *av[], char *ev[])
{
	t_shell _shell;
	
	// (void)ac;
	// (void)av;
	// (void)ev;
	// signal(SIGINT, sig_handler);

	_shell.ac = ac;
	_shell.av = av;
	_shell.ev = ev;
	_shell.export = ft_fill_env(_shell.ev, ft_count_env(_shell.ev));
	_shell.env = ft_fill_env(_shell.ev, ft_count_env(_shell.ev));
	while (1)
		ft_exe(&_shell);
	return (0);
}
