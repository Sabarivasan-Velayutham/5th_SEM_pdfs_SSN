#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
#include<strings.h>
#define PORT 8084
#define MAX 80
#define SA struct sockaddr
int main()
{
	int sockfd;
	char buff[MAX],user[5],pass[5];

	struct sockaddr_in servaddr,cli;

	sockfd = socket(AF_INET,SOCK_STREAM,0);

	if(sockfd == -1)
	{
		printf("\nSocket not created");
		exit(1);
	}
	else
	{
		printf("\nSocket created successfully");
	}

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("10.6.10.19");
	servaddr.sin_port = htons(PORT);
	
	if( connect(sockfd,(SA*)&servaddr,sizeof(servaddr)) != 0)
	{
		printf("\nClient not connected to server");
		exit(1);
	}
	else
	{
		printf("\nClient connected to server");
	}
	printf("\nEnter username:");
	scanf("%s",user);
	printf("\nEnter password:");
	scanf("%s",pass);
	bzero(buff,sizeof(buff));
	strcat(buff,user); 
	strcat(buff," ");
	strcat(buff,pass);

	write(sockfd,buff,sizeof(buff));
	bzero(buff,sizeof(buff));
	read(sockfd,buff,sizeof(buff));
	printf("\n%s\n",buff);
	bzero(buff,sizeof(buff));
	printf("\nEnter data to be sent(with flag):");
	scanf("%s",buff);
	write(sockfd,buff,sizeof(buff));
	printf("\nData sent to server");
	bzero(buff,sizeof(buff));
	read(sockfd,buff,sizeof(buff));
	printf("\n%s\n",buff);
	return 0;
}
