#ifndef PARSING_REDIRECTION_AND_PIPES_H
# define PARSING_REDIRECTION_AND_PIPES_H

t_list      *parsing_pipes(char  **commands);
t_redirect  *get_redirections(char   **commands);
int         parsing_redirection(t_content *content, char **redirections);
char        *get_here_doc_content(char  *eol);
t_redirect  *get_input_file(t_redirect *inputs);
t_redirect  *create_output_files(t_redirect *output);

#endif
