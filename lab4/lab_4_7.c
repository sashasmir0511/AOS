// Создать два параллельных процесса, в каждом из которых осуществляется работа с одним и тем же файлом.
// Каждый процесс открывает файл (имя файла передается через список аргументов командной строки).
// Один процесс пишет в файл, другой - читает из него. Что произойдет без включения блокировок?

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
#define TEXT	"test text "

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
	if (fork())
	{
//		lock.l_type=F_RDLCK;
//		lock.l_whence=SEEK_SET;
//		lock.l_start=0;
//		lock.l_len=0;
		if (fcntl(fd, F_SETLKW, &lock) == -1)
		{
			perror(argv[1]);
			exit(1);
		}

		if ((fd = open(argv[1], O_RDONLY)) < 0)
		{
			perror("File opening failed rfd\n");
			exit(1);

		}
		while ((l  = read(fd, buf, sizeof(buf))) > 0)
			write(1, buf, l);
//		lock.l_type = F_UNLCK;
//		fcntl(fd, F_SETLK, &lock);
		wait(NULL);
		close(fd);
	}
	else
	{
		int i;

//		lock.l_type=F_WRLCK;
//		lock.l_whence=SEEK_SET;
//		lock.l_start=0;
//		lock.l_len=0;
//		lock.l_type=F_WRLCK;
		if (fcntl(fd, F_SETLKW, &lock) == -1)
		{
			perror(argv[1]);
			exit(1);
		}
		if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0777)) < 0)
		{
			perror("File opening failed wfd\n");
			exit(1);
		}
		while(i++ < 100){
			if((l = write(fd, TEXT, sizeof(TEXT))) < 0) {
				perror("Write error");
				exit(1);
			}
		}
//		lock.l_type = F_UNLCK;
//		fcntl(fd, F_SETLK, &lock);
	}


	exit(0);
}
