#include<fcntl.h>
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
  
//char maca[100];
//char *maca="00.40.a2.11.af.22";


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
	
  char ip[100];
  char mac[100];
  strcpy(ip, "10.6.10.26");
  strcpy(mac, "00:40:a2:11:af:22");

  printf("IP: %s\n",ip);
  printf("MAC: %s\n",mac);    //cannot print in the same line as killed
  
  char buf[MAX_LINE];
 
 /* display result */

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
           
           t=0;
           break;
      }
i++;
c++;
    }

  }*/
  if(strncmp(mac, buf, 17) == 0)
  {
printf("\nMAC MATCHES");
    printf("\nRARP CONNECTION ESTABLISHED\n");
    send(s, ip, strlen(ip), 0);
  }
else
  {
    printf("\nMAC DOES NOT MATCH\n");
 }
  /*if (!strcmp(mac, buf)) 
  {
    printf("\nMAC MATCHES");
    printf("\nRARP CONNECTION ESTABLISHED\n");
    send(s, ip, strlen(ip), 0);
  }*/
  
  close(s);
}

