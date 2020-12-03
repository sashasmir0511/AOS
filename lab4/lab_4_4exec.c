//Помощь для лабы 4

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int		main(int argc, char *argv[])
{
	int 	b;
	int 	fd[2];
	char	buf[512];


	fd[0] = atoi(argv[1]);
	fd[1] = atoi(argv[2]);
	while ((b = read(0, buf, sizeof(buf))) > 0)
	{
		write(fd[1], "[S] Wrote: ", 11);
		write(fd[1], buf, b);
		read(fd[0], buf, sizeof(buf));
		printf("[S] Read: %s\n", buf);
	}
	close(fd[0]);
	close(fd[1]);
	return 0;
}