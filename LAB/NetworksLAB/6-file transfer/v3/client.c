#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int port = atoi(argv[1]);
    int sockD = socket(AF_INET, SOCK_STREAM, 0);
    if (sockD < 0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created. \n");

    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = INADDR_ANY;
    int connectStatus = connect(sockD, (struct sockaddr *)&servAddr, sizeof(servAddr));
    if (connectStatus == -1)
    {
        perror("[-]Error in Connecting");
        exit(1);
    }
    else
    {
        printf("\nEnter filename : ");
        char str[20];
        scanf("%s", str);
        send(sockD, str, sizeof(str), 0);
        char str1[100];
        recv(sockD, str1, sizeof(str1), 0);
        printf("Enter file name to copy contents : ");
        char f1[20];
        scanf("%s", f1);
        int fd = open(f1, O_WRONLY | O_CREAT);
        if (fd == -1)
        {
            printf("file already exists  .....");
            exit(0);
        }
        printf("\nFile contents are : \n");
        printf("%s", str1);
        int nw = write(fd, str1, strlen(str1) + 1);
    }
}
