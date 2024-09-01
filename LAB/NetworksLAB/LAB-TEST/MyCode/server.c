
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
	char username[][20] = {"sabari","krishna","praveen","vignesh"};
	char password[][20] = {"sab123","kris123","pra123","vig123"};
	char flagstr[10] ;
	strcpy(flagstr,"0111110");
	
	int socketfd = socket(AF_INET,SOCK_STREAM,0);
	if (socketfd<0) 
	{
		printf("[-] Socket not created ... \n");
		exit(1);
	}
	printf("[+] Socket created ... \n");
	
	struct sockaddr_in servaddr;
	struct sockaddr_in newaddr;
	
	socklen_t addr_size;
	
	int port = atoi(argv[1]);
	
	memset(&servaddr,'\0',sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = inet_addr("10.6.10.9");
	
	int e = bind(socketfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if (e<0) 
	{
		printf("[-] Binding error ... \n");
		exit(1);
	}
	printf("[+] Socket binded successfully ... \n");
	
	e = listen(socketfd,10);
	if (e<0) 
	{
		printf("[-] Listening error ... \n");
		exit(1);
	}
	printf("[+] Server listening ... \n");
	
	int newsocket = accept(socketfd,(struct sockaddr*)&newaddr,&addr_size);
	if (newsocket<0) 
	{
		printf("[-] Acceptance error ... \n");
		exit(1);
	}
	printf("[+] Connection established ... \n");
	
	char user[1024];
	char passwd[1024];
	char buffer[1024];
	
	recv(newsocket,user,sizeof(user),0);
	printf("Received username : %s\n",user);		
	bzero(user,sizeof(user));
	recv(newsocket,passwd,sizeof(passwd),0);
	printf("Received password : %s\n",passwd);		
	bzero(passwd,sizeof(passwd));
	
	
	int flag = 0 ;
	for (int i = 0 ; i < 4 ; i++)
	{
		if (!strcmp(user,username[i]))
		{
			if (!strcmp(passwd,password[i]))  strcpy(buffer,"User logged in ... \n");
			else strcpy(buffer,"Invalid password ... \n");
			break;
		}
		else flag++;
			
	}
	if (flag==4) strcpy(buffer,"Invalid Username ... \n");
	
	send(newsocket,buffer,sizeof(buffer),0);
	printf("Data sent ... \n");

	/*for (int i = 0 ; i < 18 ; i++)
	{
		if (data)
	}*/	
		
	

	return 0 ;
}
