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
//	perror(CLIENT);
	msgctl(client_id, IPC_RMID, 0);
	free(q_c);
	free(q_s);
	exit(1);
}

int		main(int argc, char **argv)
{
	int		i;
	int		server_id;
	int		client_id;
	t_server	*q_s;
	t_client	*q_c;

	if (argc != 3)
	{
		printf("Use ./lab_5_6_client <client_id> <server_id>");
		exit(1);
	}
	i = 1;
	client_id = atoi(argv[1]);
	server_id = atoi(argv[2]);
	q_s = (t_server*)malloc(sizeof(t_server));
	q_c = (t_client*)malloc(sizeof(t_client) + MAX_CHAR);
	q_s->mtype = 1;
	q_s->client_id = client_id;
	while (i <= 10)
	{
		q_s->mtype_client = i;
		q_s->text = 100 + i;

		if (msgsnd(server_id, q_s, sizeof(t_server) - sizeof(long), 0) == -1)
			error_exit(q_s, q_c, client_id);

		if (msgrcv(client_id, q_c, sizeof(t_client) + MAX_CHAR, 0, 0) == -1)
			error_exit(q_s, q_c, client_id);

		print_client_msg(q_c, client_id);
		i++;
	}
	msgctl(client_id, IPC_RMID,0);
	free(q_s);
	free(q_c);
}
