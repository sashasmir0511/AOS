//
// Created by alex on 28.10.2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "unistd.h"


int main(int argc, char **argv)
{
	int f1;
	int i;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(1);
	}

	if ((f1 = open(argv[1], O_RDONLY)) == -1)
	{
		perror(argv[1]);
		printf("errno = %d\n", errno);
		i = 0;
		while (sys_errlist[i] != NULL)
		{
			printf("sys_errlist[%d] = %s\n", i, sys_errlist[i]);
			i++;
		}
		exit(1);
	}
	else
		printf("Файл %s открылся правильно\n", argv[1]);

	close(f1);
	return (0);
};