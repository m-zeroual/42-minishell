#ifndef PARSING_SINGLE_DOUBLE_QUOTES_H
# define PARSING_SINGLE_DOUBLE_QUOTES_H

# include "minishell.h"
# include "execution.h"

# define    SEPARATOR           4
# define    PIPE                5
# define    INPUT_REDIRECT      6
# define    OUTPUT_REDIRECT     7


typedef struct s_data
{
    t_shell *shell;
    char    *line;
    char    *dest;
    char    separator;
    int     a;
    int     index;
}   t_data;

// void	free_double_pointer(char **str);
// int		get_separator(char *str, char *separ);
// char	**get_list_without_three(char **dpointer, int len);
// int     set_dest(t_data *data);
// char    *handle_line(t_data *data);
// char	**split_line(t_data *data);
// char	**parsing_single_double_quotes(t_shell *shell, char *args);
// int     get_lenght_of_list_without_three(char **str);

// char	*get_value(t_data *data, char separ);
char	*get_variable_name(char **line);

void    free_double_pointer(char **str);
int             get_separator(char *str, char *separ);
char    **get_list_without_three(char **dpointer, int len);
int     set_dest(t_shell *shell, char **dest, char **line, int *a);
char    *handle_line(t_shell *shell, char *line);
char    **split_line(t_shell *shell, char *line);
char    **parsing_single_double_quotes(t_shell *shell, char *args);
int     get_lenght_of_list_without_three(char **str);


#endif
