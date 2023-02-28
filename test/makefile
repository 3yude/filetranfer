# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
PROGS := test_select_cli test_echo_server \
			test_nonblockwrite_cli test_nonblockwrite_server

CC = gcc
CFLAGS = -I../lib -g -O2  -Wall

ALL: ${PROGS}

test_select_cli: test_select_cli.c
	${CC} ${CFLAGS} $^ -o $@

test_echo_server: test_echo_server.c
	${CC} ${CFLAGS} $^ -o $@

test_nonblockwrite_server: test_nonblockwrite_server.c
	${CC} ${CFLAGS} $^ -o $@

test_nonblockwrite_cli: test_nonblockwrite_cli.c
	${CC} ${CFLAGS} $^ -o $@

clean:
	rm -f test_select_cli test_echo_server 
	rm -f test_nonblockwrite_cli test_nonblockwrite_server
