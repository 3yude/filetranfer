#include "net.h"
#include <unistd.h>

void sendfile(int connfd);
void echo(int);

int main(int argc, char **argv) {
    int listenfd, connfd;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    /* AF_INET --> IPv4 , SOCK_STREAM --> tcp, protocol = 0 --> will select corresponding protocol automactically */
    listenfd = socket(PF_INET, SOCK_STREAM, 0);

    /* init servaddr */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  /* accept all address */
    servaddr.sin_port = htons(SERV_PORT);
    
    const int reuse;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));

    if (0 != bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) {
        perror("bind error!");
        exit(EXIT_FAILURE);
    }

    listen(listenfd, LISTENQ);

    for(;;) {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

        echo(connfd);

        close(connfd);
    }
}

void echo(int socketfd) {
    const int maxbuf = 1024;
    char buf[maxbuf];
    for (;;) {
        int n;
        if ((n = read(socketfd, buf, maxbuf)) < 0) {
            printf("Server: Error read!");
            exit(1);
        } else if (n == 0) {
            printf("Server: Finish!");
            break;
        } else {
            write(STDOUT_FILENO, buf, n);
        }
    }
}
