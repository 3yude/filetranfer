#include "net.h"
#include <stdlib.h>
#include <unistd.h>
#define MAX_EVENTS 10

int setnonblocking(int fd);
int do_use_fd(int fd);


int main() {
    struct epoll_event ev, events[MAX_EVENTS];
    int listenfd, connfd, nfds, epollfd;
    int n;

    /* Code to set up listening socket, 'listen_sock',
       (socket(), bind(), listen()) omitted. */

    /* int listenfd, connfd; */
    pid_t childpid;
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

    epollfd = epoll_create1(0);
    if (epollfd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = listenfd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &ev) == -1) {
        perror("epoll_ctl: listen_sock");
        exit(EXIT_FAILURE);
    }

    for (;;) {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (n = 0; n < nfds; ++n) {
            if (events[n].data.fd == listenfd) {
                clilen = sizeof(cliaddr);
                connfd = accept(listenfd,
                        (struct sockaddr *) &cliaddr, &clilen);
                if (connfd == -1) {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }
                setnonblocking(connfd);
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = connfd;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd,
                            &ev) == -1) {
                    perror("epoll_ctl: conn_sock");
                    exit(EXIT_FAILURE);
                }
            } else {
                do_use_fd(events[n].data.fd);
            }
        }
    }

}

int setnonblocking(int fd) {
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;

}

int do_use_fd(int fd) {
    char c;
    int n;

    if ((n = read(fd, &c, 1)) > 0){
        printf("%s", &c);
    }
    printf("\n");
    return 0;
}
