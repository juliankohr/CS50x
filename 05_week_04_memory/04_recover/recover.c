#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// setting uint8_t to BYTE and adding global variables
typedef uint8_t BYTE;
const int SIGNATURE_SIZE = 3;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // if command line arguments are not 2, print error message and quit
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // open file with name from cli argument
    FILE *input = fopen(argv[1], "r");
    // print error message ir NULL
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // defining a buffer for the blocks, creating a pointer named output pointing to NULL, creating name buffer for the file names, and a counter to increment file name by one.
    BYTE buffer[BLOCK_SIZE];
    FILE *output = NULL;
    char name_buffer[8];
    int file_counter = 0;

    // initiating loop while fread is true
    while (fread(buffer, BLOCK_SIZE, 1, input))
    {
        // if first 3.5 bytes are equal to the signature pattern
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // close output to start a new file
            if (output != 0)
            {
                fclose(output);
            }

            // define the file name, create a new file with certain name, increment file_counter
            sprintf(name_buffer, "%03i.jpg", file_counter);
            output = fopen(name_buffer, "w");
            file_counter++;
        }

        // if outout is not NULL, write file
        if (output != 0)
        {
            fwrite(buffer, BLOCK_SIZE, 1, output);
        }
    }

    // close input and output
    fclose(input);
    fclose(output);
    return 0;
}
