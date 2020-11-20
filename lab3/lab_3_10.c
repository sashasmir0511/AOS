#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

void sigalrm_hdl (int sig) {
	int secs = 10;
	printf("sigalrm_hdl: handling signal %d\n", sig);
	printf("sigalrm_hdl: calling sleep(%d)\n", secs);
	sleep(secs);
	printf("sigalrm_hdl: return from handler\n");
}

void sigint_hdl (int sig) {
	int secs = 10;
	printf("sigint_hdl: handling signal %d\nsigint_hdl: continuing work...\n", sig);
}

int main()
{
	int		res;
	t_sig	sigalrm_new_action;
	t_sig	sigint_new_action;

	sigalrm_new_action.sa_handler = sigalrm_hdl;
	sigemptyset(&sigalrm_new_action.sa_mask);
	sigaddset(&sigalrm_new_action.sa_mask, SIGINT);
	res = sigaction(SIGALRM, &sigalrm_new_action, NULL);
	perror("in main(): signal handler set error");

	// setting up SIGINT handler
	sigint_new_action.sa_handler = sigint_hdl;
	sigemptyset(&sigint_new_action.sa_mask);
	res = sigaction(SIGINT, &sigint_new_action, NULL);
	perror("in main(): signal handler set error");

	int secs = 5;
	alarm(secs);
	printf("main: called alarm(%d)\n", secs);
	cycle(10);
}