#include <stdio.h>
#include <cs50.h>

// initiate main function
int main(void)
{
    // ask the user for his/her name and store it in the variable name, which has the data type string
    string name = get_string("What's your name? ");
    // print "Hello" and the name of the user, which is stored in the variable name
    printf("Hello, %s!\n", name);
}
