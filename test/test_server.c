#include "net.h"
#include <asm-generic/socket.h>
#include <stdio.h>
#include <sys/socket.h>

void sendfile(int connfd);
void echo(int);

int main(int argc, char **argv) {
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    /* AF_INET --> IPv4 , SOCK_STREAM --> tcp, protocol = 0 --> will select corresponding protocol automactically */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    /* init servaddr */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  /* accept all address */
    servaddr.sin_port = htons(SERV_PORT);
    
    const int reuse;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));
    int bindret = bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(listenfd, LISTENQ);

    for(;;) {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
        /* if ((childpid = fork()) == 0) { */
        /*     close(listenfd); */

            /* do something in child process */
        printf("Server: Before echo");
        fflush(stdout);
        echo(connfd);
        printf("Server: After echo");

            /* exit(0); */
        /* } */
        close(connfd);
    }
}

void echo(int socketfd) {
    const int maxbuf = 1024;
    char buf[maxbuf];
    for (;;) {
        int n;
        if ((n = read(socketfd, buf, maxbuf)) < 0) {
            printf("Error read!");
            exit(1);
        } else if (n == 0) {
            printf("Error read!");
            break;
        } else {
            write(fileno(stdout), buf, n);
        }
    }
}
