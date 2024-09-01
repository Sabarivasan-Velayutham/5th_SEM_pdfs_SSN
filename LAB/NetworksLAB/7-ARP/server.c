#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int validate_number(char *str)
{
	while (*str)
	{
		if (!isdigit(*str))
			return 0;
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

	int sockfd, ret;
	struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	pid_t childpid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(9999);
	serverAddr.sin_addr.s_addr = inet_addr("172.29.134.86");
	// serverAddr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	if (ret < 0)
	{
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port \n");

	if (listen(sockfd, 10) == 0)
	{
		printf("[+]Listening....\n");
	}
	else
	{
		printf("[-]Error in binding.\n");
	}

	char ch[1024];
	char ch1[1024];

	do
	{
		printf("Enter IP to connect : ");
		gets(ch);
		strcpy(ch1, ch);
	} while (validate_ip(ch1) == 0);

	while (1)
	{
		newSocket = accept(sockfd, (struct sockaddr *)&newAddr, &addr_size);
		if (newSocket < 0)
		{
			exit(1);
		}

		if ((childpid = fork()) == 0)
		{
			close(sockfd);
			send(newSocket, ch, strlen(ch), 0);
			bzero(ch, sizeof(ch));
			int rb = recv(newSocket, &ch, sizeof(ch), 0);
			if (rb > 0)
			{
				printf("MAC Address Received : %s\n", ch);
				// exit(1);
			}
		}
	}

	close(newSocket);

	return 0;
}
