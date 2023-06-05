/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:51:22 by esalim            #+#    #+#             */
/*   Updated: 2023/06/05 11:59:59 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDING_H
#define EXPANDING_H

#include "minishell.h"

//PATH: src/parsing_args/expanding_varaibles/expanding.c
void	expand_exit_status(t_shell *shell, char **dest, char **line, int *j);
void	expand_redirections(t_shell *shell, char **dest, char **line, int *j);
void	expanding(t_shell *shell, char **dest, char **line, int *j);
void	expanding_variables(t_shell *shell, char **dest, char **line, int *j);

//PATH: src/parsing_args/expanding_varaibles/expanding_utils.c
char	*get_value(t_shell *shell, char **line);
char	*get_variable_name(char **line);

#endif