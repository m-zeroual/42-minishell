#include "../../../includes/minishell.h"

int is_not_acceptable(char c)
{
    return (c < 32 || c > 126);
}

void    print_error(char *str)
{
    static int i;
    char    *text;

    text = "bash: syntax error near unexpected token `";
    if (!i)
    {
        ft_putstr_fd(text, 2);
        i = 1;
    }
    ft_putstr_fd(str, 2);
    if (str[0] == '\'')
        i = 0;
}

t_redirect  *get_redirections(char   **commands)
{
    t_redirect      *redirection;
    unsigned char   input_len;
    unsigned char   output_len;
    int             i;
    int             j;
    unsigned char   two;

    redirection = ft_calloc(100, sizeof(*redirection));
    if (!redirection)
        return (NULL);
    i = 0;
    j = 0;
    while (commands[j])
    {
        input_len = 0;
        output_len = 0;
        while (commands[j] && commands[j][0] != INPUT_REDIRECT && commands[j][0] != OUTPUT_REDIRECT)
        {
            if (commands[j][0] == PIPE)
                break ;
            (j)++;
        }
        if (commands[j] && commands[j][0] == PIPE)
            break ;
        two = 0;
        while (commands[j] && commands[j][0] == INPUT_REDIRECT)
        {
            input_len++;
            if (input_len > 3 && two < 2 && ++two)
                print_error("<");
            ft_memset(commands[j], 3, ft_strlen(commands[j]));
            (j)++;
        }
        if (!commands[j] && input_len && input_len < 4)
        {
            print_error("newline");
            input_len = 4;
        }
        if (input_len > 3)
            return (print_error("'\n"), NULL);
        two = 0;
        while (input_len != 0 && commands[j] && is_not_acceptable(commands[j][0]) && two++ < 2)
        {
            if (commands[j][0] == OUTPUT_REDIRECT || commands[j][0] == 3)
                print_error(">");
            else if (commands[j][0] == INPUT_REDIRECT)
                print_error("<");
            else if (commands[j][0] == PIPE && ++two)
                print_error("|");
            else
                print_error(commands[j]);
            (j)++;
            input_len = 200;
        }
        if (input_len == 200)
            return (print_error("'\n"), NULL);
        if (input_len != 0 && commands[j][0] != OUTPUT_REDIRECT)
        {
            redirection[i].file = ft_strdup(commands[j]);
            ft_memset(commands[j], 3, ft_strlen(commands[j]));
            redirection[i].is_input = 1;
            redirection[i].is_here_doc = 0;
            if (input_len == 2)
                redirection[i].is_here_doc = 1;
            redirection[i].is_append = 0;
            redirection[i].is_output = 0;
            redirection[i].number_of_arrow = input_len;
            i++;
            (j)++;
        }
        two = 0;
        while (commands[j] && commands[j][0] == OUTPUT_REDIRECT)
        {
            output_len++;
            if (output_len > 2 && two++ < 2)
                print_error(">");
            ft_memset(commands[j], 3, ft_strlen(commands[j]));
            (j)++;
        }
        if (!commands[j] && output_len && output_len < 3)
        {
            print_error("newline");
            output_len = 4;
        }
        if (output_len > 2)
            return (print_error("'\n"), NULL);
        two = 0;
        while (output_len != 0 && commands[j] && is_not_acceptable(commands[j][0]) && two++ < 2)
        {
            if (commands[j][0] == INPUT_REDIRECT || commands[j][0] == 3)
                print_error("<");
            else if (commands[j][0] == OUTPUT_REDIRECT)
                print_error(">");
            else if (commands[j][0] == PIPE && ++two)
                print_error("|");
            else
                print_error(commands[j]);
            (j)++;
            output_len = 200;
        }
        if (output_len == 200)
            return (print_error("'\n"), NULL);
        if (output_len != 0 && commands[j] && commands[j][0] != INPUT_REDIRECT)
        {
            redirection[i].file = ft_strdup(commands[j]);
            ft_memset(commands[j], 3, ft_strlen(commands[j]));
            redirection[i].is_input = 0;
            redirection[i].is_append = 0;
            if (output_len == 2)
                redirection[i].is_append = 1;
            redirection[i].is_here_doc = 0;
            redirection[i].is_output = 1;
            redirection[i].number_of_arrow = output_len;
            i++;
            j++;
        }
    }
    return (redirection);
}

t_redirect  *get_input_redirections(t_redirect *redirections) {
    unsigned char   i;
    t_redirect      *input;
    unsigned char   len;

    i = 0;
    len = 0;
    if (!redirections)
        return (NULL);
    while (redirections[i].file)
        if (redirections[i++].is_input == 1)
            len++;
    input = ft_calloc(len + 1, sizeof(*input));
    if (!input)
        return (0);
    i = 0;
    len = 0;
    while (redirections[i].file)
    {
        if (redirections[i].is_input == 1)
        {
            input[len].file = ft_strdup(redirections[i].file);
            input[len].is_input = 1;
            input[len].is_output = 0;
            input[len].is_here_doc = redirections[i].is_here_doc;
            input[len].is_append = 0;
            input[len].number_of_arrow = redirections[i].number_of_arrow;
            len++;
        }
        i++;
    }
    return (input);
}

