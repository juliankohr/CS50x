#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// prototype of functions only_alpha and cipher
bool only_alpha(string s, int l);
char cipher(char c, string k);
// create key array with 26 elements
char key[26];

// initiate main function
int main(int argc, string argv[])
{
    // if key is not provided, print usage and quit
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        // determine length of provided key
        int len = strlen(argv[1]);
        // if not 26 characters, print error message
        if (len != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else
        {
            // check if key contains only alphabetic characters
            bool alpha = only_alpha(argv[1], len);
            // if not, print error message
            if (alpha == false)
            {
                printf("Key must only contain alphabetic characters.\n");
                return 1;
            }
            // if key contains only alphabetic characters
            else
            {
                // create seen array with 26 elements setting 0 as value of each element
                int seen[26] = {0};
                // create offset variable with ASCII value of A
                int offset = 'A';
                // write every substitution char into key array and place it into seen array after subtracting the offset +1
                for (int j = 0; j < len; j++)
                {
                    key[j] = toupper(argv[1][j]);
                    seen[key[j] - offset]++;
                }
                // check for repeating characters, if so print error message
                for (int l = 0; l < 26; l++)
                {
                    if (seen[l] != 1)
                    {
                        printf("Key must not contain repeated characters.\n");
                        return 1;
                    }
                }
                // ask the user for text that should be ciphered
                string plain = get_string("plaintext: ");
                // determine the length of plain text
                int plain_length = strlen(plain);
                printf("ciphertext: ");
                // print ciphered text
                for (int m = 0; m < plain_length; m++)
                {
                    printf("%c", cipher(plain[m], key));
                }
                printf("\n");
            }
        }
    }
}

// define only_alpha function
bool only_alpha(string s, int l)
{
    // check if every character in the provided string is an alphabetical character
    for (int i = 0; i < l; i++)
    {
        int ia = isalpha(s[i]);
        if (ia == 0)
        {
            return false;
        }
    }
    return true;
}

// define cipher function
char cipher(char c, string k)
{
    // check if provided char is an alphabetical character
    if (isalpha(c) != 0)
    {
        // check if provided char is an upper case letter
        if (isupper(c) != 0)
        {
            // if char is alpha and upper, convert char in ASCII value and subtract the offset of "A"
            int ret = (int)c - (int)'A';
            // return substitution letter
            return k[ret];
        }
        else
        {
            // if char is alpha but not uppercase, subtract the offset of "a"
            int ret = (int)c - (int)'a';
            // add the offset of 32 to preserve small cahracters in ASCII table
            char sm_ret = (int)k[ret] + 32;
            // return substitution letter
            return sm_ret;
        }
    }
    // non-alphabetical characters will be returned as they are
    else
    {
        return c;
    }
}
