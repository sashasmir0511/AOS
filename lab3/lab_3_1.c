#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>

void	foo(int sig)
{
	printf("put SIGINT %d\n", sig);
	signal(SIGINT, SIG_DFL);
}

int		main()
{
	printf("START:\n");
	signal(SIGINT, foo);
	while (1);
	return (0);
}