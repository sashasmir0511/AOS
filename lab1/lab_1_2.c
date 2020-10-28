//
// Created by alex on 28.10.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

//
int main(int argc, char **argv)
{
	int f;
	int l;
	int i;
	char buf[1024];

	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s file filemode (256 = 0400)\n", argv[0]);
		exit(1);
	}


	f = creat(argv[1], atoi(argv[2]));
	if (f >= 0)
	{
		i = write(f, "row1\nrow2\nrow3\nrow4\n", 20);
		if (i < 0){
			perror("write");
			printf("errno=%d\n", errno);
		}
		close(f);
	}
	else{
		perror("creat");
		printf("errno=%d\n", errno);
		exit(1);
	}


	f = open(argv[1], O_RDONLY); // попытается открыть на запись - будет ошибка
	if (f >= 0)
	{
		l = read(f, buf, 20);
		printf("l(read) = %d\n%s\n", l, buf);
	}
	else
	{
		perror("open");
		printf("errno=%d\n", errno);
	}
	close(f);

	f = open(argv[1], O_RDWR);
	if (f >= 0)
	{
		printf("Файл %s открылся нормально\n", argv[1]);
		printf("%s\n", buf);
	}
	else
	{
		perror(argv[1]);
		printf("errno = %d\n", errno);
	}
	close(f);
	exit(0);
}
