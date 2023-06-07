/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:15:40 by esalim            #+#    #+#             */
/*   Updated: 2023/06/07 16:43:53 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		// rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		// close(0);
	}
}

int	main(int ac, char *av[], char *ev[])
{
	t_shell	_shell;
	// int		fd;

	(void)ac;
	(void)av;
	signal(SIGINT, sig_handler);
	_shell.env = ft_fill_env(ev, ft_count_env(ev));
	_shell.status = 0;
	_shell.command_with_path = NULL;
	_shell.here_doc_parsing = 1;
	// fd = dup(0);
	while (1)
	{
		// dup2(fd, 0);
		// rl_catch_signals = 1;
		minishell(&_shell);
		// system("leaks minishell");
	}
	return (0);
}
