
// 1.	Establish the basic connection between client and the server.
// 2.	Develop an application to simulate error correction using hamming code technique
// 3.	Client gets input data from user
// 4.	Find the number of bits to be transmitted
// 5.	Find the redundant code to be generated depending on the number of bits in the data
// 6.	Compute the value of r bits
// 7.	Embed “r” bits in data and send the data to the server
// 8.	Server will find the r bits and finds whether the data has error or not. If error present, then it will find the location of error.
// 9.	Correct the data if it contains error and display it.

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define PORT 6666

int main(int argc, char **argv)
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created. \n");

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int e = bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    if (e < 0)
    {
        perror("[-]Error in Binding");
        exit(1);
    }
    printf("[+]Binding Successfull.\n");
    e = listen(server_socket, 1);
    if (e == 0)
    {
        printf("[+]Listening...\n");
    }
    else
    {
        perror("[-]Error in Binding");
        exit(1);
    }

    int client_socket = accept(server_socket, NULL, NULL);

    char code[20];
    // printf("%s",code);
    recv(client_socket, code, sizeof(code), 0);
    int m = strlen(code);
    printf("Hamming code Recieved : %s\n", code);
    // int *ham_code = malloc(20*sizeof(int));
    // printf("malloc\n");
    // int ham_code_len;
    // recv(client_socket, code, sizeof(code), 0);
    // recv(client_socket, ham_code, ham_code_len , 0);
    // printf("Received...\n");
    // printf("Lenght : %d",ham_code_len);
    // int m = strlen(code);
    // for (int i = ham_code_len; i > 0; i--) printf("%d ",ham_code[i]);
    // printf("Recieved:%s\n", code);
    // char *msg = "msg recieved";
    // decode(code, find_r(code));
    // send(client_socket, msg, strlen(msg), 0);
    close(server_socket);
    return 0;
}