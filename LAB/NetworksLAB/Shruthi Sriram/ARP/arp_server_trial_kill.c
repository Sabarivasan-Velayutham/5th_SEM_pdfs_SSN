#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/ioctl.h>

#define MAX_PENDING 5
#define MAX_LINE 256

int validate_ip(char str[])
{
	char num[100];
	int k = 0, dot_cnt = 0, flag = 0;
	
	for(int i = 0; str[i] != '\0'; i++)
	{
		if(!isdigit(str[i]) && str[i] != '.')
		{
			flag = 1;
			break;
		}
		if(str[i] != '.')
		{
			num[k] = str[i];
			k++;
		} 
		if(str[i] == '.')
		{
			dot_cnt++;
			num[k] = '\0';
			if(atoi(num) > 255 || atoi(num) < 0)
			{
				flag = 1;
				break;
			}
			else
			{
				k = 0;
				bzero(num, sizeof(num));
			}
		}
	}
	if(dot_cnt != 3)
	{
		flag = 1;
	}
	return flag;
}


int main(int argc, char **argv) 
{
	struct sockaddr_in sin, sin2;
	int len, flag=0;
	int s, new_s;
	char buf[MAX_LINE];
	int count = 0;
	int pid;
	int SERVER_PORT = atoi(argv[1]);

	s = socket(PF_INET, SOCK_STREAM, 0);
	//memset(&sin, '\0', sizeof(sin));

	bzero((char *)&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(SERVER_PORT);

	bind(s, (struct sockaddr *)&sin, sizeof(sin));

	listen(s, 10);

	printf("IP: ");
	scanf(" %s", buf);
	printf("\n");

	flag = validate_ip(buf);
	int mac_recv = 0;
	if(flag == 0)
	{
		while (1) 
		{
			new_s = accept(s, (struct sockaddr *)&sin2, &len);
			if (new_s < 0) 
			{
				exit(1);
			}
			count++;
			if ((pid = fork()) == 0) 
			{
				close(s);

				send(new_s, buf, strlen(buf), 0);
				sleep(4);
				bzero(buf, sizeof(buf));
				recv(new_s, buf, sizeof(buf), 0);
				if(strncmp(buf," ", 1))
				{
					printf("\nMAC RECEIVED: %s", buf);
					mac_recv = 1;
				}
				if(!mac_recv)
				{
					printf("IP does not match\n");
				}
				kill(pid, SIGKILL);
			}
		}
	}
	else
	{
		printf("NOT VALID!!");
	}
	close(s);
	close(new_s);
}