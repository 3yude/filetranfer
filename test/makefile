# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
PROGS := test_selectcli test_server

CC = gcc
CFLAGS = -I../lib -g -O2  -Wall

ALL: test_server test_selectcli

test_selectcli: test_selectcli.c
	${CC} ${CFLAGS} $^ -o $@

test_server: test_server.c
	${CC} ${CFLAGS} $^ -o $@

clean:
	rm -f test_selectcli test_server
