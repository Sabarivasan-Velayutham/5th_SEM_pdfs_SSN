#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/signal.h>

#define MAX_PENDING 5
#define MAX_LINE 256


int isValidMacAddress(const char* mac) {

    int i = 0;
    int s = 0;

    while (*mac) {
       if (isxdigit(*mac)) {
          i++;
       }
       else if (*mac == ':' || *mac == '-') {

          if (i == 0 || i/2 - 1 != s)
            break;

          ++s;
       }
       else {
           s = -1;
       }


       ++mac;
    }

    return (i == 12 && (s == 5 || s == 0));
}

int main(int argc, char **argv) {

  struct sockaddr_in sin, sin2;
  int len,flag = 1;
  int s, new_s;
  char buf[MAX_LINE];
  int count = 0;
  int pid;
  int SERVER_PORT = atoi(argv[1]);

  /* setup passive open */
  s = socket(PF_INET, SOCK_STREAM, 0);
  memset(&sin, '\0', sizeof(sin));
  /* build address data structure */
  bzero((char *)&sin, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(SERVER_PORT);

  if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    perror("bind error");

  listen(s, 10);

  printf("\nENTER MAC: ");
  scanf(" %s", buf);
  char temp[MAX_LINE];
  //strcpy(temp, buf);
  //flag = isValidMacAddress(temp) ? 1 : 0;
  //printf("\nflag = %d", flag);
  int k = 0;
  
  if(flag != 1){
  	printf("NOT VALID!!\n");
  	return 0;
  }
  
  while (1) {
	/* wait for connection, then receive and print text */
	new_s = accept(s, (struct sockaddr *)&sin2, &len);
	if (new_s < 0) {
	  exit(1);
	}
	
	send(new_s, buf, sizeof(buf), 0);
	sleep(1);
	count++;
	
	if ((pid = fork()) == 0) {
	  
	  bzero(buf, sizeof(buf));
	  recv(new_s, buf, sizeof(buf), 0);
	  
	  if(strcmp(buf,""))
	  {
	    printf("IP RECEIVED: %s\n", buf);
	    k = 1;
	    sleep(1);
	    kill(pid, SIGKILL);
	  }
	  break;
	}
	if(k == 1)
		break;
  }
  
  close(s);
  close(new_s);
}