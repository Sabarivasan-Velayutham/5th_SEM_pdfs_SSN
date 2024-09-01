
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <net/if.h>
#include <arpa/inet.h>

int main(int argc , char *argv[])
{

	
	int socketfd = socket(AF_INET,SOCK_STREAM,0);
	if (socketfd<0) 
	{
		printf("[-] Socket not created ... \n");
		exit(1);
	}
	printf("[+] Socket created ... \n");
	struct sockaddr_in servaddr;
	int port = atoi(argv[1]);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = inet_addr("10.6.10.9");
	
	int connectStatus = connect(socketfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if (connectStatus<0) 
	{
		printf("[-] Connection error ... \n");
		exit(1);
	}
	printf("[+] Connection successfully ... \n");
	

		
		char user[1024];
		char passwd[1024];
		char buffer[1024];
		char data[1024];
		
		printf("\nEnter username : ");
		scanf("%s",user);
		printf("\nEnter password : ");
		scanf("%s",passwd);
		
		send(socketfd,user,sizeof(user),0);
		bzero(user,sizeof(user));
		send(socketfd,passwd,sizeof(passwd),0);
		bzero(passwd,sizeof(passwd));
		
		printf("Credentials sent ... \n");
		
		recv(socketfd,buffer,sizeof(buffer),0);
		printf("Received Data from server : %s\n",buffer);	
		
		printf("\nEnter data : ");
		scanf("%s",data);		
		send(socketfd,data,sizeof(data),0);
		bzero(data,sizeof(data));
		printf("Data sent ... \n");
	//}
	
	return 0 ;
}
