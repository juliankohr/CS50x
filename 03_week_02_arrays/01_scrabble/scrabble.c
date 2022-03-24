#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Declaration of function compute_score
int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// Definition of function compute_score
int compute_score(string word)
{
    // Setting n to zero (which will be the ASCII number relating to our chars)
    int n = 0;
    // Setting i to zero (helps us to go through each char of the word)
    int i = 0;
    // Setting the score to zero (will be incremented in relation to the points each letter gets in Scrabble)
    int score = 0;
    do
    {
        // Set the initial value of n to the char value as integer
        n = word[i];
        // If the value of n is relating to a lower letter subtract 32
        if (n >= 97 && n <= 122)
        {
            n -= 32;
        }
        // If n has the value of a capital letter subtract 65 to match array of POINTS
        if (n >= 65 && n <= 90)
        {
            score += POINTS[n - 65];
        }
        // Every other character will add zweo points to the score
        else
        {
            score += 0;
        }
        // Increment i by one
        i++;
    }
    // Do it, while n is NOT zero
    while (n != 0);
    // Return the score
    return score;
}
