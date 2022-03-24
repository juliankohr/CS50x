#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool only_digits(string s);
int collatz(int n);

int main(int argc, string argv[])
{
    if (argc <= 1 || argc > 2)
    {
        printf("./collatz number\n");
        return 1;
    }
    else
    {
        if (only_digits(argv[1]) == false)
        {
            printf("./collatz number\n");
            return 1;
        }
        else
        {
            printf("Es wurden %i Schritte benötigt um auf 1 zu kommen.\n", collatz(atoi(argv[1])));
        }
    }
}

bool only_digits(string s)
{
    int length = strlen(s);
    for (int i = 0; i < length; i++)
    {
        if (isdigit(s[i]) == 0)
            return false;
    }
    return true;
}

int collatz(int n)
{
    if (n == 1)
        return 0;
    else if (n % 2 == 0)
        return 1 + collatz(n / 2);
    else
        return 1 + collatz(3 * n + 1);
}
