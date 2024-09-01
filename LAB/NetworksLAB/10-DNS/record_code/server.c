#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>

#define PORT 8080
#define MAXLINE 1024
int t = 2;

typedef struct domain
{
    char name[50];
    char IP[25];
    char repeated[10][25];
    int pointer;
} DNS;

// Driver code
int validate_number(char *str)
{
    while (*str)
    {
        if (!isdigit(*str))
        {
            return 0;
        }
        str++;
    }
    return 1;
}
int validate_ip(char *ip)
{
    int i, num, dots = 0;
    char *ptr;
    if (ip == NULL)
        return 0;
    ptr = strtok(ip, ".");
    if (ptr == NULL)
        return 0;
    while (ptr)
    {
        if (!validate_number(ptr))
            return 0;
        num = atoi(ptr);
        if (num >= 0 && num <= 255)
        {
            ptr = strtok(NULL, ".");
            if (ptr != NULL)
                dots++;
        }
        else
            return 0;
    }
    if (dots != 3)
        return 0;
    return 1;
}

int main()
{
    int sockfd;
    char buffer[MAXLINE];

    struct sockaddr_in servaddr, cliaddr;
    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;
    DNS node[10];
    strcpy(node[0].name, "www.google.com");
    strcpy(node[0].IP, "192.0.0.1");
    node[0].pointer = 0;
    strcpy(node[0].repeated[node[0].pointer++], "192.0.0.1");
    
    strcpy(node[1].name, "www.yahoo.com");
    strcpy(node[1].IP, "192.0.3.2");
    node[1].pointer = 0;
    strcpy(node[1].repeated[node[1].pointer++], "192.0.3.2");
    len = sizeof(cliaddr); // len is value/result

    while (1)
    {
        printf("\ntable : \n");
        // printf("Hello message sent.\n");
        for (int i = 0; i < t; i++)
        {
            printf("\n%s\t%s\n", node[i].name, node[i].IP);
            for (int j = 0; j < node[i].pointer; j++)
            {
                printf("%s ", node[i].repeated[j]);
            }
            printf("\n");
        }
        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                     MSG_WAITALL, (struct sockaddr *)&cliaddr,
                     &len);
        int ch;
        printf("\nEnter choice:\nCheck(0) \nModify(1)\n");
        printf("\nEner choice : ");
        scanf("%d", &ch);
        buffer[n] = '\0';
        if (ch == 0)
        {
            char res[50];
            int flag = 0;
            for (int i = 0; i < t; i++)
            {
                if (strcmp(node[i].name, buffer) == 0)
                {
                    flag = 1;
                    printf("\n%s", node[i].IP);
                    strcpy(res, node[i].IP);
                    break;
                }
            }
            if (flag == 0)
                strcpy(res, "Not Found");
            printf("Client : %s\n", buffer);
            // printf("\n%s",res);
            sendto(sockfd, (char *)res, strlen(res),
                   MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
                   len);
        }
        else
        {
            printf("\nEnter IP for %s : ", buffer);
            char ip[25];
            scanf("%s", ip);
            char temp[255];
            strcpy(temp, ip);
            if (validate_ip(ip) == 0)
                printf("\nInvalid IP");
            else
            {
                int flag = 0;
                for (int i = 0; i < t; i++)
                {
                    if (strcmp(node[i].name, buffer) == 0)
                    {
                        flag = 1;
                        // printf("\n%s",node[i].IP);
                        strcpy(node[i].repeated[node[i].pointer++], temp);
                        strcpy(node[i].IP, node[i].repeated[node[i].pointer - 1]);
                        break;
                    }
                }
                if (flag == 0)
                {
                    node[t].pointer = 0;
                    strcpy(node[t].name, buffer);
                    strcpy(node[t].IP, temp);
                    strcpy(node[t].repeated[node[t].pointer++], temp);
                    t++;
                }
            }
            sendto(sockfd, "Updated", strlen("Updated"),
                   MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
                   len);
        }
    }
    return 0;
}