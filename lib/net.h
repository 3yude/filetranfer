#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/param.h>
#include <asm-generic/socket.h>
#include <errno.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <string.h>

#define  SERV_IP      "127.0.0.1"
#define	SERV_PORT		 9876			/* TCP and UDP */
#define	LISTENQ		1024	/* 2nd argument to listen() */
