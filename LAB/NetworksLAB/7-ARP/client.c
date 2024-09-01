#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include <sys/ioctl.h>
#include<netdb.h>
#include <net/if.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

char * get_ip()
{
    int n;
    struct ifreq ifr;
    char array[] = "eth0";

    n = socket(AF_INET, SOCK_DGRAM, 0);

    //Type of address to retrieve - IPv4 IP address
    ifr.ifr_addr.sa_family = AF_INET;

    //Copy the interface name in the ifreq structure
    strncpy(ifr.ifr_name , array , IFNAMSIZ - 1);

    ioctl(n, SIOCGIFADDR, &ifr);
    close(n);

    return inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr);
}

char * get_mac()
{
    struct ifreq s;
    int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    char temp[100],*mac=(char*)malloc(sizeof(char)*500);
    strcpy(mac,"");
    strcpy(s.ifr_name, "eth0");
    if (0 == ioctl(fd, SIOCGIFHWADDR, &s)) {
        int i;
        for (i = 0; i < 6; ++i)
        {
            sprintf(temp,"%02x%s", (unsigned char) s.ifr_addr.sa_data[i],(i<5?":":""));
            strcat(mac,temp);
        }
    }
    printf("%s",mac);
    return mac;
}

int check_ip(char *ip)
{
	char *oip=get_ip();
	if(strcmp(ip,oip)==0)
		return 1;
	return 0;
}

int main(int argc,char* argv[]){

	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(9999);
	serverAddr.sin_addr.s_addr = inet_addr("172.17.51.213");
    // serverAddr.sin_addr.s_addr = INADDR_ANY;

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");
	
	char ch[1024],ch1[1024];
	
    //recieve data from server
    recv(clientSocket, &ch, sizeof(ch), 0);
    printf("The received IP from the server is : ");
    puts(ch);
    strcpy(ch1,ch);
    
    if(check_ip(ch1))
    {
    	bzero(ch, sizeof(ch));
    	strcpy(ch,get_mac());
    	send(clientSocket,ch,strlen(ch),0);
    	puts("\nConnection successful!");
    }
    else 
    puts("\nConnection un-successful");

	return 0;
}
   
