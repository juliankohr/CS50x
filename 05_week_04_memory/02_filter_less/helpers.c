#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float averagef = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            int averagei = (int)round(averagef);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = averagei;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            float sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            float sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            float sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;

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

            image[i][j].rgbtRed = (int)round(sepiaRed);
            image[i][j].rgbtGreen = (int)round(sepiaGreen);
            image[i][j].rgbtBlue = (int)round(sepiaBlue);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE *row = image[i];

            do
            {
                RGBTRIPLE temp = row[j];
                row[j] = row[width - 1 - j];
                row[width - 1 - j] = temp;
            }
            while (0);
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imgbuffer[height][width]; // Create an RGBTRIPLE 2-D array to store modified pixels.

    float counter = 0.00;
    int redsum, bluesum, greensum;
    redsum = bluesum = greensum = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imgbuffer[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = -1; k <= 1; k++) // Iterate from top to bottom of nearby pixels
            {
                for (int l = -1; l <= 1; l++) // Iterate left to right of nearby pixels
                {
                    if (i + k >= 0 && i + k < height && j + l >= 0 && j + l < width) // check if pixel fits
                    {
                        redsum += image[i + k][j + l].rgbtRed;
                        greensum += image[i + k][j + l].rgbtGreen;
                        bluesum += image[i + k][j + l].rgbtBlue;
                        counter += 1;
                    }
                }
            }

            imgbuffer[i][j].rgbtRed = round(redsum / counter);
            imgbuffer[i][j].rgbtGreen = round(greensum / counter);
            imgbuffer[i][j].rgbtBlue = round(bluesum / counter);

            counter = 0;
            redsum = bluesum = greensum = 0;
        }
    }

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y] = imgbuffer[x][y];
        }
    }
    return;
}
