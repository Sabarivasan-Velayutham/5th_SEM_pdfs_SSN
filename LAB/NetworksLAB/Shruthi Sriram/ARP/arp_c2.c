#include <fcntl.h>
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

int main(int argc, char *argv[])
{
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
  strncpy(ifr.ifr_name, "eth0", IFNAMSIZ - 1); // enp3s0

  ioctl(fd, SIOCGIFADDR, &ifr);

  close(fd);

  /* display result */
  char ip[100];
  char mac[100];
  strcpy(ip, "10.6.10.26");
  printf("IP: %s", ip);

  FILE *f = fopen("/sys/class/net/enp3s0/address", "r"); // enp3s0
  if (f != NULL)
  {
    fread(mac, sizeof(char), MAX_LINE, f);
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
    printf("\nIP DOES NOT MATCH\n");
  }
  close(s);
}
