//
// Created by alex on 06.11.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

extern char** environ;

void	print_process_info(int argc, char **argv)
{
	int		i;

	i = 0;
	while (i < argc)
	{
		printf("argv[%d] = %s", argc, argv[i]);
		i++;
	}
	i = 0;
	while (environ[i] != NULL)
	{
		printf("env[%d] = %s", i, environ[i]);
		i++;
	}
}

int main(int argc, char** argv)
{
	pid_t pid;

	if (argc < 2){
		printf("Usage: %s <executable file to launch by exec>\n", argv[0]);
		exit(0);
	}

	if (fork())
	{
		printf("In parent,  fork_result=%d,  pid=%d,  ppid=%d, pgid=%d\n",
			   pid, getpid(),  getppid(), getpgrp());
		wait(NULL);
		printf("Parent info:\n");
		print_process_info(argc, argv);
		exit(0);
	}
	else{
		printf("In child process,  fork_result=%d,  pid=%d,  ppid=%d, pgid=%d\n",
			   pid, getpid(),  getppid(), getpgrp());
		printf("Son info:\n");
		print_process_info(argc, argv);
		execvp(argv[1], (char**) argv + 1);
	}
}