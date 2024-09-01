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
	int sockfd,connfd,len,i;
	char user[4][10],buff[MAX];
	strcpy(user[0],"aaa aaa");
	strcpy(user[1],"bbb bbb");
	strcpy(user[2],"ccc ccc");
	strcpy(user[3],"ddd ddd");

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
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	
	if( bind(sockfd,(SA*)&servaddr,sizeof(servaddr)) != 0)
	{
		printf("\nBinding failed");
		exit(1);
	}
	else
	{
		printf("\nBinding successful");
	}

	if( listen(sockfd,5) == 0)
	{
		printf("\nServer is listening");
	}
	else
	{
		printf("\nListening failed");
		exit(1);
	}
	
	len = sizeof(cli);
	connfd = accept(sockfd,(SA*)&cli,&len);
	
	if(connfd == -1)
	{
		printf("\nConnection failed");
		exit(1);
	}
	else
		printf("\nConnection successful");

	bzero(buff,MAX);
	int fl = 0;
	read(connfd,buff,sizeof(buff));
	
	for(i = 0;i < 4;i++)
	{
		if(strcmp(buff,user[i]) == 0)
		{
			fl = 1;
			break;
		}
	}
	bzero(buff,sizeof(buff));
	if(fl == 1)
	{
		strcpy(buff,"Valid Username");
		write(connfd,buff,sizeof(buff));
	}	
	else
	{
		strcpy(buff,"Invalid Username/password");
		write(connfd,buff,sizeof(buff));
		exit(1);
	}
	char flag[] = "01111110",msg[20],data[11];
	int c = 0;
	fl = 0;
	bzero(buff,MAX);
	read(connfd,buff,sizeof(buff));
	for(i = 0;i < 8;i++)
		if(buff[i] != flag[i])
		{
			fl = 1;
			break;
		}
	for(i = 0;i < 10;i++)
		data[i] = buff[i+8];
	if(fl == 1)
		strcpy(msg,"Wrong flag\n");
	else
		strcpy(msg,"Correct flag\n");
	for(i = 0;i < 10;i++)
		if(data[i] == 1)
			c++;
	if(c % 2 == 1)
		data[10] = '0';
	else
		data[10] = '1'; 
	bzero(buff,sizeof(buff));
	strcpy(buff,msg);
	strcat(buff,data);	
	write(connfd,buff,sizeof(buff));
	return 0;
}
