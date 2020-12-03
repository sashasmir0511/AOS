// Создать параллельный процесс, используя только fork.
// Организовать обмен информацией между процессами через каналы.
// Предусмотреть однонаправленную и двунаправленную связь.
// При создании двунаправленной связи исключить возможность появления «смертельных объятий».
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int		main()
{
	int		fd1[2];
	int		fd2[2];
	int		b;
	char	buf[512];
	char	text1[] = "Hello";
	char	text2[] = "Goodbye";

	if (pipe(fd1) != 0 || pipe(fd2) != 0)
		perror("Error pipe");
	if (fork())
	{
		printf("Father %d\n", getpid());
		close(fd1[0]);
		close(fd2[1]);

		b = write(fd1[1], text1, sizeof(text1));
		printf("[P] Wrote %d bytes: %s\n", b , text1);

		b = read(fd2[0], buf, sizeof(buf));
		printf("[P] Read %d bytes: %s\n", b, buf);

		close(fd1[1]);
		close(fd2[0]);
		exit(0);
	}
	else
	{
		printf("Son %d\n", getpid());
		close(fd1[1]);
		close(fd2[0]);

		.;

		b = read(fd1[0], buf, sizeof(buf));
		printf("[S] Read %d bytes: %s\n", b, buf);

		close(fd1[0]);
		close(fd2[1]);
		exit(0);
	}
}