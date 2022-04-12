#include <cs50.h>
#include <stdio.h>

// prototype of function valid_triangle
bool valid_triangle(float x, float y, float z);

// initiate main function
int main(void)
{
    // ask for lenghts of side x, y and z
    float x = get_float("X: ");
    float y = get_float("Y: ");
    float z = get_float("Z: ");

    // feed function valid_triangle with user input and store the result (true || false) in boolean variable result
    bool result = valid_triangle(x, y, z);

    // if valid_triangle returns true print valid triangle, if false print invalid traingle
    printf("%s\n", result ? "valid triangle" : "invalid triangle");
}

// define valid_triangle function
bool valid_triangle(float x, float y, float z)
{
    // if any of the inputs is smaller or equal 0 return false
    if (x <= 0 || y <= 0 || z <= 0)
    {
        return false;
    }
    // if any combinations of the lengths is smaller or equal to another length, return false
    if ((x + y <= z) || (x + z <= y) || (y + z <= x))
    {
        return false;
    }
    // else return true
    return true;
}
