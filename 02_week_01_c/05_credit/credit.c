#include <cs50.h>
#include <stdio.h>

// initializing functions
long get_cardnumber(void);
int calc_length(long cardnumber);
bool calc_checksum(long cardnumber);
int calc_startdigits(long cardnumber, int length);
string determine_validity(bool checksum, int length, int startdigits);

// initialzing main function
int main(void)
{
    long cardnumber = get_cardnumber();
    int length = calc_length(cardnumber);
    bool checksum = calc_checksum(cardnumber);
    int startdigits = calc_startdigits(cardnumber, length);
    string validation = determine_validity(checksum, length, startdigits);
    printf("%s\n", validation);
}

// ask for credit card number
long get_cardnumber(void)
{
    long number = get_long("Number: ");
    return number;
}

// calculate length of credit ccard number
int calc_length(long cardnumber)
{
    // set counter to 0
    int count = 0;
    do
    {
        // for everytime the function is able to divide the credit card number by 10 increase the counter by 1
        cardnumber /= 10;
        count++;
    }
    while (cardnumber > 0);
    return count;
}

// calculate the checksum
bool calc_checksum(long cardnumber)
{
    // eod = every other digit, nmd = non multiplied digit
    int checksum_eod = 0;
    int checksum_nmd = 0;
    long cardnumber_eod = cardnumber / 10;
    long cardnumber_nmd = cardnumber;
    while (cardnumber_eod > 0)
    {
        int eod = cardnumber_eod % 10;
        int mult_eod = eod * 2;
        cardnumber_eod /= 100;

        while (mult_eod > 0)
        {
            int eod_digit = mult_eod % 10;
            checksum_eod = checksum_eod + eod_digit;
            mult_eod = mult_eod / 10;
        }
    }
    while (cardnumber_nmd > 0)
    {
        int nmd = cardnumber_nmd % 10;
        checksum_nmd += nmd;
        cardnumber_nmd /= 100;
    }
    int checksum = checksum_eod + checksum_nmd;
    int mod_checksum = checksum % 10;
    if (mod_checksum == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// calculate the to starting digits based on the length of the provided number
int calc_startdigits(long cardnumber, int length)
{
    for (int i = 2; i < length; i++)
    {
        cardnumber /= 10;
    }
    int startdigits = cardnumber;
    return startdigits;
}

// determine the validity
string determine_validity(bool checksum, int length, int startdigits)
{
    string validity = 0;
    // check if conditions apply for AMEX
    if (checksum == true && length == 15 && (startdigits == 34 || startdigits == 37))
    {
        validity = "AMEX";
    }
    // check if conditions apply for MASTERCARD
    else if (checksum == true && length == 16 && (startdigits >= 51 && startdigits <= 55))
    {
        validity = "MASTERCARD";
    }
    // check if conditions apply for VISA
    else if (checksum == true && (length == 13 || length == 16) && (startdigits >= 40 && startdigits <= 49))
    {
        validity = "VISA";
    }
    // else return INVALID
    else
    {
        validity = "INVALID";
    }
    return validity;
}

