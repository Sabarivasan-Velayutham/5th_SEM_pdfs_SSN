
#include <stdio.h>

void decimalToBinary(int num)
{
    for (int i = 7; i >= 0; i--)
    {
        // calculate bitmask to check whether
        // ith bit of num is set or not
        int mask = (1 << i);

        // ith bit of num is set
        if (num & mask)
            printf("1");
        // ith bit of num is not set
        else
            printf("0");
    }
}

int main()
{
    int num = 255;
    decimalToBinary(num);
    return 0;
}
