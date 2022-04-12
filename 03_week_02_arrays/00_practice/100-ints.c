#include <stdio.h>
#include <cs50.h>

// create initial array
int ints[0];
// prtotype of function fillarray
void fillarray(int z);

// initiate main function
int main(void)
{
    // ask how many elements the array should have
    int x = get_int("How many elements to generate in the array? ");
    // feed function fillarray with input from user
    fillarray(x);
    // define variable y
    int y = 0;
    // initialize while loop
    while (true)
    {
        // ask user from which index element the value is needed
        y = get_int("From which index element do you want its value? ");
        // check if index element is valid
        if (y >= 0 && y < x)
        {
            // if valid, print the value inside the element
            printf("The value of element %i is %i\n", y, ints[y]);
        }
        else
        {
            // else print invalid message
            printf("Invalid index element!\n");
            return 1;
        }
    }
}

// define fillarray function
void fillarray(int z)
{
    // start for loop filling the requested amount of elements with the index number + 1, so value at index 0 will be 1 and so on
    for (int i = 0; i < z; i++)
    {
        ints[i] = i + 1;
    }
}
