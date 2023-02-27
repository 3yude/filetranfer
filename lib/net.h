#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define	SERV_PORT		 9876			/* TCP and UDP */
#define	LISTENQ		1024	/* 2nd argument to listen() */
