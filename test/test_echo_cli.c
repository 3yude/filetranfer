#include "net.h"
#include <unistd.h>

void echo(int socketfd);

int main(int argc, char **argv)
{
    /* int					sockfd; */
    struct sockaddr_in	servaddr;


    int sockfd = socket(PF_INET, SOCK_STREAM, 0);         
    /* sockfd = socket(AF_INET, SOCK_STREAM, 0); */

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);

    inet_pton(AF_INET, SERV_IP, &servaddr.sin_addr);

    int flag = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    echo(sockfd);

    close(sockfd);

    return 0;
}
void echo(int socketfd) {
    const int maxbuf = 1024;
    char buf[maxbuf];
    for (;;) {
        int n;
        if ((n = read(STDIN_FILENO, buf, maxbuf)) < 0) {
            if (errno != EWOULDBLOCK)
                printf("Client: Error read!\n");
            exit(1);
        } else if (n == 0) {
            printf("Client: Finish\n");
            break;
        } else {
            write(socketfd, buf, n);
        }
    }
}
