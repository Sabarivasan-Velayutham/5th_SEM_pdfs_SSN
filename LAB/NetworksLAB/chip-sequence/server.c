
// serv
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
// #include<netinet/in.h>
#define SA struct sockaddr

typedef struct ss
{
    int seq[8], data[8];
    char name[5];
} chip;

int main()
{
    int fd, confd;
    struct sockaddr_in serv, cli;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("sock err\n");
        exit(1);
    }
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(fd, (SA *)&serv, sizeof(serv)) < 0)
    {
        printf("bind err\n");
        exit(1);
    }

    if (listen(fd, 5) < 0)
    {
        printf("listen err\n");
        exit(1);
    }
    printf("listening......\n");

    char buf[20];
    int temp = 0;
    int i, fin[8];
    int n, l = sizeof(SA);
    chip s, ss;
    confd = accept(fd, (SA *)&cli, &l);
    printf("ok1\n");
    recv(confd, (void *)&s, sizeof(s), 0);
    close(confd);
    confd = accept(fd, (SA *)&cli, &l);
    recv(confd, (void *)&ss, sizeof(ss), 0);
    for (i = 0; i < 4; i++)
    {
        fin[i] = s.data[i] + ss.data[i];
        printf("%d ", fin[i]);
    }

    for (i = 0; i < 4; i++)
        temp += fin[i] * s.seq[i]; // printf("%d ",temp); }//
    printf("\ntemp %d\n", temp);
    /*if(temp==0){
      printf("%s sends no data\n",s.name);
    }
    else */
    if (temp > 0)
        printf("%s sends data 1\n", s.name);
    else
        printf("%s sends data: 0\n", s.name);

    temp = 0;
    for (i = 0; i < 4; i++)
        temp += fin[i] * ss.seq[i]; //
    printf("temp %d\n", temp);
    /*if(temp==0){
      printf("%s sends no data\n",ss.name);
    }
    else */
    if (temp > 0)
        printf("%s sends data 1\n", ss.name);
    else
        printf("%s sends data: 0\n", ss.name);

    return 0;
}