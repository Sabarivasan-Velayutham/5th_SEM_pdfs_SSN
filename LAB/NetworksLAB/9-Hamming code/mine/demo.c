
#include<stdio.h>
#include<stdlib.h>

int main() {
	
	int i;
	
	int arrInt[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int  n = sizeof(arrInt) / sizeof(int);
	
	char *arrChar;
	arrChar = (char *) malloc (sizeof(char) * (n+1));

	for(i=0;i<n;++i)
		arrChar[i] = arrInt[i] + '0';

	arrChar[n] = '\0';
	printf("String: %s", arrChar);
	
}