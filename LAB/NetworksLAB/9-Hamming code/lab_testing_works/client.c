#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
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

char *encode(char *code, int r, int err)
{
	int c = 1, n = strlen(code) + r;
	char enc_code[n + 1];
	int i = 0;
	while (i < r)
	{
		enc_code[n - c] = 'r';
		c *= 2;
		i++;
	}
	// printf("ENC CODE : %s",enc_code);
	int k = 0;
	for (i = 0; i < n; i++)
	{
		if (enc_code[i] != 'r')
		{
			enc_code[i] = code[k++];
		}
	}
	enc_code[i] = '\0';
	
	// checking
	for (int i = 0 ; i < n ; i++) printf("%c ",enc_code[i]);

	int chk = 1;
	while (r--)
	{
		int o = 0;
		for (int i = n - chk; i >= 0; i -= 2 * chk)
		{
			for (int j = i; j > i - chk; j--)
			{
				if (j < 0)
					break;
				if (enc_code[j] == '1')
					o++;
			}
		}
		enc_code[n - chk] = o % 2 ? '1' : '0';
		chk *= 2;
	}
	if (err != -1)
		enc_code[err-1] = (enc_code[err-1] == '1') ? '0' : '1';

	char *enc = enc_code;
	return enc;
}

int main(int argc, char **argv)
{

	int client_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in client_address;

	client_address.sin_family = AF_INET;
	client_address.sin_port = htons(PORT);
	client_address.sin_addr.s_addr = INADDR_ANY;

	connect(client_socket, (struct sockaddr *)&client_address, sizeof(client_address));

	char *enc = encode(argv[1], find_r(argv[1]), atoi(argv[2]));

	send(client_socket, enc, strlen(argv[1]) + find_r(argv[1]), 0);

	char msg[255];

	recv(client_socket, msg, sizeof(msg), 0);

	printf("Message:%s\n", msg);

	close(client_socket);

	return 0;
}
