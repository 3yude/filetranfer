# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
PROGS := test_select_cli test_echo_server test_echo_cli\
			test_nonblockwrite_cli test_nonblockwrite_server \
			test_pthread \
			test_localtime \
			test_epoll_server

CC = gcc
CFLAGS = -I../lib -g -O2  -Wall

ALL: ${PROGS}

test_select_cli: test_select_cli.c
	${CC} ${CFLAGS} $^ -o $@

test_echo_cli: test_echo_cli.c
	${CC} ${CFLAGS} $^ -o $@

test_echo_server: test_echo_server.c
	${CC} ${CFLAGS} $^ -o $@

test_nonblockwrite_server: test_nonblockwrite_server.c
	${CC} ${CFLAGS} $^ -o $@

test_nonblockwrite_cli: test_nonblockwrite_cli.c
	${CC} ${CFLAGS} $^ -o $@

test_pthread: test_pthread.c
	${CC} ${CFLAGS} $^ -o $@

test_localtime: test_localtime.c
	${CC} ${CFLAGS} $^ -o $@

test_epoll_server: test_epoll_server.c
	${CC} ${CFLAGS} $^ -o $@

clean:
	rm -f test_select_cli test_echo_server 
	rm -f test_nonblockwrite_cli test_nonblockwrite_server
	rm -f test_pthread
	rm -f test_localtime
	rm -f test_epoll_server
	rm -f test_echo_cli
