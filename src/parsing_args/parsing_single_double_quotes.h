#ifndef PARSING_SINGLE_DOUBLE_QUOTES_H
# define PARSING_SINGLE_DOUBLE_QUOTES_H

# include "../../includes/minishell.h"

void	free_double_pointer(char **str);
int		get_separator(char *str, char *separ);
char	**get_list_without_spaces(char **dpointer, int len);

#endif