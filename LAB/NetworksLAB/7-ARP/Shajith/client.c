

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

int main(int argc, char **argv)
{

    int cli = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in caddr;

    caddr.sin_family = AF_INET;
    caddr.sin_port = htons(atoi(argv[1]));
    caddr.sin_addr.s_addr = INADDR_ANY;

    connect(cli, (struct sockaddr *)&caddr, sizeof(caddr));

    char IP[20];

    int n;
    struct ifreq ifr;
    char array[] = "eth0";
    n = socket(AF_INET, SOCK_DGRAM, 0);

    ifr.ifr_addr.sa_family = AF_INET;

    strncpy(ifr.ifr_name, array, IFNAMSIZ - 1);

    ioctl(n, SIOCGIFADDR, &ifr);

    close(n);

    recv(cli, IP, sizeof(IP), 0);
    printf("%s\n", IP);
    IP[sizeof(IP)] = '\0';
    char *myIP = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
    printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

    int flag = 1;

    for (int i = 0; i < strlen(myIP); i++)
    {
        if (myIP[i] != IP[i])
        {
            flag = 0;
            break;
        }
    }

    if (flag)
    {
        send(cli, "WORKS!!!", 8, 0);
    }
    else
    {
        send(cli, "NOPE!!!", 7, 0);
    }

    close(cli);

    return 0;
}