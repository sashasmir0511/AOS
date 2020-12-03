// Создать два параллельных процесса, разделяющие ввод с клавиатуры и вывод на экран.
// Что получится при исполнении этих процессов?

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#define	Father	"[P]: "
#define	Son		"[S]: "

int		main(int argc, char **argv)
{
	int		l;
	int		fd;
	char	buf[80];
	char 	*prefix;
	struct flock	lock;

	if (fork())
		prefix = Father;
	else
		prefix = Son;
	fd = 0;
	if (argc == 2)
		if ((fd = open(argv[1], O_RDWR)) == -1)
		{
			perror(argv[1]);
			exit(1);
		}

	/*lock.l_type=F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=0;
	lock.l_len=0;
	lock.l_type=F_WRLCK;
	if (fcntl(fd, F_SETLKW, &lock) == -1)
	{
		perror(argv[1]);
		exit(1);
	}*/

	while ((l = read(fd, buf, sizeof(buf))) > 0)
	{
		write(1, prefix, 5);
		write(1, buf, l);
		sleep(0.1);
	}

//	lock.l_type = F_UNLCK;
//	fcntl(fd, F_SETLK, &lock);

	close(fd);
	wait(NULL);
	exit(0);
}
