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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    // store kernels gx and gy in corresponding 2-dimensional arrays
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // create a buffer array to store temporary values
    RGBTRIPLE buffer[height][width];

    // for all horizontal and vertical pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // define RGB variables for each kernel
            int gxb = 0, gyb = 0, gxg = 0, gyg = 0, gxr = 0, gyr = 0;

            // for all adjacent pixels needed (3x3 box)
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    // check if pixel is inside the dimensions of the image
                    if (i + k >= 0 && i + k < height && j + l >= 0 && j + l < width)
                    {
                        // for all pixels inside the dimensions, extract value of every RGB channel and multiply with corresponding values of gx and gy kernels
                        gxb += image[i + k][j + l].rgbtBlue * gx[k + 1][l + 1];
                        gyb += image[i + k][j + l].rgbtBlue * gy[k + 1][l + 1];
                        gxg += image[i + k][j + l].rgbtGreen * gx[k + 1][l + 1];
                        gyg += image[i + k][j + l].rgbtGreen * gy[k + 1][l + 1];
                        gxr += image[i + k][j + l].rgbtRed * gx[k + 1][l + 1];
                        gyr += image[i + k][j + l].rgbtRed * gy[k + 1][l + 1];
                    }
                }
            }

            // define RGB channels combined by the provided sobel filter algorithm, add squared gx and gy values for each color and calculate square root lastly round value
            int sobelb = round(sqrt(pow(gxb, 2) + pow(gyb, 2)));
            int sobelg = round(sqrt(pow(gxg, 2) + pow(gyg, 2)));
            int sobelr = round(sqrt(pow(gxr, 2) + pow(gyr, 2)));

            // if some of the sobel values are higher than 255 set them to 255
            if (sobelb > 255)
            {
                sobelb = 255;
            }
            if (sobelg > 255)
            {
                sobelg = 255;
            }
            if (sobelr > 255)
            {
                sobelr = 255;
            }

            // set sobel values into the RGB channel of each pixel in the buffer
            buffer[i][j].rgbtBlue = sobelb;
            buffer[i][j].rgbtGreen = sobelg;
            buffer[i][j].rgbtRed = sobelr;
        }
    }

    // put every buffer value into the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = buffer[i][j].rgbtBlue;
            image[i][j].rgbtGreen = buffer[i][j].rgbtGreen;
            image[i][j].rgbtRed = buffer[i][j].rgbtRed;
        }
    }
    return;
}