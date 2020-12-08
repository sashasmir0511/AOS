// Написать программы для работы с очередями сообщений в соответствии с моделью клиент-сервер:
// 		каждый процесс использует собственную очередь сообщений.
// Процесс-сервер читает запросы из своей очереди сообщений и посылает ответ процессам-клиентам в их очереди.
// Процессы-клиенты читают ответ и выводят его в выходной поток.
// Процессы-клиенты должны передавать процессу-серверу информацию о своих очередях сообщений (куда записывать ответ).

#include "lab_5.h"

int		create_server()
{
	key_t	key;
	char 	*name_server;
	int		server_id;

	creat("server6", 0777);
	if ((key = ftok("server6", 'A')) == -1)
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
		execl("lab_5_6_server", "lab_5_6_server", ft_itoa(server_id), NULL);
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
			name = strcat(ft_itoa(i), "client_6");
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
				execl("lab_5_6_client", "lab_5_6_client", ft_itoa(client_id), ft_itoa(server_id), NULL);
		}
	}
}

int		main(int argc, char **argv)
{
	int		count_client;
	int		server_id;


	if (argc != 2)
	{
		printf("Use ./lab_5_6 <count client>\n");
		exit(1);
	}
	if (atoi(argv[1]) < 1)
		exit(1);

	server_id = create_server();
	count_client = atoi(argv[1]);
	create_clients(count_client, server_id);

	exit(0);
}
