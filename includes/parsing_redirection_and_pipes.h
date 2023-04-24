#ifndef PARSING_REDIRECTION_AND_PIPES_H
# define PARSING_REDIRECTION_AND_PIPES_H

//PATH: src/parsing_args/parsing_pipes_and_redirections/parsing_pipes/parsing_pipes_utils.c
int         get_number_of_commands(char **commands, int j);
int         get_number_of_pipe(char **commands);

//PATH: src/parsing_args/parsing_pipes_and_redirections/parsing_pipes/parsing_pipes.c
t_list    *parsing_pipes(char  **commands);

//PATH: src/parsing_args/parsing_pipes_and_redirections/parsing_redirections/parsing_redirection.c
t_redirect  *get_redirections(char   **commands);
void    set_redirections(t_redirect *redirection, char *str, char is_input, int len);
t_redirect  *get_input_redirections(t_redirect *redirections);
t_redirect  *get_output_redirections(t_redirect *redirections);
int parsing_redirection(t_content *content, char **redirections);

//PATH: src/parsing_args/parsing_pipes_and_redirections/parsing_redirections/parsing_redirection_utils.c
int         check_permissions(char  *filename, char *permissions);
void        free_t_redirect(t_redirect *redirect);
t_redirect  *create_output_files(t_redirect *output);
t_redirect  *get_input_file(t_redirect *inputs);
char        *get_here_doc_content(char  *eol);

//PATH: src/parsing_args/parsing_pipes_and_redirections/parsing_redirections/parsing_redirection_tools.c
int     skip_commands(char **commands, int *j);
int     redirect_len(char **commands, int *j, char c, char *print_c);
int     check_redirection_error(char **cmds, int *j, int len, int swap);
int     for_each_command(t_redirect *redirection, char **commands, int *i, int *j);
void    init_t_redirect(t_redirect *dest, t_redirect *src);

//PATH: src/parsing_args/main_parsing.c
t_list  *main_parsing(char   *getLine);
void    setup_here_doc(char *string, int fds[2]);
char    *get_random_name(int len);
int     setup_output_redirections(t_redirect *output, int *pipe_fds, int has_next, int has_prev);
int     setup_input_redirections(t_redirect *input, char **str, int *pipe_fds, int has_next);


t_list      *parsing_pipes(char  **commands);
t_redirect  *get_redirections(char   **commands);
int         parsing_redirection(t_content *content, char **redirections);
char        *get_here_doc_content(char  *eol);
t_redirect  *get_input_file(t_redirect *inputs);
t_redirect  *create_output_files(t_redirect *output);

void    free_t_redirect(t_redirect *redirect);

void    p_error(char *str);

#endif
