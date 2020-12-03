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
	int		b;
	char	buf[512];
	char	text1[] = "Hello";
	char	text2[] = "Goodbye";

	if (pipe(fd1) != 0)
		perror("Error pipe");
	if (fork())
	{
		printf("Father %d\n", getpid());
		close(fd1[0]);

		b = write(fd1[1], text1, sizeof(text1));
		printf("[P] Wrote %d bytes: %s\n", b , text1);
		sleep(1);
		b = write(fd1[1], text2, sizeof(text2));
		printf("[P] Wrote %d bytes: %s\n", b , text2);

		close(fd1[1]);
		exit(0);
	}
	else
	{
		printf("Son %d\n", getpid());
		close(fd1[1]);

		b = read(fd1[0], buf, sizeof(buf));
		printf("[S] Read %d bytes: %s\n", b, buf);
		sleep(1);
		b = read(fd1[0], buf, sizeof(buf));
		printf("[S] Read %d bytes: %s\n", b, buf);

		close(fd1[0]);
		exit(0);
	}
}