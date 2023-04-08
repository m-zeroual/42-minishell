#ifndef PARSING_REDIRECTION_AND_PIPES_H
# define PARSING_REDIRECTION_AND_PIPES_H

void    parsing_pipes(char  **commands);
t_redirect  *get_redirections(char   **commands, int *j);
int parsing_redirection(char **redirections, int *j);

#endif
