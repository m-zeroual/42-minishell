/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:15:40 by esalim            #+#    #+#             */
/*   Updated: 2023/06/01 16:44:34 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}
		// rl_replace_line("", 0);

int	main(int ac, char *av[], char *ev[])
{
	t_shell	_shell;

	(void)ac;
	(void)av;
	signal(SIGINT, sig_handler);
	_shell.env = ft_fill_env(ev, ft_count_env(ev));
	_shell.status = 0;
	_shell.here_doc_parsing = 1;
	while (1)
	{
		system("leaks minishell");
		minishell(&_shell);
	}
	return (0);
}
