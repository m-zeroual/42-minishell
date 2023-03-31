#include "../../includes/minishell.h"

/**
 *  TODO:this function return the first (single | double) quates character in the string
 */

char    get_separator(char *str)
{
    int i;

    i = -1;
    if (!str || !*str)
        return (0);
    while (str[++i])
        if (str[i] == '\'' || str[i] == '"')
            return (str[i]);
    return (0);
}

/**
 *  TODO: count how many chararcters in string except single quates or double quates ( " || ' )
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
    separator = get_separator(str);
    while (str[++i])
        if (str[i] != separator)
            len++;
    return (len);
}

/**
 *  TODO:   hundle the first command
 *  @CASES:
 *      double quates: "l""s"   ==> ls
 *      single quates: 'l''s'   ==> ls
 *      mix quates   : "l"""''"s" ==> ls
 *      redirection to input: < file1
 *
 */

char    *hundle_first_part(char *first_part) {
    char    *dest;
    int     i;
    int     j;
    char    separator;

    if (!first_part || !*first_part)
        return (0);
    dest = malloc(count_chars(first_part) + 1);
    if (!dest)
        return (NULL);
    i = 0;
    j = 0;
    int a = 0;
    char *str = first_part;
    while (*first_part)
    {
        separator = get_separator(first_part);
        while (separator && *first_part == separator)
        {
            first_part++;
            a = !a;
        }
        while (*first_part && *first_part != separator)
            dest[j++] = *(first_part++);
        if (separator && *first_part == separator)
        {
            first_part++;
            printf("close quates\n");
            a = !a;
        }
    }
    first_part = str;
    if (a)
        printf("Error : you messing a separator\n");
    dest[j] = 0;
    free(first_part);
    return (dest);
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
        char *getLine = "'\"'l\"'\"'s'\"s'\"";//readline("minishell $> ");
        char *line = ft_strtrim(getLine, " \t\n");
        split_line(line);
        break ;
        //ft_printf("%s\n", str);
        //system(str);
    }
    return (0);
}
