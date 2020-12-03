#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>

typedef struct sigaction t_sig;

void	foo(int sig)
{
	printf("put SIGINT %d\n", sig);
}

int		main()
{
	t_sig sig;

	printf("START:\n");
	sig.sa_handler = foo;
	sigemptyset(&sig.sa_mask);
//	sig.sa_flags = 0;
	sig.sa_flags = SA_RESETHAND;
//	sig.sa_flags = SA_RESTART;

	sigaction(SIGINT, &sig, NULL);

	while(1);
	return (0);
}