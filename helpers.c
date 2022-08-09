#include "helpers.h"
#include <math.h>
#include <cs50.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE average;
    float average_nr;
    for (int i =0 ; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            float Red = image[i][j].rgbtRed;
            float Blue = image[i][j].rgbtBlue;
            float Green = image[i][j].rgbtGreen;
            average = round((Red + Blue + Green) / 3);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image [i][j] = image [i][width - j - 1];
            image [i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image [i][j];
        }
    }
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            float counter = 0.00;
            int sumR, sumB, sumG;
            sumR = sumB = sumG = 0;
            for (int x = -1; x < 2 ; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentX = i + x;
                    int currentY = j + y;
                    if (currentX < 0 || currentX > (height-1) || currentY < 0 || currentY > (width-1))
                    {
                        continue;
                    }
                    sumR = sumR + image[currentX][currentY].rgbtRed;
                    sumB = sumB + image[currentX][currentY].rgbtBlue;
                    sumG = sumG + image[currentX][currentY].rgbtGreen;
                    counter++;
                }
                temp[i][j].rgbtRed = round(sumR /counter);
                temp[i][j].rgbtBlue = round(sumB /counter);
                temp[i][j].rgbtGreen = round(sumG /counter);
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0 ; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {- 1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int i = 0; i < height ; i++)
    {

        for (int j = 0; j < width ; j++)
        {
            int redX = 0;
            int greenX = 0;
            int blueX = 0;
            int redY = 0;
            int greenY = 0;
            int blueY = 0;

            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    if (i - 1 + x < 0 || i - 1 + x > height - 1 || j - 1 + y < 0 || j - 1 + y > width - 1)
                    {
                        continue;
                    }

                    redX = redX + (image[i - 1 + x][j - 1 + y].rgbtRed * Gx[x][y]);
                    blueX = blueX + (image[i - 1 + x][j - 1 + y].rgbtBlue * Gx[x][y]);
                    greenX = greenX + (image[i -1 + x][j - 1 + y].rgbtGreen * Gx[x][y]);
                    redY = redY + (image[i - 1 + x][j - 1 + y].rgbtRed * Gy[x][y]);
                    blueY = blueY + (image[i - 1 + x][j - 1 + y].rgbtBlue * Gy[x][y]);
                    greenY = greenY + (image[i -1 + x][j -1 + y].rgbtGreen * Gy[x][y]);
                }
            }
            int red = round(sqrt((redX*redX) + (redY*redY)));
            int green = round(sqrt((greenX*greenX) + (greenY*greenY)));
            int blue = round(sqrt((blueX*blueX) + (blueY*blueY)));
            if (red > 255)
            {
                red = 255;
            }
            else if (green > 255)
            {
                green = 255;
            }
            else if (blue > 255)
            {
                blue = 255;
            }
            temp[i][j].rgbtRed = red;
            temp[i][j].rgbtBlue = blue;
            temp[i][j].rgbtGreen = green;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
    return;
}
