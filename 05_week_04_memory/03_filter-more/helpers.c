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
            } while (0);
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxBlue = 0;
            int gyBlue = 0;
            int gxGreen = 0;
            int gyGreen = 0;
            int gxRed = 0;
            int gyRed = 0;

            for (int r = -1; r < 2; r++)
            {
                for (int c = -1; c < 2; c++)
                {
                    if (i + r < 0 || i + r > height - 1)
                    {
                        continue;
                    }
                    if (j + c < 0 || j + c > width - 1)
                    {
                        continue;
                    }

                    gxBlue += image[i + r][j + c].rgbtBlue * gx[r + 1][c + 1];
                    gyBlue += image[i + r][j + c].rgbtBlue * gy[r + 1][c + 1];
                    gxGreen += image[i + r][j + c].rgbtGreen * gx[r + 1][c + 1];
                    gyGreen += image[i + r][j + c].rgbtGreen * gy[r + 1][c + 1];
                    gxRed += image[i + r][j + c].rgbtRed * gx[r + 1][c + 1];
                    gyRed += image[i + r][j + c].rgbtRed * gy[r + 1][c + 1];
                }
            }

            int blue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));
            int green = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int red = round(sqrt(gxRed * gxRed + gyRed * gyRed));

            temp[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
            temp[i][j].rgbtGreen = (green > 255) ? 255 : green;
            temp[i][j].rgbtRed = (red > 255) ? 255 : red;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}
