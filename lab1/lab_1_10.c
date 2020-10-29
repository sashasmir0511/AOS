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

int main(int argc, char * argv[]){
	int		f;
	char	c;

	if (argc != 2){
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(1);
	}
	if ((f = open(argv[1], O_RDONLY)) == -1)
	{
		perror(argv[1]);
		exit(1);
	}
	for (lseek(f, 1, SEEK_END); lseek(f, -2, SEEK_CUR) !=- 1; read(f, &c, 1), write(1, &c, 1));
	close(f);
	exit(0);
}