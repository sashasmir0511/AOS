// Написать программу, иллюстрирующую возможность синхронизации процессов при помощи очередей сообщений.

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "lab_5.h"

int 	main(int argc, char **argv)
{
	key_t	key;
	int		msgid;
	int		k, i;
	t_queue_int *q_i;
	t_queue_char *q_c;

	if ((key = ftok(argv[0], 'A')) == -1)
	{
		perror("ftok");
		exit(1);
	}
	if ((msgid = msgget(key, IPC_CREAT | 0600)) == -1)
	{
		perror("msgget");
		exit(1);
	}

	q_i = (struct queue_int *)malloc(sizeof(q_i));
	q_c = (struct queue_char *)malloc(MAX_CHAR);

	q_i->mtype=1;
	q_c->mtype=1;

	if (fork())
	{
		i = 0;

		while(i++ < 10)
		{
			if (msgsnd(msgid, q_i, sizeof(int), 0) == -1)
			{
				perror("msgsndP");
				exit(1);
			}

			printf("%s: cработал %ld\n", PARENT, q_c->mtype);
			q_i->mtype++;
			q_c->mtype++;

			if (msgrcv(msgid, q_c, 50, q_c->mtype, 0) == -1)
			{
				perror("msgrcvP");
				exit(1);
			}
		}
		wait(NULL);
		msgctl(msgid, IPC_RMID,0);
	}
	else
	{

		while(i++ < 10)
		{
			if (msgrcv(msgid, q_i, 50, q_i->mtype, 0) == -1)
			{
				perror("msgrcvS");
				exit(1);
			}

			printf("%s: cработал %ld\n", SON, q_i->mtype);
			q_i->mtype++;
			q_c->mtype++;

			if (msgsnd(msgid, q_c, sizeof(int), 0) == -1)
			{
				perror("msgsndS");
				exit(1);
			}
		}
	}
	exit(0);
}
