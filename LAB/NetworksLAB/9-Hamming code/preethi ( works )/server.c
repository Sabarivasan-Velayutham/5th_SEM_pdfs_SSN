#include <netinet/in.h> //structure for storing address information
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include "hc.h"
#include <math.h>

int main(int argc, char const* argv[])
{
	int servSockD = socket(AF_INET, SOCK_STREAM, 0);
	char rev_msg[255];
	int port=atoi(argv[1]);

	struct sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	servAddr.sin_addr.s_addr = INADDR_ANY;

	bind(servSockD, (struct sockaddr*)&servAddr,sizeof(servAddr));
	listen(servSockD, 1);
	int clientSocket = accept(servSockD, NULL, NULL);
	
	hc packet;
	recv(clientSocket, &packet, sizeof(packet), 0);
	printf("Data received : %s\n\n", packet.msg+1);
	strcpy(rev_msg,packet.msg);
	reverseStr(rev_msg+1);
	int pos=check(rev_msg,packet.r);
	if(!pos)
		printf("\nThere's no error in the data recieved\n");
	else
	{
		printf("\nThere's error in the received Data!\n");
		printf("\nBit-position %d is changed!\n",pos);
		rev_msg[pos]=(rev_msg[pos]=='0'?'1':'0');
		strcpy(packet.msg,rev_msg);
		reverseStr(packet.msg+1);
		printf("\nCorrect Original Data: %s\nProof: ",packet.msg+1);
		check(packet.msg,packet.r);
	}
	int k=0;
	char data[255];
	for(int i=0;rev_msg[i];i++)
		if(i&(i-1))
			data[k++]=rev_msg[i];
	data[k]='\0';
	reverseStr(data);
	close(servSockD);
	
	printf("\nTransmitted Data Bit: %s\n",data);
	return 0;
}
