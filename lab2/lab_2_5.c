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


int main(){
	printf("I am father before fork. My pid=%d ppid=%d\n", getpid(), getppid());
	if (fork()){
		printf("I am father after fork. My pid=%d ppid=%d\n", getpid(), getppid());
		sleep(1);
		printf("I am father. See zombie where.\n");
		system ("ps");
		exit(0);	
	}
	else{
//		printf("I am son. I exit with code 3\n");
		exit(3);
	}
}
