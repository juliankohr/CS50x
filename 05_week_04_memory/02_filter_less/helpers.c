#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for all horizontal and vertical pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // determine the average amount of RGB channels to receive a float number
            float averagef = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            // round the float average to get an integer
            int averagei = (int)round(averagef);
            // set all RGB channels to the average to transform the pixels into grayscale
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = averagei;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // for all horizontal and vertical pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // store each RGB value in a variable
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // applying given algorithm on previous stored RGB variables
            float sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            float sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            float sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;

            // if any of the values exceeds 255, set it to 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // setting rounded RGB values into each pixel
            image[i][j].rgbtRed = (int)round(sepiaRed);
            image[i][j].rgbtGreen = (int)round(sepiaGreen);
            image[i][j].rgbtBlue = (int)round(sepiaBlue);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // for all horizontal and half of the vertical pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // use the pointer row to point on each vertical row of the picture
            RGBTRIPLE *row = image[i];

            do
            {
                // storing row at place j into the variable tmp
                RGBTRIPLE temp = row[j];
                // injecting the row value from the opposite into row at place j
                row[j] = row[width - 1 - j];
                // injecting the initial value of row at place j (stored in tmp) into the opposite row
                row[width - 1 - j] = temp;
            }
            while (0);
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a 2-dimensional buffer array in size of the image
    RGBTRIPLE buffer[height][width];

    // defining a counter variable with initial value 0
    float counter = 0.00;
    // define variables for each RGB channel with the initial value 0 (needed to calculate )
    int redtotal = 0;
    int bluetotal = 0;
    int greentotal = 0;

    // store the image in the buffer array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            buffer[i][j] = image[i][j];
        }
    }

    // for all horizontal and vertical pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // for all adjacent pixels needed for blurring (3x3 box)
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    // check if pixel is inside the dimensions of the image
                    if (i + k >= 0 && i + k < height && j + l >= 0 && j + l < width)
                    {
                        // store RGB values of each pixel inside the 3x3 box in corresponding RGB variables, defined previously
                        redtotal += image[i + k][j + l].rgbtRed;
                        greentotal += image[i + k][j + l].rgbtGreen;
                        bluetotal += image[i + k][j + l].rgbtBlue;
                        // incease counter by 1 for each pixel addad to the total variables of each RGB channel
                        counter += 1;
                    }
                }
            }

            // calculate average RGB values and store inside the buffer on intended place
            buffer[i][j].rgbtRed = round(redtotal / counter);
            buffer[i][j].rgbtGreen = round(greentotal / counter);
            buffer[i][j].rgbtBlue = round(bluetotal / counter);

            // resetting counter and RGB variables
            counter = 0;
            redtotal = 0;
            bluetotal = 0;
            greentotal = 0;
        }
    }

    // for all horizontal and vertical pixels
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            // store values from buffer arry in acrual image
            image[x][y] = buffer[x][y];
        }
    }
    return;
}
