#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include<string.h>
#include<ctype.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>
char * MAC()
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
    return mac;
}

char * IP()
{
    int n;
    char *ip=(char*)malloc(sizeof(char)*500);
    struct ifreq ifr;
    char array[] = "eth0";
    n = socket(AF_INET, SOCK_DGRAM, 0);
    //Type of address to retrieve - IPv4 IP address
    ifr.ifr_addr.sa_family = AF_INET;
    //Copy the interface name in the ifreq structure
    strncpy(ifr.ifr_name , array , IFNAMSIZ - 1);
    ioctl(n, SIOCGIFADDR, &ifr);
    close(n);
    //display result
    sprintf(ip,"%s", inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr) );
    return ip;
}
int isValidIP(char *ip)
{
	int dot_cnt=0;
	for(int i=0;ip[i];i++)
	{
		if(ip[i]=='.')
			dot_cnt++;
		else if(ip[i]<'0' || ip[i]>'9')
			return 0;
	}
	if(dot_cnt!=3)
		return 0;
	strcat(ip,".");
	char s[10]={0},temp[2];
	temp[1]='\0';
	int ok=1;
	for(int i=0;ip[i];i++)
	{
		temp[0]=ip[i];	
		if(ip[i]!='.')
			strcat(s,temp);	
		else
		{
			strcat(s,"\0");
  			char *ptr;
   			long num= strtol(s, &ptr, 10);
			if(!num && ptr[0]!='\0')
				return 0;
			if(num<0 || num>255)
				return 0;
    			memset(s, 0, 10);
		}
	}
	return 1;
}
int isValidMAC(char *mac)
{
	int col_cnt=0;
	for(int i=0;mac[i];i++)
	{
		if(mac[i]==':')
			col_cnt++;
		else if(!isdigit(mac[i]) && (!isalpha(mac[i]) || ( isalpha(mac[i]) && (mac[i]<'a' || mac[i]>'f'))))
			return 0;
	}
	if(col_cnt!=5)
		return 0;
	for(int i=2;mac[i];i=i+3)
		if(mac[i]!=':')
			return 0;
	return 1;
}
int main(int argc, char const* argv[])
{
	int port=atoi(argv[1]);
    int sockD = socket(AF_INET, SOCK_STREAM, 0); 
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port= htons(port);
    servAddr.sin_addr.s_addr = INADDR_ANY;
    char *ip=IP();
    char *ip1=IP();
    char *mac=MAC();
	printf("\nMy MAC:%s\n",mac);
	printf("\nMy IP:%s\n",ip);
    if(isValidIP(ip1))
       printf("\nip validated\n");
    else
       printf("\ninvalid ip\n");
       if(isValidMAC(mac))
       printf("\nmac validated\n");
    else
       printf("\ninvalid mac\n");
    int connectStatus= connect(sockD, (struct sockaddr*)&servAddr,sizeof(servAddr));
    if (connectStatus == -1)
		printf("Error...\n");
    else 
    {
        char strData[255];
        recv(sockD, strData, sizeof(strData),0);

		printf("\nRARP request received!\n");
        
		if(!strcmp(strData,mac))
        	{
        	strcpy(strData,ip);
        	printf("MAC matched!\nIP sent!\n");
        	}
        else
		{
			printf("\nMAC NOT MATCHED! MAC = %s received\n",strData);        	
			strcpy(strData,"False");
		}
        send(sockD, strData, sizeof(strData), 0);
        if(!strcmp(strData,mac))
        {
        	recv(sockD, strData, sizeof(strData),0);
        	printf("Ack: %s\n",strData);
        }
    }
    
 	return 0;
 }
