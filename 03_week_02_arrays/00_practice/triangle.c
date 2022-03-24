#include <cs50.h>
#include <stdio.h>

bool valid_triangle(float x, float y, float z);

int main(void)
{
    float x = get_float("X: ");
    float y = get_float("Y: ");
    float z = get_float("Z: ");

    bool result = valid_triangle(x, y, z);

    printf("%s\n", result ? "valid triangle" : "invalid triangle");
}

bool valid_triangle(float x, float y, float z)
{
    if (x <= 0 || y <= 0 || z <= 0)
    {
        return false;
    }
    if ((x + y <= z) || (x + z <= y) || (y + z <= x))
    {
        return false;
    }
    return true;
}
