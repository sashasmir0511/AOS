#include "lab_5.h"

void	print_client_msg(t_client *q_c, int client_id)
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

	printf("%s:\tClient - %d\n\t\tНомер сообщения - %ld\n\t\tСообщение - %s\n",
		   CLIENT, client_id, q_c->mtype, q_c->text);

	lock.l_type = F_UNLCK;
	fcntl(1, F_SETLK, &lock);
}

void	error_exit(t_server *q_s, t_client *q_c, int client_id)
{
	perror(CLIENT);
	msgctl(client_id, IPC_RMID, 0);
	free(q_c);
	free(q_s);
	exit(1);
}

void	interrupt(int sig)
{
	printf("Close client\n");
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

void	work_client(int server_id)
{
	int		i;
	char	c_client_id[2];
	t_server	*q_s;
	t_client	*q_c;

	i = 0;
	q_s = (t_server*)malloc(sizeof(t_server));
	q_c = (t_client*)malloc(sizeof(t_client) + MAX_CHAR);
	q_s->mtype = 1;
	q_s->mtype_client = 1;
	while (1)
	{
		q_s->client_id = server_id;
		q_s->text = 100 + i;

		if (msgsnd(server_id, q_s, sizeof(t_server) - sizeof(long), 0) == -1)
			error_exit(q_s, q_c, server_id);

		if (msgrcv(server_id, q_c, sizeof(t_client) + MAX_CHAR, 0, 0) == -1)
			error_exit(q_s, q_c, server_id);

		print_client_msg(q_c, server_id);
		i++;
	}
	free(q_c);
	free(q_s);
}

int		main(int argc, char **argv)
{
	int		server_id;
	char 	*name;
	t_sig		sig;
	key_t	key_client;

	if (argc != 2)
	{
		printf("Use ./lab_5_7_client <server_id>");
		exit(1);
	}

	sig.sa_handler = interrupt;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);

	server_id = atoi(argv[1]);
	work_client(server_id);

}
