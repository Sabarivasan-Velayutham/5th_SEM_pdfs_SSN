#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  char name[100];
  char ips[50][50];
  int n;
} dns;

char *search(dns table[], int n, char *name)
{
  char *ip = (char *)malloc(sizeof(char) * 500);
  strcpy(ip, "No entry");
  for (int i = 0; i < n; i++)
  {
    if (!strcmp(name, table[i].name))
    {
      strcpy(ip, table[i].ips[table[i].n - 1]);
      return ip;
    }
  }
  return ip;
}

void display(dns table[], int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("\nWebsite name: %s", table[i].name);
    for (int j = 0; j < table[i].n; j++)
    {
      printf("\n%s", table[i].ips[j]);
    }
  }
}

int isValidIP(char *ip)
{
  int dot_cnt = 0;
  for (int i = 0; ip[i]; i++)
  {
    if (ip[i] == '.')
      dot_cnt++;
    else if (ip[i] < '0' || ip[i] > '9')
      return 0;
  }
  if (dot_cnt != 3)
    return 0;
  strcat(ip, ".");
  char s[10] = {0}, temp[2];
  temp[1] = '\0';
  int ok = 1;
  for (int i = 0; ip[i]; i++)
  {
    temp[0] = ip[i];
    if (ip[i] != '.')
      strcat(s, temp);
    else
    {
      strcat(s, "\0");
      char *ptr;
      long num = strtol(s, &ptr, 10);
      ok &= ((!num && ptr[0] != '\0') || (num < 0 || num > 255)) ? 0 : 1;
      memset(s, 0, 10);
    }
  }
  ip[strlen(ip) - 1] = '\0';
  return ok;
}

int append(dns table[], int n)
{
  int flag = 0, k = 0;
  char w_name[50], ip[50] = "\0";

  printf("\nEnter the website name: ");
  scanf(" %s", w_name);
  while (!isValidIP(ip))
  {
    if (k++)
      printf("\nInvalid IP! Enter again\n");
    printf("\nEnter the ip: ");
    scanf(" %s", ip);
  }
  for (int i = 0; i < n; i++)
  {
    if (strcmp(table[i].name, w_name) == 0)
    {
      // printf("\nFound.%s", ip);
      flag = 1;
      table[i].n++;

      strcpy(table[i].ips[table[i].n - 1], ip);
      // printf("\nupdated:%s",);
      break;
    }
  }

  return flag;
}