t_redirect  *get_output_redirections(t_redirect *redirections) {
    unsigned char   i;
    t_redirect      *output;
    unsigned char   len;

    i = 0;
    len = 0;
    if (!redirections)
        return (NULL);
    while (redirections && redirections[i].file)
        if (redirections[i++].is_output == 1)
            len++;
    output = ft_calloc(len + 1, sizeof(*output));
    if (!output)
        return (0);
    i = 0;
    len = 0;
    while (redirections && redirections[i].file)
    {
        if (redirections[i].is_output == 1)
        {
            output[len].file = ft_strdup(redirections[i].file);
            output[len].is_input = 0;
            output[len].is_output = 1;
            output[len].is_append = redirections[i].is_append;
            output[len].is_here_doc = 0;
            output[len].number_of_arrow = redirections[i].number_of_arrow;
            len++;
        }
        i++;
    }
    return (output);
}

void    free_t_redirect(t_redirect *redirect) {
    unsigned char   i;

    if (!redirect)
        return ;
    i = 0;
    while (redirect[i].file)
        free(redirect[i++].file);
    ft_bzero(redirect, sizeof(*redirect));
    free(redirect);
}

t_redirect *create_output_files(t_redirect *output)
{
    int i;
    int fd;
    t_redirect  *last_file;

    if (!output || !output[0].file)
        return (NULL);
    i = 0;
    last_file = ft_calloc(1, sizeof(*last_file));
    if (!last_file)
        return (NULL);
    if (output[i].is_append)
        fd = open(output[i].file, O_CREAT | O_APPEND, 0644);
    else
        fd = open(output[i].file, O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        ft_putstr_fd("bash: ", 2);
        ft_putstr_fd(output[i - 1].file, 2);
        ft_putstr_fd(": Not a directory\n", 2);
        return (NULL);
    }
    i++;
    while (output[i].file)
    {
        close(fd);
        if (output[i].is_append)
            fd = open(output[i++].file, O_CREAT | O_APPEND, 0644);
        else
            fd = open(output[i++].file, O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            ft_putstr_fd("bash: ", 2);
            ft_putstr_fd(output[i - 1].file, 2);
            ft_putstr_fd(": Not a directory\n", 2);
            return (NULL);
        }
    }
    last_file->file = ft_strdup(output[i - 1].file);
    last_file->is_append = output[i - 1].is_append;
    last_file->is_output = output[i - 1].is_output;
    last_file->is_input = 0;
    last_file->is_here_doc = 0;
    last_file->number_of_arrow = output[i - 1].number_of_arrow;
    free_t_redirect(output);
    return (last_file);
}

t_redirect  *get_input_file(t_redirect *inputs) {
    int i;
    int index;
    t_redirect  *last_file;

    i = -1;
    index = 0;
    if (!inputs)
        return (NULL);
    last_file = ft_calloc(3, sizeof(*last_file));
    if (!last_file)
        return (NULL);
    while (inputs[++i].file)
        if (inputs[i].is_here_doc)
            index = i;
    if (!i)
        return (NULL);
    last_file->file = ft_strdup(inputs[i - 1].file);
    last_file->is_here_doc = inputs[i - 1].is_here_doc;
    last_file->is_input = inputs[i - 1].is_input;
    last_file->is_output = 0;
    last_file->is_append = 0;
    last_file->number_of_arrow = inputs[i - 1].number_of_arrow;
    if (index != i - 1)
    {
        last_file++;
        last_file->file = ft_strdup(inputs[index].file);
        last_file->is_here_doc = inputs[index].is_here_doc;
        last_file->is_input = inputs[index].is_input;
        last_file->is_output = 0;
        last_file->is_append = 0;
        last_file->number_of_arrow = inputs[index].number_of_arrow;
        last_file--;
    }
    free_t_redirect(inputs);
    return (last_file);

}

char    *get_here_doc_content(char  *eol) {
    int i;
    int len;
    char    *string;
    char    *line;
    char    *tmp;

    if (!eol)
        return (0);
    i = 0;
    len = ft_strlen(eol);
    string = ft_calloc(2, sizeof(*string));
    if (!string)
        return (NULL);
    while (1)
    {
        line = readline("> ");
        if (!line)
            return (NULL);
        if (!ft_strncmp(line, eol, len + 1))
        {
            len = ft_strlen(string);
            if (len)
                string[len - 1] = 0;
            break;
        }
        tmp = ft_strjoin(string, line);
        free(string);
        string = ft_strjoin(tmp, "\n");
        free(tmp);
        free(line);
    }
    return (string);
}

int parsing_redirection(t_content *content, char **redirections)
{
    t_redirect *redirect;

    if (!redirections || !*redirections)
        return (0);
    redirect = get_redirections(redirections);
    if (!redirect)
        return (0);
    //TODO: protect this variables
    content->output_redirections = create_output_files(get_output_redirections(redirect));
    content->input_redirections = get_input_file(get_input_redirections(redirect));
    free_t_redirect(redirect);
    return (1);
}
//        printf("file_name = |%s|\tis_append = |%d|\tis_string = |%d|\tis_here_doc = |%d|\tis_input = |%d|\tis_output = |%d|\tnumber_of_arrow = |%d|\n", redirect[i].file, redirect[i].is_append, redirect[i].is_string, redirect[i].is_here_doc,redirect[i].is_input, redirect[i].is_output, redirect[i].number_of_arrow);
