#include <netinet/in.h> //structure for storing address
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

#define PORT 6666
int ham_code_len;
char ham_code[20];

int check_parity(int n, int i, char code[])
{
    int p = 0, k;
    for (int j = i; j <= n; j = k + i)
    {
        for (k = j; k < j + i && k <= n; k++) // for i=1 ->bits=1,3,5,7,9,11    for i=2 ->bits 2,3,6,7,10,11
        {                                     // i is parity bit position
            if (code[k] == '1')
                p++;
        }
    }
    if (p % 2 == 0)
        return 0; // if no. of 1 is even return 0
    else
        return 1; // if no. of 1 is odd return 1
}

void hamming_code(int data[], int num)
{
    int r = 0, m = 0, n, j = 1, c;
    // static int code[20]; 
    char code[20];

    while ((r + num + 1) > (pow(2, r))) // calculating no. of parity/redundant bits
        r++;

    n = num + r; // adding no. of redundant bits to array size
    for (int i = 1; i <= n; i++)
    {
        if (i == pow(2, m) && m <= r)
        {
            code[i] = 0; // initializing all the bit position of power 2 to zero
            m++;
        }
        else
        {
            code[i] = data[j]; // assgning data to remaining positions
            j++;
        }
    }

    m = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i == pow(2, m) && m <= r)
        {
            c = check_parity(n, i, code); // assigning parity bit to position of power 2
            code[i] = c;
            m++;
        }
    }

    printf("The hamming code for given data is : ");
    for (int i = n; i > 0; i--)
    {
        printf("%c", code[i]);
        // ham_code[i] = code[i] + '0';
        // printf("Char : %c",ham_code[i]);
    }

    printf("\n");
    // char *temp;
    // temp = (char *)malloc(sizeof(char) * (n + 1));
    // for (int i = n; i > 0; i--)
    //     temp[i] = code[i] + '0';

    // printf("Char Array: ");
    // for(int i=0;i<n;i++)
    // 	printf("%c ", temp[i]);
    // temp[n] = '\0';

    // printf("\n");
    printf("Message : %s", code);

    ham_code_len = n;
    return;
    // return code;
}

int main(int argc, char **argv)
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created. \n");

    struct sockaddr_in client_address;
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(PORT);
    client_address.sin_addr.s_addr = INADDR_ANY;

    int connectStatus = connect(client_socket, (struct sockaddr *)&client_address, sizeof(client_address));
    if (connectStatus == -1)
    {
        perror("[-]Error in Connecting");
        exit(1);
    }

    int data[10], num;

    printf("Enter the size of data : ");
    scanf("%d", &num);
    printf("Enter the data : ");
    for (int i = num; i > 0; i--)
        scanf("%d", &data[i]);
    // hamming_code(data, num);
    // printf("Lenght : %d",ham_code_len);
    // for (int i = ham_code_len; i > 0; i--)
    //     printf("%c ",ham_code[i]);

    hamming_code(data, num);
    // hamming_code(data, num);
    printf("hello mame\n");
    // int ham_code_len = *(&ham_code + 1) - ham_code; // using pointer arithmetic.
    printf("Lenght : %d\n", ham_code_len);

    // char *msg = ham_code;
    // printf("Message : %s",msg);
    // char str_ham_code[20] = ""
    // for (int i = ham_code_len; i > 0; i--)
    // {
    //     str_ham_code += ham_code[i];
    //     printf("%s",str_ham_code);
    // }
    send(client_socket, ham_code, strlen(ham_code), 0);
    printf("Haming code sent ...\n");

    // for (int i = ham_code_len; i > 0; i--)
    // {
    //     sprintf(string, "%d", ham_code[i]);
    //     str_ham_code += string;
    //     printf("%s",str_ham_code);
    // }

    // printf("%d ",ham_code[i]);
    // printf("Hamming code : %ls\n", code);
    // char *enc = encode(argv[1], find_r(argv[1]), atoi(argv[2]));
    // send(client_socket, &ham_code, ham_code_len , 0);
    // printf("Length : %d",ham_code_len);
    // send(client_socket, ham_code, ham_code_len , 0);
    // char msg[255];
    // recv(client_socket, msg, sizeof(msg), 0);
    // printf("Message : %s\n", msg);
    close(client_socket);
    return 0;
}