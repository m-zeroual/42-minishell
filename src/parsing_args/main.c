#include "../../includes/minishell.h"

/**
 *  TODO:this function return the first (single | double) quotes character in the string
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
            separ[0] = str[i];
            return (i);
        }
    }
    return (i);
}

/**
 *  TODO: count how many chararcters in string except single quotes or double quotes ( " || ' )
 */

size_t  count_chars(char *str)
{
    char    separator;
    int     i;
    size_t  len;

    if (!str || !*str)
        return (0);
    i = -1;
    len = 0;
    get_separator(str, &separator);
    while (str[++i])
        if (str[i] != separator)
            len++;
    return (len);
}

/**
 *  TODO:   hundle the first command
 *  @CASES:
 *      double quotes: "l""s"   ==> ls
 *      single quotes: 'l''s'   ==> ls
 *      mix quotes   : "l"""''"s" ==> ls
 *      redirection to input: < file1
 *
 */



char    *hundle_line(char *line) {
    char    *dest;
    int     j;
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
    int a = 0;
    dest[j++] = '`';
    while (*line)
    {
        separ_index = get_separator(line, &separator);
        while (separ_index-- > 0 && *line)
        {
            if (!a && *line == ' ')
                dest[j++] = '`';
            dest[j++] = *(line++);
            if (!a && *(line - 1) == ' ' && *line != ' ')
                dest[j++] = '`';
        }
        if (*line && *line == separator && line++)
            a = !a;
        while (*line && *line != separator)
        {
            if (!a && *line == ' ')
                dest[j++] = '`';
            dest[j++] = *(line++);
            if (!a && *(line - 1) == ' ' && *line != ' ')
                dest[j++] = '`';
        }
        if (*line && *line == separator && line++)
            a = !a;
    }
    if (!a && !*line)
        dest[j++] = '`';
    if (a)
        printf("Error : you messing a separator\n");
    dest[j] = 0;
    free(tmp);
    tmp = ft_strdup(dest);
    free(dest);
    return (tmp);
}


/**
 * @Function: char  **split_line(char *line);
 *
 *  Split  Line to two part. first part contains commands and second part contains options and args
 *  example :
 *      line = "echo 'hello  world'";
 *      part 1 = "echo"
 *      part 2 = "hello  world";
 *
 * @PARAM   char *line 
 *
 * @RETURN double pointer that contains data splited
 *
 */

char    **split_line(char *line)
{
    char    *first_part;
    first_part = hundle_line(line);
    ft_printf("part -1 |%s|\n", first_part);
    char **str = ft_split(first_part, '`');
    int i = -1;
    while (str[++i])
    {
        char *tmp = ft_strtrim(str[i], " \t\n");
        if (tmp)
            ft_printf("part %d |%s|\n", i, tmp);
        free(tmp);
    }
    return (0);
}

/*
char    *parsing_first_command(char *line)
{

}
*/
int main(void) {
    while (1)
    {
        char *getLine = /*"'\"'l\"'\"'s'\"s'\"";*/readline("minishell $> ");
        char *line = ft_strtrim(getLine, " \t\n");
        split_line(line);
        //ft_printf("%s\n", str);
        //system(str);
    }
    return (0);
}
