#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>

typedef struct sigaction t_sig;

int		cycle(int num)
{
	int	i;
	int j;
	int k;
	int z;

	i = 0;
	printf("Start cycle:\n");
	while (i < num)
	{
		j = 0;
		while (j < 1000)
		{
			k = 0;
			while (k < 1000)
			{
				z = 0;
				while (z < 1000)
					z++;
				k++;
			}
			j++;
		}
		printf("Cycle %d * 10^9\n", i);
		i++;
	}
	printf("End cycle\n");
}

void	foo(int sig)
{
	return;
}

int		main()
{
	t_sig	sig;
	pid_t	pid;
	int 	status;

	printf("START:\n");
	sig.sa_handler = foo;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGCHLD, &sig, NULL);

	if (pid = fork())
	{
		printf("Father %d\n", getpid());
		sleep(2);
//		kill(pid, SIGKILL);
//		kill(pid, SIGUSR1);
		pid = wait(&status);
		printf("Child process %d finished with status %d   0x%x\n", pid, status, status);
	}
	else
	{
		cycle(10);
//		pause();
		exit(9);
	}
	return (0);
}