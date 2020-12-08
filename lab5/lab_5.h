//
// Created by alex on 04.12.2020.
//

#ifndef AOS_LAB_5_H
#define AOS_LAB_5_H


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
#include "utils/utils.h"
#include <fcntl.h>

# define MAX_CHAR 50
# define MAX_MSG 100
# define PARENT "[ P ]"
# define SON "[ S ]"
# define SERVER "[ Server ]"
# define CLIENT "[ Client ]"

typedef struct sigaction t_sig;

typedef struct	queue_char
{
	long	mtype;
	char	text[1];
}				t_queue_char;

typedef struct	queue_int
{
	long	mtype;
	int		number;
}				t_queue_int;

typedef struct	client
{
	long	mtype;
	char 	text[1];
}				t_client;

typedef struct	server
{
	long	mtype; // 8 byte
	int 	mtype_client;
	int 	client_id;
	int		text;
}				t_server;

#endif //AOS_LAB_5_H
