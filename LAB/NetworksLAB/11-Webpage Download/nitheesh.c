
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    char domain[20], path[50];
    sscanf(argv[1], "https://%[^/]%[^\n]", domain, path);

    printf("\nDomain:%s\nPath:%s\n", domain, path);

    struct hostent *server;
    server = (struct hostent *)malloc(sizeof(struct hostent));
    server = gethostbyname(domain);
    struct in_addr *ip = (struct in_addr *)server->h_addr_list;

    int len, s;

    struct sockaddr_in sin;

    sin.sin_port = htons(80);
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(inet_ntoa(*ip[0]));

    s = socket(PF_INET, SOCK_STREAM, 0);

    if (connect(s, (struct sockaddr *)&sin, sizeof(sin)))
    {
        printf("\nConnect error");
        return -1;
    }

    printf("Connected");

    char buff[100];
    sprintf(buff, "GET %s HTTP/1.1\r\nHost: %s \r\n\r\n", path, domain);
    len = send(s, buff, sizeof(buff), 0);

    char buff2[1000];

    FILE *fp = fopen("temp.html", "w");
    while (len = recv(s, buff2, sizeof(buff2), 0))
    {
        for (int i = 0; i < 1000; i++)
        {
            if (feof(fp))
                break;
            fputc(buff2[i], fp);
        }
        break;
    }

    fclose(fp);
    close(s);
    return 0;
}