#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int socket_desc, i, bytes_read;    
    char server_reply[1024], ip[100], request[100],trail[100],filename[50];
    char *hostname = argv[1];
    struct sockaddr_in server;
    struct hostent *he;
    struct in_addr **addr_list;
    FILE *fp;

	/*Splitting the trailer part*/	
	strcpy(trail,"\0");

	int l = 0;

	for(l=0;l<strlen(hostname);l++)
		if(hostname[l] == '/')
		{
			break;
		}

	if(l!=strlen(hostname))
	{
		strcpy(trail,hostname+l);
		hostname[l] = '\0';
		printf("Hostname = %s, file = %s",hostname,trail);
	}

    if ((he = gethostbyname(hostname)) == NULL) {
        //gethostbyname failed
        herror("gethostbyname\n");
        return 1;
    }

    addr_list = (struct in_addr **) he->h_addr_list;

    for(i = 0; addr_list[i] != NULL; i++) {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
    }

    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket!\n");
    }

    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    //Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0) {
        printf("connect error!\n");
        return 1;
    }

    printf("Connected...\n");
	
	for(int i=0;hostname[i]!='\0';i++)
    //Send some data
    snprintf(request, 99, "GET %s HTTP/1.1\r\n"
            "Host: %s\r\n"
            "\r\n\r\n", trail,hostname
    );

    if (send(socket_desc, request, strlen(request), 0) < 0) {
        puts("Send failed!\n");
        return 1;
    }
    puts("Data Sent...\n");

    //Receive a reply from the server
	printf("\nEnter the filename: ");
	scanf(" %s",filename);

    fp = fopen(filename, "w+");

    while (bytes_read = read(socket_desc, server_reply, sizeof(server_reply)) > 0) {
        fputs(server_reply, fp);
        memset(server_reply, 0, sizeof(server_reply));
    } 
    do {
        bytes_read = read(socket_desc, server_reply, sizeof(server_reply));
        fputs(server_reply, fp);
        memset(server_reply, 0, sizeof(server_reply));
    } while (bytes_read > 0);

    printf("reply received...\n");

    fclose(fp);
    close(socket_desc);

    return 0;
}
