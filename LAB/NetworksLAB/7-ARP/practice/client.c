
int isValidMAC(char *mac)
{
    int dot = 0 ;
    for (int i = 0 ; mac[i] , i++)
    {
        if (mac[i]==":") dot++;
        else if ((isalpha(mac[i]) && mac[i]<'a' || mac[i]>'f') || !isdigit(mac[i] && !isalpha(mac[i])))
            return 0 ; 
    }

    if (dot != 5 ) return 0 ;

    
    return 1 ;
}