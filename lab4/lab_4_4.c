// Повторить п. 2, создавая параллельные процессы с помощью связки fork - exec.
// Как передать дескрипторы канала в порожденный процесс?
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "utils/utils.h"


int		main()
{
	int		fd1[2];
	int		fd2[2];
	int		b;
	char	buf[512];

	if (pipe(fd1) != 0 || pipe(fd2) != 0)
		perror("Error pipe");
	if (fork())
	{
		printf("Father %d\n", getpid());
		close(fd1[0]);
		close(fd2[1]);

		while ((b = read(fd2[0], buf, sizeof(buf))) > 0)
		{
			printf("[P] Read: %s\n", buf);
			write(fd1[1], "[P] Wrote: ", 11);
			write(fd1[1], buf, b);
		}

		close(fd1[1]);
		close(fd2[0]);
		exit(0);
	}
	else
	{
		printf("Son %d\n", getpid());
		close(fd1[1]);
		close(fd2[0]);

		execl("4e", "4e", ft_itoa(fd1[0]), ft_itoa(fd2[1]), NULL);
		perror("Exec: ");
	}
}
