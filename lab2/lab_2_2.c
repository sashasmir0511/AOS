//
// Created by alex on 01.11.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

/*
int main(){
	int		l;
	char	buf[10];
	int		parent;
	int		child;
	int		i;

	parent = 0;
	child = 0;
	i = 0;
//	while (i < 100)
//	{
	sprintf(buf, ".tmp%d", getpid());
	close(creat(buf, 0600));
	l = fork();
	if (unlink(buf) != -1)
		if (l)
			parent += 1;
		else {
			child += 1;
		}
		i++;
//	}
//	printf("parent = %d\nchild = %d\n", parent, child);
	exit(0);
}
 */

int main(){
	int l;
	char buf[10];

	sprintf(buf, ".tmp%d", getpid());
	close(creat(buf, 0600));
	l = fork();
	if (unlink(buf)!=-1)
		write(1, l?"#":"*", 1);
	exit(0);
}