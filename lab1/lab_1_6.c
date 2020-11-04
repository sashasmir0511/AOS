//
// Created by alex on 29.10.2020.
//

//
// Created by alex on 29.10.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

// filemode 256 - 0400
// filemode 384 - 0600

// SEEK_SET, SEEK_CUR, SEEK_END

int main(int argc, char **argv)
{
	int		f;
	int		i;
	char	buf[1024];

	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s file filemode (256 = 0400)\n", argv[0]);
		exit(1);
	}
	f = creat(argv[1], strtol(argv[2], NULL, 8));
	if (f >= 0)
	{
		i = write(f, "row1\nrow2\nrow3\nrow4\n", 20);
		if (i < 0){
			perror("write");
			printf("errno=%d\n", errno);
		}
		lseek(f, 2000, SEEK_CUR);
		i = write(f, "row5\nrow6\nrow7\nrow8\n", 20);
		if (i < 0) {
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

	f = open(argv[1], O_RDWR);
	if (f >= 0)
	{
		i = read(f, buf, 2040);
		printf("Файл %s открылся нормально\n", argv[1]);
		printf("%s\n", buf); //считает всё до /0
		write(1, buf, 2040); //считает всё
	}
	else
	{
		perror(argv[1]);
		printf("errno = %d\n", errno);
	}
	close(f);
	exit(0);
}