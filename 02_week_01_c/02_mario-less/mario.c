#include <cs50.h>
#include <stdio.h>

// initiating main function
int main(void)
{
    // set height as a variable that stores an integer value
    int height;

    // start a do-while loop to make sure that the user provides an input from 1 to 8
    do
    {
        // ask the user how high the pyramids should be
        height = get_int("Height: ");
        // make sure that the input is in the range of 1 and 8
    }
    while (height < 1 || height > 8);

    // start loop on which # gets printed based on the provided height input of user
    for (int i = 0; i < height; i++)
    {
        // print left spacing as long as j < height whereas j is depending on i so the number of spacings decrease while i and the number of # increase
        for (int j = i + 1; j < height; j++)
        {
            printf(" ");
        }
        // prints pyramid in dependency to i
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        // starts new line after each row
        printf("\n");
    }
}

