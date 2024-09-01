#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define PORT 6666

int find_r(char *code)
{
	int r = 0, m = strlen(code);
	int cur = 1;
	while (cur < m + r + 1)
	{
		cur *= 2;
		r++;
	};
	return r;
}

void decode(char *code, int r)
{
	int c = 1, n = strlen(code);
	int parity[r];
	int x = 0;
	int chk = 1;
	while (r > x)
	{
		int o = 0;
		for (int i = n - chk; i >= 0; i -= 2 * chk)
		{
			for (int j = i; j > i - chk; j--)
			{
				if (j < 0)
					break;
				if (code[j] == '1')
					o++;
			}
		}
		parity[x++] = o % 2 ? 1 : 0;
		chk *= 2;
	}

	int val = 0, v = 1;
	for (int j = 0; j < r; j++)
	{
		val += v * parity[j];
		v *= 2;
	}
	printf("\nError in bit %d", n-val+1 );
	printf("\nCorrected Code:");
	for (int i = 0; i < n; i++)
	{
		if (i == n - val)
		{
			if (code[i] == '1')
				printf("0");
			else
				printf("1");
		}
		else
			printf("%c", code[i]);
	}
}

int main(int argc, char **argv)
{
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_address;

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;

	bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
	listen(server_socket, 1);

	int client_socket = accept(server_socket, NULL, NULL);

	char code[255];

	recv(client_socket, code, sizeof(code), 0);

	int m = strlen(code);
	printf("Recieved:%s\n", code);

	char *msg = "msg recieved";

	decode(code, find_r(code));

	send(client_socket, msg, strlen(msg), 0);

	close(server_socket);

	return 0;
}
