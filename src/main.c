/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:15:40 by esalim            #+#    #+#             */
/*   Updated: 2023/06/08 20:16:52 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	_shell;

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		// printf("\n");
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
		rl_catch_signals = 1;
		_shell.status = 1;
		close(0);
	}
}

int	main(int ac, char *av[], char *ev[])
{

	(void)ac;
	(void)av;
	signal(SIGINT, sig_handler);
	_shell.env = ft_fill_env(ev, ft_count_env(ev));
	_shell.status = 0;
	_shell.command_with_path = NULL;
	_shell.here_doc_parsing = 1;
	_shell.fd = dup(0);
	while (1)
	{
		rl_catch_signals = 0;
		dup2(_shell.fd, 0);
		_shell.line = readline("minishell -> ");
		if (!_shell.line)
		{
			if (rl_catch_signals == 0)
				exit(_shell.status);
			else
			{
				_shell.status = 1;
				continue ;
			}
		}
		minishell(&_shell);
		system("leaks minishell");
	}
	return (0);
}
