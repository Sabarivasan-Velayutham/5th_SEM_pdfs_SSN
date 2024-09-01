
// client
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SA struct sockaddr

typedef struct ss
{
    int seq[8], data[8];
    char name[5];
} chip;

int main()
{
    int fd;
    struct sockaddr_in serv;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("sock err\n");
        exit(1);
    }
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(fd, (SA *)&serv, sizeof(serv));
    char buf[20];
    int i, t, temp[10];

    chip s;
    printf("client name: ");
    scanf("%s", s.name);
    printf("seq: ");
    for (i = 0; i < 4; i++)
        scanf("%d", &s.seq[i]);
    printf("data(0/1): ");
    scanf("%d", &t);
    for (i = 0; i < 4; i++)
        if (t == 0)
            s.data[i] = -1 * s.seq[i];
        /*else if(t==2)
          s.data[i]=0;*/
        else
            s.data[i] = s.seq[i];
    printf("seq: ");
    for (i = 0; i < 4; i++)
        printf("%d", s.seq[i]);
    printf("\ndata: ");
    for (i = 0; i < 4; i++)
        printf("%d", s.data[i]);
    send(fd, (void *)&s, sizeof(chip), 0);

    return 0;
}