#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct hammingCode
{
	char msg[255];
	int r;
}hc;

int find_r(int m)
{
	int r=0;
	while(pow(2,r)<m+r+1)
		r++;
	return r;
}

void reverseStr(char *str)
{
	int n=strlen(str);
	for (int i=0;i<n/2;i++)
	{
		char ch=str[i];
		str[i]=str[n-i-1];
		str[n-i-1]=ch;
	}
}

char* gen_enc_code(char *data,int r)
{
	int m=strlen(data),j=m-1;
	while(pow(2,r)<m+r+1)
		r++;
	char *msg=(char*)malloc(sizeof(char)*(m+r+1));
	msg[0]='-';
	for(int i=1;i<m+r+1;i++)
	{
		if((i&(i-1))==0)
			msg[i]='r';
		else
			msg[i]=data[j--];		
	}
	msg[m+r+1]='\0';
	return msg;
}

void find_msg(char *msg,int r)
{
	for(int skip=1;skip<pow(2,r);skip=skip*2)
	{
		int _1=0;
		for(int i=skip;msg[i];i=i+skip)
		{
				int temp=skip;
				while(temp-- && i<strlen(msg))
				{
					if(msg[i++]=='1')
						_1++;
				}
		}
		msg[skip]=(_1&1)?'1':'0';
	}
	//reverseStr(msg+1);
	//printf("%s\n",msg+1);
}

int check(char *msg,int r)
{
	char red[r];
	red[r]='\0';
	int i_r=0,pos=0;
	for(int skip=1;skip<pow(2,r);skip=skip*2)
	{
		int _1=0;
		for(int i=skip;msg[i];i=i+skip)
		{
				int temp=skip;
				while(temp-- && i<strlen(msg))
				{
					//printf("-%d-",i);
					if(msg[i++]=='1')
						_1++;					
				}
		}
		//printf("\n");
		red[i_r++]=(_1&1)?'1':'0';
	}
	//printf("\nred: %s\n",red);
	printf("red: ");
	for(int i=strlen(red)-1;i>=0;i--)
		printf("%c",red[i]);
	printf("\n");
	for(int i=0;red[i];i++)
		pos+=(red[i]-'0')*pow(2,i);
	return pos;
}

/*int main()
{
	char data[]="1010";
	int r=find_r(strlen(data));
	char *msg=gen_enc_code(data,r);
	printf("%s\n",msg+1);
	printf("%s\n",data);
	find_msg(msg,r);
	check(msg,r);
	return 0;
}*/
