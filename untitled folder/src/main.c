/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:15:40 by esalim            #+#    #+#             */
/*   Updated: 2023/06/09 15:00:13 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_catch_signals = 1;
		close(0);
	}
	else if (sig == SIGQUIT)
		return ;
}

void	ft_init_struct(t_shell *_shell, char *ev[])
{
	_shell->env = ft_fill_env(ev, ft_count_env(ev));
	_shell->status = 0;
	_shell->here_doc_parsing = 1;
	_shell->command_with_path = NULL;
	_shell->fd = dup(0);
}

int	main(int ac, char *av[], char *ev[])
{
	t_shell	_shell;

	(void)ac;
	(void)av;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	ft_init_struct(&_shell, ev);
	while (1)
	{
		rl_catch_signals = 0;
		dup2(_shell.fd, 0);
		_shell.line = readline("minishell -> ");
		if (!_shell.line)
		{
			if (rl_catch_signals)
			{
				_shell.status = 1;
				continue ;
			}
			ft_printf("exit\n");
			exit(_shell.status);
		}
		minishell(&_shell);
	}
	return (close(_shell.fd), 0);
}
