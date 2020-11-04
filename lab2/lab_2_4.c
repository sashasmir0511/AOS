//
// Created by alex on 01.11.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int		p;
	int		rc;

	printf("I am father before fork. My pid=%d ppid=%d\n", getpid(), getppid());
	printf("I am father. Syscall \"wait\" return %d\n", wait(&rc));
	if (fork())
	{
		printf("I am father after fork. My pid=%d ppid=%d\n", getpid(), getppid());
		printf("I am father. I go wait for son\n");
		sleep(1);
		exit(0);
	}
	else{
		printf("I am son. My pid=%d ppid=%d\n", getpid(), getppid());
		sleep(2);
		printf("I am son. My pid=%d ppid=%d\n", getpid(), getppid());
		printf("I am son. I exit with code 3\n");
		exit(3);
	}
}
