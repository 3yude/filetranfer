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

    int val, maxdfp1;
    fd_set rset;
    
    val = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, val | O_NONBLOCK);
    val = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, val | O_NONBLOCK);

    FD_ZERO(&rset);
    FD_SET(STDERR_FILENO, &rset);
    FD_SET(sockfd, &rset);
    


    maxdfp1 = MAX(fileno(stdin),sockfd) + 1;

    printf("Before select\n");

    select(maxdfp1, &rset, 0, 0, 0);

    printf("After select\n");

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
