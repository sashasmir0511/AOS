//
// Created by alex on 04.11.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(){

	if (fork())
	{
		printf("I am father after fork. My pid=%d ppid=%d gpid=%d\n",
			getpid(), getppid(), getpgrp());
		pause();
		exit(0);
	}
	else{
		printf("I am son. My pid=%d ppid=%d  gpid=%d\n",
			getpid(), getppid(), getpgrp());
		pause();
		exit(3);
	}
}
