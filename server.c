#include "net.h"

void sendfile(int connfd);

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

    int bindret = bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(listenfd, LISTENQ);

    for(;;) {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
        if ((childpid = fork()) == 0) {
            close(listenfd);

            /* do something in child process */
            sendfile(connfd);

            exit(0);
        }
        close(connfd);
    }
}
