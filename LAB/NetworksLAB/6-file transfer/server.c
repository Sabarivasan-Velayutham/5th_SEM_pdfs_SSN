#include <netinet/in.h> 
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<fcntl.h>
  
int main(int argc, char const* argv[])
{
	int e ;
	int port=atoi(argv[1]);
    int servSockD = socket(AF_INET, SOCK_STREAM, 0);
    if(servSockD<0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
     printf("[+]Server socket created. \n");
     
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = INADDR_ANY;
    e = bind(servSockD, (struct sockaddr*)&servAddr,sizeof(servAddr));
    if(e<0)
     {
         perror("[-]Error in Binding");
         exit(1);
     }
     printf("[+]Binding Successfull.\n");


    e = listen(servSockD, 1);
    if(e==0)
     {
         printf("[+]Listening...\n");
     }
     else 
     {
         perror("[-]Error in Binding");
         exit(1);
     }
     
    char strData[1000];
    int clientsocket;
    clientsocket=accept(servSockD,NULL,NULL);
    recv(clientsocket, strData, sizeof(strData), 0);
    int fd;
    fd=open(strData,O_RDONLY);
    if (fd==-1)
    {
        printf("Cannot open file\n");
        exit(0);
    }
    printf("Requested file : %s\n",strData);
    printf("Sending file ... ");
    char buf[1000];
    int nr=read(fd,buf,100);
    printf("\nSent !");
    send(clientsocket,buf,nr, 0);
    return 0;
}
