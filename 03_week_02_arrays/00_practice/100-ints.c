#include <stdio.h>
#include <cs50.h>

int ints[0];
void fillarray(int z);

int main(void)
{
    int x = get_int("How many elements to generate in the array? ");
    fillarray(x);
    int y = 0;
    while (true)
    {
        y = get_int("From which index element do you want its value? ");
        if (y >= 0 && y < x)
        {

            printf("The value of element %i is %i\n", y, ints[y]);
        }
        else
        {
            printf("Invalid index element!\n");
            return 1;
        }
    }
}

void fillarray(int z)
{
    for (int i = 0; i < z; i++)
    {
        ints[i] = i + 1;
    }
}
