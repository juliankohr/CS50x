// Including all libraries
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Declaring only_digits that will return false if teh coammnd- line argument will contain sth. else than numbers
bool only_digits(string s);
// Declaring a function that will rotate the characters, but nothing else
char rotate(char c, int n);

// Defining main function, taking command-line arguments
int main(int argc, string argv[])
{
    // If more arguments than 1 and less or equal 1 provided, the program will stop and output a usage note
    if (argc <= 1 || argc > 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // If one command-line argument is provided, make sure, its only digits
    else
    {
        bool digit = only_digits(argv[1]);
        // If not, return usage note
        if (digit == false)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        else
        {
            int key = atoi(argv[1]) % 26;
            string plaintext = get_string("plaintext: ");
            int string_length = strlen(plaintext);
            printf("ciphertext: ");
            for (int j = 0; j < string_length; j++)
            {
                printf("%c", rotate(plaintext[j], key));
            }
            printf("\n");
        }
    }
}

// Defining function only_digits, that takes a string as input and outputs a boolean
bool only_digits(string s)
{
    // Get length of string
    int length = strlen(s);
    // For every element of the string, make sure it's a digit. If so return true, if not, false
    for (int i = 0; i < length; i++)
    {
        int id = isdigit(s[i]);
        if (id == 0)
        {
            return false;
        }
    }
    return true;
}

// Defining function rotate, that takes chars and the key as int as inputs and outputs the  rotated chars
char rotate(char c, int n)
{
    // Check if char is in alphabet, so punctioations get returned without rotation
    if (isalpha(c) != 0)
    {
        // Convert char to its relating integer according to the ASCII table
        int given_char = (int)c;
        // Calculate new place in ASCII chart
        int rotation = given_char + n;
        // Check if its uppercase and set the value in relation to the uppercase chars in ASCII chart (so A with key 27 will turn to B and so on)
        if (isupper(c) != 0)
        {
            if (rotation > 90)
            {
                rotation -= 26;
                char rotated_char = rotation;
                return rotated_char;
            }
            else
            {
                char rotated_char = rotation;
                return rotated_char;
            }
        }
        else
        {
            // If its lowercase, set the value in relation to the lowercase chars in ASCII chart (so a with key 27 will turn to b and so on)
            if (rotation > 122)
            {
                rotation -= 26;
                char rotated_char = rotation;
                return rotated_char;
            }
            else
            {
                char rotated_char = rotation;
                return rotated_char;
            }
        }
    }
    // If char is not in the alphabet, return the char untouched
    else
    {
        return c;
    }
}