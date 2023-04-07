#ifndef PARSING_SINGLE_DOUBLE_QUOTES_H
# define PARSING_SINGLE_DOUBLE_QUOTES_H

# include "minishell.h"

void	free_double_pointer(char **str);
int		get_separator(char *str, char *separ);
char	**get_list_without_spaces(char **dpointer, int len);
int		set_dest(char **dest, char **line, int *a, int j);
char	*hundle_line(char *line);
char	**split_line(char *line);
char	**parsing_args(char *args);

#endif