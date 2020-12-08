#include "lab_5.h"

void	print_server_msg(t_server *q_s)
{
	struct flock	lock;

	lock.l_type=F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=0;
	lock.l_len=0;
	if (fcntl(1, F_SETLKW, &lock) == -1)
	{
		perror("fcntl");
		exit(1);
	}

	printf("%s:\tClient - %d\n\t\tНомер сообщения - %d\n\t\tПрислал число - %d\n",
		   SERVER, q_s->client_id, q_s->mtype_client, q_s->text);

	lock.l_type = F_UNLCK;
	fcntl(1, F_SETLK, &lock);
}

void	error_exit(t_server *q_s, t_client *q_c, int server_id)
{
//	perror(SERVER);
	msgctl(server_id, IPC_RMID, 0);
	free(q_c);
	free(q_s);
	exit(1);
}

void	interrupt(int sig)
{
	printf("Close server\n");
	int total_mq, msqid, res;
	struct msqid_ds ds;
	struct msginfo msginfo;

	total_mq = msgctl(0, MSG_INFO, (struct msqid_ds *) &msginfo);

	if (total_mq < 0)
		printf("[ clean_all_queues ]: total_mq error\n");

	for (int i = 0; i <= total_mq; i++)
	{
		msqid = msgctl(i, MSG_STAT, &ds);
		if (msqid < 0)
			continue;
		res = msgctl(msqid, IPC_RMID, 0);
		if (res < 0)
			printf("[ clean_all_queues ]: msgctl error\n");

	}
	exit(2);
}

void	work_server(t_server *q_s, t_client *q_c, int server_id)
{
	while (1)
	{
		if (msgrcv(server_id, q_s, sizeof(t_server) - sizeof(long), 0, 0) == -1)
			error_exit(q_s, q_c, server_id);

		print_server_msg(q_s);

		q_c->mtype = q_s->mtype_client;
		strcpy(q_c->text, strcat(ft_itoa(q_s->text), "00"));

		msgsnd(q_s->client_id, q_c, sizeof(q_c), 0);
	}
}

int		main(int argc, char **argv)
{
	int			server_id;
	t_server	*q_s;
	t_client	*q_c;
	t_sig		sig;
	key_t		key;

	if (argc != 2)
	{
		creat("server7", 0777);
		if ((key = ftok("server7", 'A')) == -1)
		{
			perror("ftok");
			exit(1);
		}
		if ((server_id = msgget(key, IPC_CREAT | 0600)) == -1)
		{
			perror("msgget");
			exit(1);
		}
	}
	else
		server_id = atoi(argv[1]);

	sig.sa_handler = interrupt;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);

	q_s = (t_server*)malloc(sizeof(t_server));
	q_c = (t_client*)malloc(sizeof(t_client) + MAX_CHAR);
	work_server(q_s, q_c, server_id);
	exit(0);
}
