#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>

typedef struct sigaction t_sig;

void	foo(int sig)
{
	int	pid;
	int rc;

	pid = wait(&rc);
	printf("Son - %d code - 0x%x\n", pid, rc);
}

int		main()
{
	int		i;
	t_sig	sig;

	printf("START:\n");
//	sig.sa_handler = SIG_IGN;
	sig.sa_handler = foo;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
//	sig.sa_flags = SA_RESETHAND;
//	sig.sa_flags = SA_RESTART;
//	sig.sa_flags = SA_NODEFER;
	sigaction(SIGCHLD, &sig, NULL);
	i = 0;
	while(i < 10)
	{
		if (fork() == 0)
		{
			printf("child %d\n", getpid());
			//sleep(5);
			exit(1);
		}
		i++;
	}

	while (1)
		pause();
	return (0);
}