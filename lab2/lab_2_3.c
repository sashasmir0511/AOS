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
	if (fork()){
//		sleep(1);
		printf("I am father after fork. My pid=%d ppid=%d\n", getpid(), getppid());
		printf("I am father. I go wait for son\n");
		p = wait(&rc);
		printf("I am father. My son with pid %d exit with code 0x%x\n", p, rc); // 0x(exit)(еслли по сигналу)
		exit(0);
	}
	else{
		printf("I am son. My pid=%d ppid=%d\n", getpid(), getppid());
		printf("I am son. I exit with code 3\n");
		exit(3);
	}
}
