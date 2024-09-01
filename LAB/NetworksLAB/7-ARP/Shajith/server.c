

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <ctype.h>
#include <pthread.h>

int main(int argc, char **argv)
{
    int serv = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in saddr;

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serv, (struct sockaddr *)&saddr, sizeof(saddr));

    listen(serv, 5);
    int i = 0;
    int sockets[10];

    while (1)
    {
        sockets[i++] = accept(serv, NULL, NULL);
        if (i == atoi(argv[3]))
            break;
    }
    for (int i = 0; i < atoi(argv[3]); i++)
    {
        send(sockets[i], argv[2], strlen(argv[2]), 0);
        char IP[20];
        recv(sockets[i], IP, sizeof(IP), 0);
        printf("%d => %s\n", i + 1, IP);
    }
    close(serv);
    return 0;
}