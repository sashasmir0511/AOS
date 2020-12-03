// Модифицировать программу п. 2 таким образом, чтобы процессы реализовали двунаправленную связь (диалог).
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int 	main()
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

		while ((b = read(0, buf, sizeof(buf))) > 0)
		{
			write(fd2[1], buf, b);
			sleep(1);
			read(fd1[0], buf, sizeof(buf));
			printf("[S] Read: %s\n", buf);
		}

		close(fd1[0]);
		close(fd2[1]);
		exit(0);
	}
}
