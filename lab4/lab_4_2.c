// Модифицировать программу п. 1 таким образом, чтобы родительский процесс читал из канала в цикле,
// пока не встретится конец файла (порожденный процесс может записывать в канал информацию,
// читаемую им из стандартного входного потока).
// Как избежать бесконечного ожидания родительским процессом чтения из пустого канала?
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int		main()
{
	int		fd1[2];
	int		b;
	char	buf[512];

	if (pipe(fd1) != 0)
		perror("Error pipe");
	if (fork())
	{
		printf("Father %d\n", getpid());
		close(fd1[1]);

		while ((b = read(fd1[0], buf, sizeof(buf))) > 0)
			printf("[P] Read: %s\n", buf);

		close(fd1[1]);
		exit(0);
	}
	else
	{
		printf("Son %d\n", getpid());
		close(fd1[0]);

		while ((b=read(0, buf, sizeof(buf))) > 0)
			write(fd1[1], buf, sizeof(buf));

		close(fd1[0]);
		exit(0);
	}
}
