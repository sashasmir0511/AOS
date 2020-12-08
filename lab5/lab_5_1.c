//Task 1.
//Создать очередь сообщений или получить доступ к уже существующей очереди.
//Вывести на экран статистическую информацию об очереди сообщений.
//Поместить несколько сообщений различных типов в очередь.
#include "lab_5.h"


int main(int argc, char **argv)
{
	key_t	key;
	int		msgid;
	int		k, i;
	struct queue_int *q_i;
	struct queue_char *q_c;

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
	i = 0;
	while (i++ < 100) {
		q_i->mtype = i;
		q_i->number = 100 + i;
		if (msgsnd(msgid, q_i, sizeof(int), 0) == -1) {
			perror("msgsnd1");
			exit(1);
		}
	}

	strcpy(q_c->text, "01234567890");
	i = 0;
	while (i++ < 100) {
		q_c->mtype = i;
		if (msgsnd(msgid, q_c, MAX_CHAR, 0) == -1) {
			perror("msgsnd1");
			exit(1);
		}
	}
	free(q_i);
	free(q_c);
	exit(0);
}
