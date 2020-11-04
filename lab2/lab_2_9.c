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

void	read_file(char *argv, char *name)
{
	int		l;
	int		f_write, f_read;
	char	c;
	struct timespec t;

	if ((f_read = open(argv, O_RDONLY))==-1){
		perror(argv);
		exit(1);
	}
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

	if (fork())
		read_file(argv[1], "father9");
	else
		read_file(argv[1], "son9");
	close(f);
	exit(0);
}