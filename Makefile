CC = gcc
CFLAGS = -I./lib -g -O2 -Wall

ALL: server client

server: server.c
	${CC} ${CFLAGS} $^ -o $@  

client: client.c
	${CC} ${CFLAGS} $^ -o $@  


clean:
	rm -f server client
