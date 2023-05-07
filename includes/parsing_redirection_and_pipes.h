#ifndef PARSING_REDIRECTION_AND_PIPES_H
# define PARSING_REDIRECTION_AND_PIPES_H

#include "execution.h"

//PATH: src/parsing_args/parsing_pipes_and_redirections/parsing_pipes/parsing_pipes_utils.c
int         get_number_of_commands(char **commands, int j);
int         get_number_of_pipe(char **commands);

//PATH: src/parsing_args/parsing_pipes_and_redirections/parsing_pipes/parsing_pipes.c
t_list    *parsing_pipes(t_shell *shell, char  **commands);

//PATH: src/parsing_args/parsing_pipes_and_redirections/parsing_redirections/parsing_redirection.c
t_redirect  *get_redirections(t_shell *shell, char   **commands);
void    set_redirections(t_redirect *redirection, char *str, char is_input, int len);
t_redirect  *get_input_redirections(t_redirect *redirections);
t_redirect  *get_output_redirections(t_redirect *redirections);
int	parsing_redirection(t_shell *shell, t_content *content, char **redirections);

//PATH: src/parsing_args/parsing_pipes_and_redirections/parsing_redirections/parsing_redirection_utils.c
int         check_permissions(t_shell *shell, char  *filename, char *permissions);
void        free_t_redirect(t_redirect *redirect);
t_redirect	*create_output_files(t_shell *shell, t_redirect *output, char *error);
t_redirect  *get_input_file(t_shell *shell, t_redirect *inputs, char *error);
char        *get_here_doc_content(t_shell *_shell, char  *eol);

//PATH: src/parsing_args/parsing_pipes_and_redirections/parsing_redirections/parsing_redirection_tools.c
int     skip_commands(char **commands, int *j);
int     redirect_len(char **commands, int *j, char c, char *print_c);
int     check_redirection_error(char **cmds, int *j, int len, int swap);
int     for_each_command(t_redirect *redirection, char **commands, int *i, int *j);
void    init_t_redirect(t_redirect *dest, t_redirect *src);

//PATH: src/parsing_args/main_parsing.c
t_list  *main_parsing(t_shell *shell, char   *getLine);
void    setup_here_doc(char *string);
int     setup_input_redirections(t_shell *_shell, char **str);
int     setup_output_redirections(t_list *pipe);



void    p_error(char *str);
void	search_and_replace(char *src, char search, char replace);

#endif
