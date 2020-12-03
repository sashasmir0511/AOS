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
	int f[2], l, i;
	int flags;


	pipe2(f, O_NDELAY);

//	flags = fcntl(f[0], F_GETFL, 0);
//	fcntl(f[0], F_SETFL, flags | O_NONBLOCK | O_NDELAY);

//	flags = fcntl(f[1], F_GETFL, 0);
//	fcntl(f[1], F_SETFL, flags | O_NONBLOCK);

	//	write(0, "after open fifo\n", 16);
	while ((l = read(f[0], buf, sizeof(buf))) > 0)
		write(1, buf, l);
	close(f[0]);
	close(f[1]);
	exit(0);

}
