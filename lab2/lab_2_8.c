//
// Created by alex on 04.11.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

void	read_file(int f_read, char *name)
{
	int		l;
	int		f_write;
	char	c;
	struct timespec t;

	f_write = creat(name, 0600);
	while ((l = read(f_read, &c, 1)) > 0)
	{
		t.tv_sec=0;
		t.tv_nsec=100000;
		nanosleep(&t, NULL);
		write(f_write, &c, l);
	}
	close(f_write);
}

int main(int argc, char * argv[]){
	int		f;

	if (argc != 2){
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(1);
	}
	if ((f = open(argv[1], O_RDONLY))==-1){
		perror(argv[1]);
		exit(1);
	}
	if (fork())
		read_file(f, "father");
	else
		read_file(f, "son");
	close(f);
	exit(0);
}