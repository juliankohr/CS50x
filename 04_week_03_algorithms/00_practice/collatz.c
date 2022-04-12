#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// prototype of functions only_digits and collatz
bool only_digits(string s);
int collatz(int n);

// initialize main function
int main(int argc, string argv[])
{
    // if cli is not 2, print usage information
    if (argc != 2)
    {
        printf("./collatz number\n");
        return 1;
    }
    else
    {
        // check if provided number is contains only digits
        if (only_digits(argv[1]) == false)
        {
            // if not only digits print usage information
            printf("./collatz number\n");
            return 1;
        }
        else
        {
            // in any other case print how many steps were needed to get to 1, by using the collatz function
            printf("Es wurden %i Schritte benötigt um auf 1 zu kommen.\n", collatz(atoi(argv[1])));
        }
    }
}

// define only_digits function
bool only_digits(string s)
{
    // determine the length of string
    int length = strlen(s);
    // for every character of string, check if it is a digit
    for (int i = 0; i < length; i++)
    {
        // if char is not a digit, return false
        if (isdigit(s[i]) == 0)
            return false;
    }
    // if string only contains digit, return true
    return true;
}

// define collatz function
int collatz(int n)
{
    // if number is 1, return 0
    if (n == 1)
        return 0;
    // if number is a even number, divide number by 2 and put it in the recursion of the function
    else if (n % 2 == 0)
        return 1 + collatz(n / 2);
    // if number is odd, multiply by 3 and add 1 and put it in the recursion of the function
    else
        return 1 + collatz(3 * n + 1);
}
