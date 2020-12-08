// Написать программу, позволяющую удалять очереди сообщений по идентификатору.
// Обработать возможные ошибочные ситуации.

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

int		main(int argc, char **argv)
{
	int msgqid;
	int res_cnlt;

	if (argc != 2)
		exit(1);
	msgqid = strtol(argv[1], NULL, 10);
	res_cnlt = msgctl(msgqid, IPC_RMID,0);
	if(res_cnlt == -1)
	{
		perror("removing failed");
		exit(1);
	}
	exit(0);
}
