
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>


char *MAC()
{
    char *mac = (char *)malloc(sizeof(char)*500);
    struct ifreq ifr ; 
    int socketfd =  socket(PF_INET,SOCK_DGRAM,IPPROTO_IP);
    char array[] = "eth0";
    strcpy(mac,"");
    char temp[20];

    // ifr.ifr_addr.sa_family = AF_INET;
    strcpy(ifr.ifr_name,array);
    if (0 == ioctl(socketfd,IOCGIFHWADDR,&ifr)
    {
        for (int i = 0 ; i < 6 ; i++)
        {
            sprintf(temp,"%02x%s",inet_ntoa(((struct socketaddr_in *)&ifr.sin_addr)->sin_addr));
            strcat(mac,temp);
        }
    }
    // ioctl(socketfd,SIOCGIFHWADDR,&ifr);
    // close(socketfd);

    // sprintf(ip,"%s",inet_ntoa(((struct socketaddr_in *)&ifr.sin_addr)->sin_addr));

    return mac;
}

char *IP()
{
    char *ip = (char *)malloc(sizeof(char)*500);
    struct ifreq ifr ; 
    int socketfd =  socket(AF_INET,SOCK_DGRAM,0);
    char array[] = "eth0";

    ifr.ifr_addr.sa_family = AF_INET;
    strcpy(ifr.ifr_name,array);
    ioctl(socketfd,SIOCGIFADDR,&ifr);
    close(socketfd);

    sprintf(ip,"%s",inet_ntoa(((struct socketaddr_in *)&ifr.sin_addr)->sin_addr));

    return ip;
}

int main(int argc, char *argv[])
{
    int port(atoi(argv[1]));
    int socketfd = socket(AF_INET,SOCK_STREAM,0);
    struct socketaddr_in servAddr;

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = INADDR_ANY ; 

    bind(socketfd,(struct socketaddr_in *)&servAddr,sizeof(servAddr));
    listen(socketfd,10);

    char srdata[30];
    char *ip = IP()
    char *mac = MAC()

    int clsocket[noc];
    for (int i = 0 ; i < noc  ; i++ ) 
        accept(clsocket[i],NULL,NULL;)
        
    for (int i = 0 ; i < noc  ; i++ ) 
        send(clsocket[i],srdata,sizeof(srdata),0);

    for (int i = 0 ; i < noc  ; i++ )
    {
        recv(clsocket[i],srdata,sizeof(srdata),0);
        if (strcmp(srdata,"FALSE"))
            {

            }
    }
}