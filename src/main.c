/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:15:40 by esalim            #+#    #+#             */
/*   Updated: 2023/06/08 22:46:02 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	g_shell;

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_catch_signals = 1;
		g_shell.status = 1;
		close(0);
	}
	else if (sig == SIGQUIT)
		return ;
}

int	main(int ac, char *av[], char *ev[])
{
	(void)ac;
	(void)av;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	g_shell.env = ft_fill_env(ev, ft_count_env(ev));
	g_shell.status = 0;
	g_shell.here_doc_parsing = 1;
	g_shell.command_with_path = NULL;
	g_shell.fd = dup(0);
	while (1)
	{
		rl_catch_signals = 0;
		dup2(g_shell.fd, 0);
		g_shell.line = readline("minishell -> ");
		if (!g_shell.line)
		{
			if (rl_catch_signals)
			{
				g_shell.status = 1;
				continue ;
			}
			exit(g_shell.status);
		}
		minishell(&g_shell);
	}
	return (close(g_shell.fd), 0);
}
