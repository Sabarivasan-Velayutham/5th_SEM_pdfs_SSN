#include <errno.h> 
#include <arpa/inet.h> 
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <net/if.h>

#define MAX_PENDING 5
#define MAX_LINE 256

int main(int argc, char *argv[]) {
  struct sockaddr_in sin;
  char *host, *ip_addr;
  int s;
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
  int fd;
 struct ifreq ifr;

 fd = socket(AF_INET, SOCK_DGRAM, 0);

 /* I want to get an IPv4 IP address */
 ifr.ifr_addr.sa_family = AF_INET;

 /* I want IP address attached to "eth0" */
 strncpy(ifr.ifr_name, "enp0s3", IFNAMSIZ-1);      //enp3s0

 ioctl(fd, SIOCGIFADDR, &ifr);

 close(fd);

 /* display result */
  char ip[100];
  char mac[100];
  strcpy(ip, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
  printf("IP: %s", ip);

  FILE *f = fopen("/sys/class/net/enp0s3/address", "r");      //enp3s0
  if (f != NULL) 
  {
    fread(mac, sizeof(char), MAX_LINE, f);
  }
  fclose(f);
  mac[18] = '\0';
  printf("\nMAC: %s\n", mac);
  bzero(buf, sizeof(buf));
  recv(s, buf, sizeof(buf), 0);

  int i=0,t=1,c=1;
  /*while(c<12)
  {
    if(mac[i]==':')
    {
      i++;
    }
    else
    {
      //printf(" %c-%c ",mac[i],buf[i]);
      if(mac[i]!=buf[i])
      {
           printf(" %c-%c ",mac[i],buf[i]);
           t=0;
           break;
      }
      i++;
      c++;
    }

  }*/
  printf("msg received: %s\n", buf);
  //printf("%d %ld %ld\n", strcmp(buf, mac), strlen(mac), strlen(buf));
  if(strncmp(buf, mac, 17) == 0)
  {
	printf("\nMAC MATCHES");
    printf("\nRARP CONNECTION ESTABLISHED\n");
    send(s, ip, strlen(ip), 0);
  }
	else
  {
    printf("MAC DOES NOT MATCH\n");
 }
  /*if (!strncmp(mac, buf, strlen(mac))) 
  {
    printf("\nMAC MATCHES");
    printf("\nRARP CONNECTION ESTABLISHED\n");
    send(s, ip, strlen(ip), 0);
  }*/
  

  close(s);
}