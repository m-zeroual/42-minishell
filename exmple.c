// while (_shell->pipes && ++(_shell->i))
// {
// 	printf("----------node[%d]----------\n", _shell->i);
// 	int j = 0;
// 	while (_shell->pipes->content->commands[j])
// 		printf("|%s|\n", _shell->pipes->content->commands[j++]);
// 	// printf("|%p||%p|\n", _shell->pipes->content->input_redirections, &_shell->pipes->content->input_redirections->file);
// 	j = 0;
// 	printf("--input--\n");
// 	while (_shell->pipes->content->input_redirections && _shell->pipes->content->input_redirections[j].file)
// 	{
// 		printf("|%s|\n", _shell->pipes->content->input_redirections[j].file);
// 		printf("|%d|\n", _shell->pipes->content->input_redirections[j].is_input);
// 		printf("|%d|\n", _shell->pipes->content->input_redirections[j].is_output);
// 		printf("|%d|\n", _shell->pipes->content->input_redirections[j].is_append);
// 		printf("|%d|\n", _shell->pipes->content->input_redirections[j++].is_here_doc);
// 	}
// 	printf("--output--\n");
// 	j = 0;
// 	while (_shell->pipes->content->output_redirections && _shell->pipes->content->output_redirections[j].file)
// 	{
// 		printf("|%s|\n", _shell->pipes->content->output_redirections[j].file);
// 		printf("|%d|\n", _shell->pipes->content->output_redirections[j].is_input);
// 		printf("|%d|\n", _shell->pipes->content->output_redirections[j].is_output);
// 		printf("|%d|\n", _shell->pipes->content->output_redirections[j].is_append);
// 		printf("|%d|\n", _shell->pipes->content->output_redirections[j++].is_here_doc);
// 	}
// }

// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <string.h>

// int main()
// {
// 	char	**s = malloc(16);
// 	s[0] = "./script.sh";
// 	s[1] = NULL;
// 	if (execve("./", s, NULL) == -1)
// 		printf("dsgsfg\n");
// 	return 0;
// }


//execDemo.c
 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
        //A null terminated array of character
        //pointers
        char *str[]={"script", 0};
        execve("./script.sh",str, 0);
     
        /*All statements are ignored after execvp() call as this whole
        process(execDemo.c) is replaced by another process (EXEC.c)
        */
        printf("Ending-----");
     
    return 0;
}