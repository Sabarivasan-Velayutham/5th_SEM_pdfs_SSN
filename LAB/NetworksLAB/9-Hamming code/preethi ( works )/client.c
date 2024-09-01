#include <netinet/in.h> //structure for storing address information
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include "hc.h"
#include <math.h>

int main(int argc, char const* argv[])
{
	int flag=0;
	int port=atoi(argv[1]);
	int sockD = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	servAddr.sin_addr.s_addr = INADDR_ANY;
	int connectStatus = connect(sockD, (struct sockaddr*)&servAddr,sizeof(servAddr));
	if(connectStatus == -1) 
		printf("Error...\n");
	else 
	{
		char data[255] ;//= "1011010";
		printf("Enter the Data Bit: ");
		scanf("%s",data);
		int r=find_r(strlen(data));
		char *msg=gen_enc_code(data,r);
		//printf("%s\n",msg+1);
		printf("\nData bit: %s\n",data);
		find_msg(msg,r);
		//char msg[255];
		//strcpy(msg,rev_msg);
		int l=strlen(msg);
		reverseStr(msg+1);
		printf("\nData to be transmitted to the server side: %s\n",msg+1);
		
		//incorporate error
		printf("\nWant to change bits?(y/n): ");
		char ch;
		scanf(" %c",&ch);
		switch(ch)
		{
			case 'y':
			case 'Y':	printf("Enter bit position to invert(1-%d): ",l-1);
						int pos;
						scanf("%d",&pos);
						if(pos<1||pos>l-1)
							printf("Invalid bit position!\n");
						else
						{
							msg[l-pos]=(msg[l-pos]=='0'?'1':'0');
							flag=1;
						}
						break;
			case 'n':case 'N':break;
			default:	printf("\nInvalid choice!\n");
		}
		hc packet;
		packet.r=r,strcpy(packet.msg,msg);
		send(sockD, &packet, sizeof(packet), 0);
		printf("\nData has been sent %s!\n",(flag?"with error":"without error"));
	}
	close(sockD);
	return 0;
}

