/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:59:20 by esalim            #+#    #+#             */
/*   Updated: 2023/06/07 17:01:54 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include "parsing_single_double_quotes.h"
# include "parsing_redirection_and_pipes.h"
# include <readline/readline.h>
# include "execution.h"
# include "expanding.h"
# include "errors.h"
# include <fcntl.h>

int		**get_pipes(int size);
void	create_pipes(t_list *pipes);
void	close_all_pipes(t_content *content);
void	free_struct(t_shell *_shell, t_list *tmp);

void	setup_all(t_shell *_shell);
char	**duplicate_dpointer(char **src);
void	del_content(void *cont);
void	replace_symbols(char *str);
void	replace_symbols_rev(char *str);

void	free_t_redirect_2(t_redirect *redirect);

#endif
