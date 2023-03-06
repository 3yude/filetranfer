#include "net.h"
#include "http_parser.h"
#include <unistd.h>

void sendfile(int connfd);
void echo(int);
int my_header_field_callback(http_parser*, const char *at, size_t length);
int my_url_callback(http_parser*, const char *at, size_t length);

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
    
    const int reuse = 1;
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

        http_parser_settings settings;
        http_parser_settings_init(&settings);
        settings.on_url = my_url_callback;
        settings.on_header_field = my_header_field_callback;
        /* ... */

        http_parser *parser = malloc(sizeof(http_parser));
        http_parser_init(parser, HTTP_REQUEST);

        size_t len = 80*1024, nparsed;
        char buf[len];
        int recved;

        while ((recved = read(connfd, buf, len)) > 0){

            /* recved = recv(connfd, buf, len, 0); */ 
            printf("recved = %d\n", recved);
            nparsed = http_parser_execute(parser, &settings, buf, recved);
            printf("nparsed = %d\n", (int)nparsed);

            if (parser->upgrade) {
                /* handle new protocol */
            } else if (nparsed != recved) {
                /* Handle error. Usually just close the connection. */
                printf("nparsed != recved\n");
            }
            write(STDOUT_FILENO, buf, recved);

        }

        if (recved < 0) {
            /* Handle error. */
            printf("recved < 0\n");
        }

        /* Start up / continue the parser.
         * Note we pass recved==0 to signal that EOF has been received.
         */

        printf("close connfd\n");
        free(parser);
        close(connfd);
    }
}


int my_header_field_callback(http_parser* parser, const char *at, size_t length) {

    printf("Call : my_header_field_callback\n" );
    return 0;
}
int my_url_callback(http_parser* parser, const char *at, size_t length) {

    printf("Call : my_url_callback\n" );
    return 0;
}
