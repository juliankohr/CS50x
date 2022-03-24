#include <cs50.h>
#include <stdio.h>
#include <math.h>

// Declare a function count that takes a text string, an array results with integers and outputs void (nothing)
void count(string text, int results[]);
// Declare a function cl_index that takes an array results with integers
int cl_index(int results[]);

// Main function
int main(void)
{
    // Promt user for text input
    string text = get_string("Text: ");
    // Create an array with three elements
    int results[3];
    // Call function count with input text string and results array
    count(text, results);
    // Create integer variable called grade which equals the return value of function cl_index
    int grade = cl_index(results);
    // If grade is smaller than 1 print the following
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    // Else if grade is higher or equal to 16 print the following
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    // In all other cases print the following
    else
    {
        printf("Grade %i\n", grade);
    }
}

// Define function count
void count(string text, int results[])
{
    // Define local variables
    int letter_count = 0;
    int word_count = 1;
    int sentence_count = 0;
    int n;
    int i = 0;
    // Do while n != zero. n will have the ASCII mapped decimal value of each char
    do
    {
        // Go through each character
        n = text[i];
        // If value of character equals a letter, increment the letter count by 1
        if ((n >= 65 && n <= 90) || (n >= 97 && n <= 122))
        {
            letter_count++;
        }
        // If n equals 32 (Space), increment the word count by 1
        if (n == 32)
        {
            word_count++;
        }
        // If n equals the value for period, exclamation- or questionmark, increment the sentence count by 1
        if (n == 33 || n == 46 || n == 63)
        {
            sentence_count++;
        }
        // Increment i to get the value of the next character
        i++;
    }
    // Do this while n != 0 (which will indicate the end of the strings char array)
    while (n != 0);
    // Save the results in the results array created in the main function.
    results[0] = letter_count;
    results[1] = word_count;
    results[2] = sentence_count;
}

// Define function cl_index
int cl_index(int results[])
{
    // Define all local variables as floats
    float index;
    // Calculate letters per 100 words
    float letters_p100 = (((float)results[0] / (float)results[1]) * 100);
    // Calculate sentences per 100 words
    float sentences_p100 = (((float)results[2] / (float)results[1]) * 100);
    // Calculate the Coleman-Liau index
    index = (0.0588 * letters_p100) - (0.296 * sentences_p100) - 15.8;
    // Return the rounded value of that index
    return round(index);
}
