#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool only_alpha(string s, int l);
char cipher(char c, string k);
char key[26];

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        int len = strlen(argv[1]);
        if (len != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else
        {
            bool alpha = only_alpha(argv[1], len);
            if (alpha == false)
            {
                printf("Key must only contain alphabetic characters.\n");
                return 1;
            }
            else
            {
                int seen[26] = {0};
                int offset = 'A';
                for (int j = 0; j < len; j++)
                {
                    key[j] = toupper(argv[1][j]);
                    seen[key[j] - offset]++;
                }
                for (int l = 0; l < 26; l++)
                {
                    if (seen[l] != 1)
                    {
                        printf("Key must not contain repeated characters.\n");
                        return 1;
                    }
                }
                string plain = get_string("plaintext: ");
                int plain_length = strlen(plain);
                printf("ciphertext: ");
                for (int m = 0; m < plain_length; m++)
                {
                    printf("%c", cipher(plain[m], key));
                }
                printf("\n");
            }
        }
    }
}

bool only_alpha(string s, int l)
{
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

char cipher(char c, string k)
{
    if (isalpha(c) != 0)
    {
        if (isupper(c) != 0)
        {
            int ret = (int)c - (int)'A';
            return k[ret];
        }
        else
        {
            int ret = (int)c - (int)'a';
            char sm_ret = (int)k[ret] + 32;
            return sm_ret;
        }
    }
    else
    {
        return c;
    }
}