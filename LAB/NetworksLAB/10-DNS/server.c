// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<ctype.h>
	
#define PORT	 7531
#define MAXLINE 1024

typedef struct DNS{
	char name[255],ip[255];
}DNS;


int validate_number(char *str) {
   while (*str) {
      if(!isdigit(*str)){
         return 0;
      }
      str++;
   }
   return 1;
}

int validate_ip(char *ip) {
   int i, num, dots = 0;
   char *ptr;
   if (ip == NULL)
      return 0;
      ptr = strtok(ip, ".");
      if (ptr == NULL)
         return 0;
   while (ptr) {
      if (!validate_number(ptr))
         return 0;
         num = atoi(ptr);
         if (num >= 0 && num <= 255) {
            ptr = strtok(NULL, ".");
            if (ptr != NULL)
               dots++;
         } else
            return 0;
    }
    if (dots != 3)
       return 0;
      return 1;
}



// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	struct sockaddr_in servaddr, cliaddr;
		
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
		
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
		
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
		
	int len, n;
	
	len = sizeof(cliaddr); //len is value/result

	int N = 3;

	DNS table[25];

	strcpy(table[0].name,"google.com");
	strcpy(table[0].ip,"142.89.78.66");
	
	strcpy(table[1].name,"yahoo.com");
	strcpy(table[1].ip,"10.2.45.67");
	
	strcpy(table[2].name,"annauniv.com");
	strcpy(table[2].ip,"197.34.53.122");


	while(1){

		int op;		
		
		printf("\nUpdate[0] or Recieve[1]:");
		
		scanf("%d",&op);
		
		if(op==0){
			while(1){
			
				char site[250],newIP[255];
				printf("Name and IP:");
				scanf("%s %s",site,newIP);
				
				char newnewIP[255];
				
				strcpy(newnewIP,newIP);
			
				if(validate_ip(newIP)){
			
					strcpy(table[N].name,site);
					strcpy(table[N].ip,newnewIP);
					N++;
					break;
				}else printf("Invalid IP..\n");
			
			}
				
		}
		
		else{
		
			n = recvfrom(sockfd, (char *)buffer, MAXLINE,MSG_WAITALL, ( struct sockaddr *) &cliaddr,&len);
			buffer[n] = '\0';
			printf("Client : %s\n", buffer);
			char IP[255];
		
			for(int i=0;i<N;i++){
				if(strcmp(table[i].name,buffer)==0){
					strcpy(IP,table[i].ip);
					printf("IP:%s\n",IP);
				}
			}
		
			sendto(sockfd, (char *)IP, strlen(IP),MSG_CONFIRM,(const struct sockaddr *) &cliaddr,len);
			printf("Hello message sent.\n");
		
		}
		
	}	
	
		
	return 0;
}
