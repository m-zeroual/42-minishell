#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
int main()
{
	char *s = "USER";
	printf("%s\n", getcwd(s, PATH_MAX));
	//printf("%s\n", s);
	//int p = fork();
	//if (p == 1)
	//	execv("/bin/pwd", NULL);
	//wait(0);
	//char *str = getcwd("HOME", 1024);
	//chdir(str);
	//free(str);
	//p = fork();
//	if (p == 1)
//		execv("/bin/pwd", NULL);
//	wait(0);

}
