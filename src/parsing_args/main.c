#include "../../includes/minishell.h"

/**
 *  this function return the index of the first (single | double)
 *  quotes character in the string and set separ to this character
 *  EXAMPLE:
 *      str = `ls -"'a'" -'l'`  ==> separ = `"` | return 4
 */
int    get_separator(char *str, char *separ)
{
    int i;

    i = -1;
    if (!str || !*str)
        return (0);
    while (str[++i])
    {
        if (str[i] == '\'' || str[i] == '"')
        {
            *separ = str[i];
            return (i);
        }
    }
    return (i);
}

/**
 *  hundle the line by removing double and single quotes and return string
 *  separed by 5 ascii characher 
 *  EXAMPLE:
 *      "p""w"'d'  ==> "`pwd`"
 *      ""l's' "-a" '-l' ""-R  =>  "`ls` `-a` `-l` `-R`"
 */
char    *hundle_line(char *line)
{
    char    *dest;
    int     j;
    int     a;
    int     separ_index;
    char    separator;
    char    *tmp;

    if (!line || !*line)
        return (0);
    dest = ft_calloc(ft_strlen(line) * 2 + 1, sizeof *dest);
    if (!dest)
        return (NULL);
    tmp = line;
    j = 0;
    a = 0;
    dest[j++] = 5;
    while (*line)
    {
        separ_index = get_separator(line, &separator);
        while (separ_index-- > 0 && *line)
        {
            if (!a && *line == ' ')
                dest[j++] = 5;
            dest[j++] = *(line++);
            if (!a && *(line - 1) == ' ' && *line != ' ')
                dest[j++] = 5;
        }
        if (*line && *line == separator && line++)
            a = !a;
        while (*line && *line != separator)
        {
            if (!a && *line == ' ')
                dest[j++] = 5;
            dest[j++] = *(line++);
            if (!a && *(line - 1) == ' ' && *line != ' ')
                dest[j++] = 5;
        }
        if (*line && *line == separator && line++)
            a = !a;
    }
    if (!a && !*line)
        dest[j++] = 5;
    if (a)
        printf("Error : you messing a separator\n");
    dest[j] = 0;
    free(tmp);
    tmp = ft_strdup(dest);
    free(dest);
    return (tmp);
}

/**
 *  this function will be free the double pointer that you giving to him
 */
void    free_double_pointer(char **str)
{
    int i;

    i = 0;
    if (!str || !*str)
        return ;
    while (str[i])
        free(str[i++]);
    free(str);
}

/**
 *  this function takes double pointer and trim all strings from it and return
 *  a double pointer without any Extra spaces
 *  EXAMPLE:
 *      {"ls", "     ", "-a", "   -l  ", " ", "-R ", "  "}  ==>  {"ls", "-a", "-l", "-R"}
 *
 */
char    **get_list_without_spaces(char **dpointer, int len)
{
    char    **result;
    char    *tmp;
    int     i;
    int     j;

    if (!dpointer || !*dpointer)
        return (0);
    result = ft_calloc(len + 1, sizeof *result);
    if (!result)
        return (free_double_pointer(dpointer), NULL);
    j = 0;
    i = -1;
    while (dpointer[++i])
    {
        tmp = ft_strtrim(dpointer[i], " \t\n");
        if (tmp)
        {
            result[j++] = ft_strdup(tmp);
            free(tmp);
        }
    }
    return (free_double_pointer(dpointer), result);
}

/**
 *  split the string returned by hundle_line() function using 5 ascii character
 *  and trim all space in right and left side of each string and retun double
 *  pointer that pointing to the first string.
 *  ft_split(str, 5);
 *  ft_strtrim(str, " \t\n");
 *  EXAMPLE:
 *      "`ls` `-a` `-l` `-R`"  =>  {"ls", "-a", "-l", "-R"}
 */
char    **split_line(char *line)
{
    char    *line_after_hundling;
    char    *tmp;
    char    **str; 
    int     i;
    int     len;

    line_after_hundling = hundle_line(line);
    if (!line_after_hundling)
        return (0);
    str = ft_split(line_after_hundling, 5);
    free(line_after_hundling);
    if (!str)
        return (0);
    i = -1;
    len = 0;
    while (str[++i])
    {
        tmp = ft_strtrim(str[i], " \t\n");
        if (tmp)
        {
            len++;
            free(tmp);
        }
    } 
    return (get_list_without_spaces(str, len));
}

/**
 *  the function will remove all extra space in left and right of args and
 *  after that spliting him by using split_line() function, and return the
 *  result of last funtion
 *  `   "ls" "-a" "-l" -R   ` ==> `"ls" "-a" "-l" -R`
 */
char    **parsing_args(char *args)
{
    char    *line;

    if (!args || !*args)
        return (0);
    line = ft_strtrim(args, " \t\n");
    if (!line)
        return (0);
    return (split_line(line));
}

int main(void) {
    while (1)
    {
        char *getLine = readline("minishell $> ");
        char    **commands = parsing_args(getLine);
        while (*commands)
            printf("|%s|\n", *(commands++));
        free(getLine);
    }
    return (0);
}
