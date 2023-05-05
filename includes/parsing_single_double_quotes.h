#ifndef PARSING_SINGLE_DOUBLE_QUOTES_H
# define PARSING_SINGLE_DOUBLE_QUOTES_H

# include "minishell.h"
# include "execution.h"

# define    SEPARATOR           4
# define    PIPE                5
# define    INPUT_REDIRECT      6
# define    OUTPUT_REDIRECT     7

void	free_double_pointer(char **str);
int		get_separator(char *str, char *separ);
char	**get_list_without_three(char **dpointer, int len);
int     set_dest(t_shell *shell, char **dest, char **line, int *a, int j);
char    *handle_line(t_shell *shell, char *line);
char	**split_line(t_shell *shell, char *line);
char	**parsing_single_double_quotes(t_shell *shell, char *args);
int     get_lenght_of_list_without_three(char **str);

#endif
