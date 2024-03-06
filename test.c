#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	main(void)
{
	int	file;
	int	old_out;
	int	pid;

	old_out = dup(1);
	file = open("out", O_WRONLY | O_CREAT, 0777);
	pid = fork();
	if (pid == 0)
	{
		dup2(file, 1);
		close(file);
		printf("hello1");
	}
	else
	{
		close(file);
		printf("hello2");
	}
	//close(file);
	//dup2(old_out, 1);
	//close(old_out);
	return (0);
}
