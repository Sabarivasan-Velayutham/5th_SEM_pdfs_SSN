// Server side implementation of UDP client-server model
#include "dns.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define MAXLINE 1024

int main()
{

  dns values[15];
  int no = 3;

  // printf("\nEnter the no of websites: ");
  // scanf("%d", &no);
  /*for (int i = 0; i < no; i++) {
    values[i].n = 1;

    printf("\nEnter the name of website: ");
    scanf(" %s", values[i].name);

    printf("\nEnter the ip: ");
    scanf(" %s", values[i].ips[0]);

    // strcpy(values[i].name,w_name);
    // strcpy(values[i].ips[0],ip);
  }*/
  strcpy(values[0].name, "www.yahoo.com");
  strcpy(values[0].ips[0], "10.2.45.67");
  values[0].n = 1;

  strcpy(values[1].name, "www.annauniv.edu");
  strcpy(values[1].ips[0], "197.34.53.122");
  values[1].n = 1;

  strcpy(values[2].name, "www.google.com");
  strcpy(values[2].ips[0], "142.89.78.66");
  values[2].n = 1;

  int sockfd;
  char buffer[MAXLINE];
  char *retIP = (char *)malloc(sizeof(char) * 500);
  struct sockaddr_in servaddr, cliaddr;

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  memset(&cliaddr, 0, sizeof(cliaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(PORT);

  if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
  {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  int len, n, ch;

  len = sizeof(cliaddr);

  while (1)
  {
    printf("\n1.Modify\n2.Insert new\n3.Display\n4.Direct to Listen\n5.Exit\nEnter your choice: ");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
      if (!append(values, no))
        printf("\nInvalid server name!");
      display(values, no);
      break;
    case 2:
      no++;
      values[no - 1].n = 1;
      printf("\nEnter the name of website: ");
      scanf(" %s", values[no - 1].name);
      int k = 0;
      while (!isValidIP(values[no - 1].ips[0]))
      {
        if (k++)
          printf("\nInvalid IP! Enter again\n");
        printf("\nEnter the ip: ");
        scanf(" %s", values[no - 1].ips[0]);
      }
    case 3:
      display(values, no);
      break;
    case 4:
      break;
    case 5:
      return 0;
    default:
      printf("Invalid choice!\n");
    }
    printf("\n\nListening...\n");
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL,
                 (struct sockaddr *)&cliaddr, &len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    strcpy(retIP, search(values, no, buffer));
    sendto(sockfd, (const char *)retIP, strlen(retIP), MSG_CONFIRM,
           (const struct sockaddr *)&cliaddr, len);
    printf("Reply Sent\n");
  }
  return 0;
}
