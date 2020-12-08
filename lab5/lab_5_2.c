// Написать программу, позволяющую читать сообщения из очереди и выводить их на экран.
// Идентификатор очереди и тип сообщения передается через аргументы командной строки.

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

void print_queue_int(t_queue_int *m)
{
	printf("type = %ld, number = %d\n", m->mtype, m->number);
}

void print_queue_char(t_queue_char *m)
{
	printf("type = %ld, text = %s\n", m->mtype, m->text);
}

int		main(int argc, char **argv)
{
	int		msgid;
	int		type;
	int		rcv_res;
	t_queue_int *q_i;
	t_queue_char *q_c;

	if (argc != 3)
		exit(1);
	msgid = strtol(argv[1], NULL, 10);
	type = strtol(argv[2], NULL, 10);
	if(msgid == -1 || type == -1)
	{
		perror("msgget error");
		exit(1);
	}

	q_i = (struct queue_int *)malloc(sizeof(q_i));
	q_c = (struct queue_char *)malloc(MAX_CHAR);

	strcpy(q_c->text, "AAAAAAAAAAAA");
	if ((rcv_res = msgrcv(msgid, q_i, 50, type, 0)) == -1)
	{
		perror("msgrcv1");
		exit(1);
	}
	if ((rcv_res = msgrcv(msgid, q_c, 50, type, 0)) == -1)
	{
		perror("msgrcv2");
		exit(1);
	}
	print_queue_int(q_i);
	print_queue_char(q_c);
	exit(0);
}