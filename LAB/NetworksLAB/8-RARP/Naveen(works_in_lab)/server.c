#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/types.h>

#include <string.h>
#include <ctype.h>

#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>

char *MAC()
{
    struct ifreq s;
    int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    char temp[100], *mac = (char *)malloc(sizeof(char) * 500);
    strcpy(mac, "");
    strcpy(s.ifr_name, "eth0");
    if (0 == ioctl(fd, SIOCGIFHWADDR, &s))
    {
        int i;
        for (i = 0; i < 6; ++i)
        {
            sprintf(temp, "%02x%s", (unsigned char)s.ifr_addr.sa_data[i], (i < 5 ? ":" : ""));
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
    int n = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ - 1);
    ioctl(n, SIOCGIFADDR, &ifr);
    close(n);
    // display result
    sprintf(ip, "%s", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
    return ip;
}
int isValidMAC(char *mac)
{
    int col_cnt = 0;
    for (int i = 0; mac[i]; i++)
    {
        if (mac[i] == ':')
            col_cnt++;
        else if (!isdigit(mac[i]) && (!isalpha(mac[i]) || (isalpha(mac[i]) && (mac[i] < 'a' || mac[i] > 'f'))))
            return 0;
    }
    if (col_cnt != 5)
        return 0;
    for (int i = 2; mac[i]; i = i + 3)
        if (mac[i] != ':')
            return 0;
    return 1;
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
    printf("Enter Destination MAC: ");
    scanf("%[^\n]s", strData);
    if (isValidMAC(strData))
        printf("\nvalid mac address\n");
    else
        printf("\ninvalid mac address\n");
    // strcpy(strData,"40:a8:f0:5c:e7:d4");
    printf("\nARP request broadcasted..\n\nWaiting for Reply..\n\n");
    int clientsocket[4];
    for (int i = 0; i < 3; i++)
        clientsocket[i] = accept(servSockD, NULL, NULL);
    for (int i = 0; i < 3; i++)
        send(clientsocket[i], strData, sizeof(strData), 0);
    int flag = 0;
    for (int i = 0; i < 3; i++)
    {
        recv(clientsocket[i], strData, sizeof(strData), 0);
        if (strcmp(strData, "False"))
        {
            printf("IP of the accepted client %s\n", strData);
            strcpy(strData, "Received");
            send(clientsocket[i], strData, sizeof(strData), 0);
            printf("\nAcknowledgement Sent!\n");
            flag = 1;
            break;
        }
    }
    if (!flag)
        printf("\nARP requeted failed\n");
    return 0;
}
