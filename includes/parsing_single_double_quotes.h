/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_single_double_quotes.h                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:05:45 by esalim            #+#    #+#             */
/*   Updated: 2023/06/05 17:39:40 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_SINGLE_DOUBLE_QUOTES_H
# define PARSING_SINGLE_DOUBLE_QUOTES_H

# include "minishell.h"
# include "execution.h"

# define    SEPARATOR           4
# define    PIPE                5
# define    INPUT_REDIRECT      6
# define    OUTPUT_REDIRECT     7

char	*get_variable_name(char **line);

//PATH:	src/parsing_args/parsing_single_double_quotes/parsing_single_double_quotes_utils.c
int		is_only_three(char *str);
void    free_double_pointer(char **str);
int     get_separator(char *str, char *separ);
int		get_lenght_of_list_without_three(char **str);
char    **get_list_without_three(char **dpointer, int len);

//PATH:	src/parsing_args/parsing_single_double_quotes/checking.c
void	check_errors(char **dest, char **line, int *index);
int		check_conditions(t_shell *shell, char **dest, char **line);
void	check_pipe_redir(t_shell *shell, char	**line, char **dest, int *j);

//PATH:	src/parsing_args/parsing_single_double_quotes/parsing_single_double_quotes.c
void	append_to_dest(t_shell *shell, char **dest, char **line, int *j);
int		set_dest(t_shell *shell, char **dest, char **line, int *a);
char	*handle_line(t_shell *shell, char *line);
char	**split_line(t_shell *shell, char *line);
char	**parsing_single_double_quotes(t_shell *shell, char *args);

//PATH:	src/parsing_args/parsing_single_double_quotes/parsing_single_double_quotes_tools.c
void	replace_chars(char	*str);
void	replace_chars_rev(char *str);
void	switch_a(char **line, int *a, char separator);
void	search_and_replace(char *src, char search, char replace);

#endif
