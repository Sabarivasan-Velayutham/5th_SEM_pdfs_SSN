#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#include <string.h>
#include <ctype.h>

#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>

char *MAC()
{
    struct ifreq ifr;
    int socketfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    char temp[100], *mac = (char *)malloc(sizeof(char) * 500);
    strcpy(mac, "");
    strcpy(ifr.ifr_name, "eth0");
    if (0 == ioctl(socketfd, SIOCGIFHWADDR, &ifr))
    {
        int i;
        for (i = 0; i < 6; ++i)
        {
            sprintf(temp, "%02x%s", (unsigned char)ifr.ifr_addr.sa_data[i], (i < 5 ? ":" : ""));
            strcat(mac, temp);
        }
    }
    return mac;
}

char *IP()
{
    char *ip = (char *)malloc(sizeof(char) * 500);
    struct ifreq ifr;
    char array[] = "eth0";
    int socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, array, IFNAMSIZ - 1);
    ioctl(socketfd, SIOCGIFADDR, &ifr);
    close(socketfd);
    // display result
    sprintf(ip, "%s", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
    return ip;
}

int main(int argc, char const *argv[])
{
    int port = atoi(argv[1]);
    int servSockD = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = INADDR_ANY;

    bind(servSockD, (struct sockaddr *)&servAddr, sizeof(servAddr));
    listen(servSockD, 3);

    char strData[30];
    char *ip = IP();
    char *mac = MAC();
    printf("\nMy MAC:%s", mac);
    printf("\nMy IP:%s\n", ip);
    printf("Enter client's ip: ");
    scanf("%s", strData);
    // strcpy(strData,"10.6.10.10");

    int noc = 3;
    int clientsocket[noc];
    for (int i = 0; i < noc; i++)
        clientsocket[i] = accept(servSockD, NULL, NULL);
    for (int i = 0; i < noc; i++)
        send(clientsocket[i], strData, sizeof(strData), 0);
    for (int i = 0; i < noc; i++)   
    {
        recv(clientsocket[i], strData, sizeof(strData), 0);
        if (strcmp(strData, "False"))
        {
            printf("MAC of the client %s\n", strData);
            strcpy(strData, "Received");
            send(clientsocket[i], strData, sizeof(strData), 0);
            printf("\nAcknowledgement Sent!\n");
            break;
        }
    }
    return 0;
}
