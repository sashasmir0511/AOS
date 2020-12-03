// Создать именованный канал (любым способом).
// Убедиться, что канал создан.
// Рассмотреть особенности работы с именованным каналом
// (открыть файл с установленным и не установленным флагом O_NDELAY).
// Использовать его для обмена информацией с процессом, созданным другим пользователем (своим соседом).

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int		main()
{
	char buf[512];
	int f, l;

	write(0, "before fifo\n", 12);
	if ((f = open("fifo", O_RDONLY)) == -1)
	if ((f = open("fifo", O_RDONLY | O_NDELAY)) < 0)
	{
		perror("fifo: ");
		exit(1);
	}

		write(0, "after open fifo\n", 16);
	while ((l = read(f[0], buf, sizeof(buf))) > 0)
		write(1, buf, l);
	close(f);
	exit(0);

}
