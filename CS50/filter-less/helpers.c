#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Loop through image[i][j], take each elements color values, Average them out, and store that average value in to each color value
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round(((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0));
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //Create a maximum value so as to not surpass memory limitations
    const int maxVal = 255;
    //Loop through image and plug in corresponding values to a formula that spits back out a color value which will help resemle a sepia filter
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            //Determine if any values exceed maxval, and ensure it caps out at the max, otherwise store new result back into variable.
            if (sepiaRed > maxVal)
            {
                image[i][j].rgbtRed = maxVal;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            if (sepiaGreen > maxVal)
            {
                image[i][j].rgbtGreen = maxVal;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            if (sepiaBlue > maxVal)
            {
                image[i][j].rgbtBlue = maxVal;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        //either if is to obtain amount of steps necessary to swap values and create the reflection
        if (width % 2 == 0)
        {
            for (int j = 0; j < width / 2; j++)
            {
                RGBTRIPLE tmp;
                tmp = image[i][j];
                image[i][j] = image[i][(width - 1) - j];
                image[i][(width - 1) - j] = tmp;
            }
        }
        // if width is odd
        else
        {
            for (int j = 0; j < ((width - 1) / 2); j++)
            {
                RGBTRIPLE tmp;
                tmp = image[i][j];
                image[i][j] = image[i][(width - 1) - j];
                image[i][(width - 1) - j] = tmp;
            }
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Create 2d array to store copy of image
    RGBTRIPLE copy[height][width];
    //Loop through image and create an identical copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }



    //Loop through copy, use copy for math, and store result back into image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avgRed;
            int avgGreen;
            int avgBlue;
            //Upper Left corner, Blur formula
            if (i == 0 && j == 0)
            {
                avgRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i + 1][j].rgbtRed) / 4.0);
                avgGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen) / 4.0);
                avgBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue) / 4.0);
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //Upper right corner
            else if (i == 0 && j == width - 1)
            {
                avgRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed) / 4.0);
                avgGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen) / 4.0);
                avgBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue) / 4.0);
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //Bottom left corner
            else if (i == height - 1 && j == 0)
            {
                avgRed = round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed) / 4.0);
                avgGreen = round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen) / 4.0);
                avgBlue = round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue) / 4.0);
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //Bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                avgRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed) / 4.0);
                avgGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen) / 4.0);
                avgBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue) / 4.0);
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //Top side no corners
            else if (i == 0 && !(j == 0) && !(j == width - 1))
            {
                avgRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j -
                                1].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);
                avgGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i +
                                  1][j - 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
                avgBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j -
                                 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //Bottom side no corners
            else if (i == height - 1 && !(j == 0) && !(j == width - 1))
            {
                avgRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j +
                                1].rgbtRed + copy[i - 1][j - 1].rgbtRed) / 6.0);
                avgGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i -
                                  1][j + 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) / 6.0);
                avgBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j +
                                 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue) / 6.0);
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //Left side no corners
            else if (j == 0 && !(i == 0) && !(i == height - 1))
            {
                avgRed = round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j +
                                1].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);
                avgGreen = round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                                  copy[i][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
                avgBlue = round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j +
                                 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //Right side no corners
            else if (j == width - 1 && !(i == 0) && !(i == height - 1))
            {
                avgRed = round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j -
                                1].rgbtRed + copy[i + 1][j - 1].rgbtRed) / 6.0);
                avgGreen = round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i -
                                  1][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) / 6.0);
                avgBlue = round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j -
                                 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / 6.0);
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //Average all adjacent units colors, plus self, set all color variables to respective averages
            else if (!(i == 0) && !(i == height - 1) && !(j == 0) && !(j == width - 1))
            {
                avgRed = round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed +
                                copy[i + 1][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j -
                                        1].rgbtRed) / 9.0);
                avgGreen = round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                  copy[i + 1][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j -
                                          1].rgbtGreen) / 9.0);
                avgBlue = round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                 copy[i + 1][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j -
                                         1].rgbtBlue) / 9.0);
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
        }
    }
}
