//С помощью системных вызовов pipe и dup реализовать конвейер: who | wc -l.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int		main()
{
	int		fd[2];

	if (pipe(fd) != 0)
		perror("Pipe error: ");
	if (fork())
	{
		close(fd[1]);
		close(0);
		dup2(fd[0], 0);
		close(fd[0]);

		execlp("wc", "wc", "-l", NULL);
		perror("Wc: ");
		exit(1);
	}
	else
	{
		close(fd[0]);
		close(1);
		dup2(fd[1], 1);
		close(fd[1]);

		execlp("who", "who", NULL);
		perror("Who: ");
		exit(1);
	}
	exit(0);
}
