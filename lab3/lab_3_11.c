#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

typedef struct sigaction t_sig;

void par_sigusr_hdl (int sig) {
	printf("par_sigusr_hdl: handling signal %d\n", sig);
}

void chld_sigusr_hdl (int sig) {
	printf("chld_sigusr_hdl: handling signal %d\n", sig);
}

int main(int argc, char* argv[]) {
	pid_t pid = fork();
	if (pid == 0) {
		int		res;
		t_sig	sigalrm_new_action;
		sigset_t sigset;

		sigalrm_new_action.sa_handler = chld_sigusr_hdl;
		sigemptyset(&sigalrm_new_action.sa_mask);
		res = sigaction(SIGUSR1, &sigalrm_new_action, NULL);
		perror("in child: signal handler set error");
		// sigaction(SIGUSR2, &sigalrm_new_action, &sigalrm_old_action);

		sigemptyset(&sigset);
//		sigprocmask(SIG_UNBLOCK, &sigset, NULL);
//		sigaddset(&sigset, SIGUSR1);

		printf("child: initial suspend\n");
		sigsuspend(&sigset);
		for (int i = 0; i < 5; ++i) {
			printf("child: do work\n");
			sleep(1);
			printf("child: sending control to parent %d\n", getppid());
			kill(getppid(), SIGUSR1);
			if (i != 4) sigsuspend(&sigset);
		}
		printf("child %d exited\n", getpid());
	} else {
		int 	res;
		t_sig	sigalrm_new_action;

		sigalrm_new_action.sa_handler = par_sigusr_hdl;
		sigemptyset(&sigalrm_new_action.sa_mask); // blocking signals during handling
		res = sigaction(SIGUSR1, &sigalrm_new_action, NULL);
		perror("in parent: signal handler set error");

		sigset_t sigset;
		sigemptyset(&sigset);
//		sigaddset(&sigset, SIGUSR1);

		for (int i = 0; i < 5; ++i) {
			printf("parent: do work\n");
			sleep(1);
			printf("parent: sending control to child %d\n", pid);
			kill(pid, SIGUSR1);
			sigsuspend(&sigset);
		}

		int chld_status;
		pid_t cpid = wait(&chld_status);
		printf("WAIT triggered %d exited, status: %d\n", cpid, chld_status);
		printf("Parent exited\n");
	}
}
