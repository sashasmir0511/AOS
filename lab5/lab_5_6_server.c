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

int		main(int argc, char **argv)
{
	int			server_id;
	t_server	*q_s;
	t_client	*q_c;

	if (argc != 2)
	{
		printf("Use ./lab_5_6_server <server_id>");
		exit(1);
	}
	server_id = atoi(argv[1]);
	q_s = (t_server*)malloc(sizeof(t_server));
	q_c = (t_client*)malloc(sizeof(t_client) + MAX_CHAR);
	while (1)
	{
		if (msgrcv(server_id, q_s, sizeof(t_server) - sizeof(long), 0, 0) == -1)
			error_exit(q_s, q_c, server_id);

		print_server_msg(q_s);

		q_c->mtype = q_s->mtype_client;
		strcpy(q_c->text, strcat(ft_itoa(q_s->text), "00"));

//		if (msgsnd(q_s->client_id, q_c, sizeof(q_c), 0) == -1)
//			error_exit(q_s, q_c, server_id);
		msgsnd(q_s->client_id, q_c, sizeof(q_c), 0);
	}
	exit(0);
}
