// Осуществить при помощи программ п. 6.
// обмен сообщениями между несколькими пользователями, при условии,
// что каждому пользователю предназначены сообщения любого или определенного типа
// (по договоренности). Будут ли примеры с очередями сообщений "приводить себя в порядок"?
// Что произойдет, если прервать процесс-сервер с помощью клавиши CTRL-C?

#include "lab_5.h"

int		create_server()
{
	key_t	key;
	char 	*name_server;
	int		server_id;

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
	if (fork() == 0)
		execl("lab_5_7_server", "lab_5_7_server", ft_itoa(server_id), NULL);
	return server_id;
}

int		create_clients(int count_client, int server_id)
{
	int		i;
	key_t	key_client;
	int		client_id;
	char 	*name;

	i = 0;
	while(i++ < count_client)
	{
		if (fork() == 0)
		{
			name = strcat(ft_itoa(i), "client_7");
			creat(name, 0777);
			if ((key_client = ftok(name, 'A')) == -1)
			{
				perror("ftok");
				exit(1);
			}
			if ((client_id = msgget(key_client, IPC_CREAT | 0600)) == -1)
			{
				perror("msgget");
				exit(1);
			}
			if (fork() == 0)
				execl("lab_5_7_client", "lab_5_7_client", ft_itoa(server_id), ft_itoa(client_id), NULL);
		}
	}
}

int		main(int argc, char **argv)
{
	int		count_client;
	int		server_id;


	if (argc != 2)
	{
		printf("Use ./lab_5_7 <count client>\n");
		exit(1);
	}
	if (atoi(argv[1]) < 1)
		exit(1);

	server_id = create_server();
	count_client = atoi(argv[1]);
	create_clients(count_client, server_id);

	exit(0);
}