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

int main(int argc, char *argv[]) 
{
	struct sockaddr_in sin;
	char *host, *ip_addr;
	int s, new_s;
	int SERVER_PORT;

	SERVER_PORT = atoi(argv[1]);
	ip_addr = argv[2];

	s = socket(PF_INET, SOCK_STREAM, 0);

	bzero((char *)&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(SERVER_PORT);
	sin.sin_addr.s_addr = inet_addr(ip_addr);
	connect(s, (struct sockaddr *)&sin, sizeof(sin));

	char buf[MAX_LINE];
	struct ifreq ifr;

	new_s = socket(AF_INET, SOCK_DGRAM, 0);

	/* I want to get an IPv4 IP address */
	ifr.ifr_addr.sa_family = AF_INET;

	/* I want IP address attached to "eth0" */
	strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);      //enp3s0

	ioctl(new_s, SIOCGIFADDR, &ifr);

	close(new_s);

	/* display result */
	char ip[100];
	char mac[100];
	strcpy(ip, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
	printf("IP: %s", ip);

	FILE *f = fopen("/sys/class/net/eth0/address", "r");      //enp3s0
	if (f != NULL) 
	{
		fread(mac, sizeof(char), 100, f);
	}
	printf("\nMAC: %s", mac);
	bzero(buf, sizeof(buf));
	recv(s, buf, sizeof(buf), 0);
	if (!strncmp(ip, buf, strlen(ip))) 
	{
		printf("\nIP MATCHES");
		printf("\nARP CONNECTION ESTABLISHED\n");
		send(s, mac, strlen(mac), 0);
	}
	else
	{
		strcpy(buf, " ");
		send(s, buf, strlen(buf), 0);
		printf("\nIP DOES NOT MATCH\n");
	}

	close(s);
}