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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void ft()
{
	char *str = malloc(1);
   str = 0;	
}
int main(int argc, char const *argv[], char **env)
{
	ft();
	while (1);
	return 0;
}
