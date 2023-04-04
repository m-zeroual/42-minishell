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

char    *hundle_first_part(char *first_part) {
    char    *dest;
    int     i;
    int     j;
    int     separ_index;
    char    separator;
    char    *tmp;

    if (!first_part || !*first_part)
        return (0);
    tmp = first_part;
    dest = malloc(count_chars(first_part) + 1);
    if (!dest)
        return (NULL);
    i = 0;
    j = 0;
    int a = 0;
    while (*first_part)
    {
        i = 0;
        separ_index = get_separator(first_part, &separator);
        while (i++ < separ_index)
            dest[j++] = *(first_part++);
        if (*first_part == separator && first_part++)
            a = !a;
        while (*first_part && *first_part != separator)
            dest[j++] = *(first_part++);
        if (*first_part == separator && first_part++)
            a = !a;
    }
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
    char    *second_part;
    char    *tmp;
    int     end_of_part_1;

    tmp = ft_strchr(line, ' ');
    end_of_part_1 = tmp - line;
    if (!tmp && end_of_part_1 <= 0)
    {
        end_of_part_1 = ft_strlen(line) + 1;
        second_part = 0;
    }
    else
        second_part = ft_strtrim(tmp, " ");
    first_part = ft_strndup(line, end_of_part_1);
    first_part = hundle_first_part(first_part);
    ft_printf("part 1 = |%s|\npart 2 = |%s|\n", first_part, second_part);
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
