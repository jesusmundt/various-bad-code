#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

float limit(float value, float max);

// New typedef struct to create a copy of the pixels value
/*typedef struct
{
    int blue;
    int green;
    int red;
}
rgbvalues;*/

int getBulletPixelSize(int height, float bulletsize, float targetheight)
{

    float verticalres = height / targetheight;

    return bulletsize * verticalres;

}

void findHoles(int height, int width, RGBTRIPLE image[height][width], float bulletsize, float targetheight)
{
    int edgergbmin = 100;

    int maxpixels = pi * getBulletPixelSize(height, bulletsize, targetheight) * 10;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3 > edgergbmin)
            {
                for (int k = 0; k < maxpixels; k++)
                {
                    int l = i, m = j;

                    if ()

                }
            }
        }
    }

}

void printMatrix(int height, int width, RGBTRIPLE image[height][width])
{
    int sum = 0;

    for (int i = 950; i < 1020; i++)
    {
        for (int j = 1150; j < 1220; j++)
        {
            printf("%i, ", image[i][j].rgbtBlue);
            sum = sum + image[i][j].rgbtBlue;
        }

        printf("\n");
    }

    printf("%i \n", sum);
}


rgbvalues getBackground(int height, int width, RGBTRIPLE image[height][width])
{
    rgbvalues average, sum, averageB, sumB;

    averageB.blue = 0;
    averageB.green = 0;
    averageB.red = 0;

    sumB.blue = 0;
    sumB.green = 0;
    sumB.red = 0;

    for (int i = 0; i < (height/4); i++)
    {
        for (int j = 0; j < (width/4); j++)
        {

            sumB.blue = sumB.blue + image[i][j].rgbtBlue;
            sumB.green = sumB.green + image[i][j].rgbtGreen;
            sumB.red = sumB.red + image[i][j].rgbtRed;

        }

        averageB.blue = sumB.blue / (height*width/16);
        averageB.green = sumB.green / (height*width/16);
        averageB.red = sumB.red / (height*width/16);

    }

    for (int k = 0; k < (height); k++)
    {
        for (int l = 0; l < (width); l++)
        {
            average.blue = 0;
            average.green = 0;
            average.red = 0;

            sum.blue = 0;
            sum.green = 0;
            sum.red = 0;

            if ((image[k][l].rgbtBlue + image[k][l].rgbtGreen + image[k][l].rgbtRed) / 3 < (averageB.blue + averageB.green + averageB.red) * 0.8 / 3 || (image[k][l].rgbtBlue + image[k][l].rgbtGreen
                + image[k][l].rgbtRed) / 3 > (averageB.blue + averageB.green + averageB.red) * 1.6 / 3 )
            {
                for (int m = k; m < k + 30; m++)
                {
                    for (int n = l; n < l + 20; n++)
                    {

                    sum.blue = sum.blue + image[m][n].rgbtBlue;
                    sum.green = sum.green + image[m][n].rgbtGreen;
                    sum.red = sum.red + image[m][n].rgbtRed;

                    average.blue = sum.blue / 900;
                    average.green = sum.green / 900;
                    average.red = sum.red / 900;

                    }

                }

                /*if (abs(average.blue - (average.blue + average.green + average.red) / 3) > 5 || abs(average.green - (average.blue + average.green + average.red) / 3) > 5
                || abs(average.red - (average.blue + average.green + average.red) / 3) > 5)*/
                if ((average.blue + average.green + average.red) / 3 < (averageB.blue + averageB.green + averageB.red) * 0.1 / 3 || (average.blue + average.green + average.red)
                    / 3 > (averageB.blue + averageB.green + averageB.red) * 1.8 / 3)
                {
                    image[k][l].rgbtBlue = 0;
                    image[k][l].rgbtGreen = 0;
                    image[k][l].rgbtRed = 0;
                }

                else

                {
                    image[k][l].rgbtBlue = 255;
                    image[k][l].rgbtGreen = 255;
                    image[k][l].rgbtRed = 255;
                }

            }

            else

            {
                image[k][l].rgbtBlue = 0;
                image[k][l].rgbtGreen = 0;
                image[k][l].rgbtRed = 255;
            }
        }
    }

    return average;

}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average = 0;

    // Loop to calculate the average value and asign it to the new pixel value
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Variable to switch values
    int a = 0;

    // Loop to switch values from left to right and vice-versa, for half of the width value only
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < floor(width / 2.0); j++)
        {

            a = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = a;

            a = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = a;

            a = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = a;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE imagecopy[height][width])
{
    // Declaring an array to store the average for each RGB pixel and a new copy of the pixels array to store the new values
    float average[3];
    //rgbvalues imagecopy[height][width];

    // Loop to calculate the pixels averages
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Top left corner
            if (i == 0 && j == 0)
            {
                average[0] = (image[i][j].rgbtBlue + image[i +  1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 4.0;
                average[1] = (image[i][j].rgbtGreen + image[i +  1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 4.0;
                average[2] = (image[i][j].rgbtRed + image[i +  1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4.0;
            }

            // Bottom right corner
            else if (i == (height - 1) && j == (width - 1))
            {
                average[0] = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 4.0;
                average[1] = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 4.0;
                average[2] = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 4.0;
            }

            // Bottom left corner
            else if (i == (height - 1) && j == 0)
            {
                average[0] = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 4.0;
                average[1] = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 4.0;
                average[2] = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed) / 4.0;
            }

            // Top right corner
            else if (i == 0 && j == (width - 1))
            {
                average[0] = (image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 4.0;
                average[1] = (image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 4.0;
                average[2] = (image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 4.0;
            }

            // Top edge
            else if (i == 0 && j != 0 && j != (width - 1))
            {
                average[0] = (image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue
                              + image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6.0;
                average[1] = (image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen
                              + image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6.0;
                average[2] = (image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed
                              + image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6.0;
            }

            // Left edge
            else if (i != 0 && i != (height - 1) && j == 0)
            {
                average[0] = (image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue
                              + image[i + 1][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.0;
                average[1] = (image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen
                              + image[i + 1][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.0;
                average[2] = (image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed
                              + image[i + 1][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.0;
            }

            // Right edge
            else if (i != 0 && i != (height - 1) && j == (width - 1))
            {
                average[0] = (image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue
                              + image[i + 1][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 6.0;
                average[1] = (image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen
                              + image[i + 1][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 6.0;
                average[2] = (image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed
                              + image[i + 1][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 6.0;
            }

            // Bottom edge
            else if (i == (height - 1) && j != 0 && j != (width - 1))
            {
                average[0] = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue
                              + image[i - 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 6.0;
                average[1] = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen
                              + image[i - 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 6.0;
                average[2] = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed
                              + image[i - 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 6.0;
            }

            // All other interior pixels
            else
            {
                average[0] = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j - 1].rgbtBlue
                              + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue
                              + image[i + 1][j - 1].rgbtBlue) / 9.0;
                average[1] = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j - 1].rgbtGreen
                              + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen
                              + image[i + 1][j - 1].rgbtGreen) / 9.0;
                average[2] = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j - 1].rgbtRed
                              + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed
                              + image[i + 1][j - 1].rgbtRed) / 9.0;
            }

            // New pixels values into a copy of the pixels array to keep original values for next calculations
            imagecopy[i][j].rgbtBlue = round(average[0]);
            imagecopy[i][j].rgbtGreen = round(average[1]);
            imagecopy[i][j].rgbtRed = round(average[2]);
        }
    }

    // Loop to asign the new values to the final pixels array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = imagecopy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = imagecopy[i][j].rgbtGreen;
            image[i][j].rgbtRed = imagecopy[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE imagecopy[height][width])
{
    // Declaring 3x3 GX and GY arrays, two 3x3 arrays to store the total sum for every RGB pixel and a copy to store the new pixels values
    int GX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int GY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    float sum_gx[3], sum_gy[3];
    //rgbvalues imagecopy[height][width];

    // Loop to calculate new pixels values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Top left corner
            if (i == 0 && j == 0)
            {
                sum_gx[0] = image[i][j].rgbtBlue * GX[1][1] + image[i][j + 1].rgbtBlue * GX[1][2] + image[i + 1][j].rgbtBlue * GX[2][1]
                            + image[i + 1][j + 1].rgbtBlue * GX[2][2];
                sum_gx[1] = image[i][j].rgbtGreen * GX[1][1] + image[i][j + 1].rgbtGreen * GX[1][2] + image[i + 1][j].rgbtGreen * GX[2][1]
                            + image[i + 1][j + 1].rgbtGreen * GX[2][2];
                sum_gx[2] = image[i][j].rgbtRed * GX[1][1] + image[i][j + 1].rgbtRed * GX[1][2] + image[i + 1][j].rgbtRed * GX[2][1]
                            + image[i + 1][j + 1].rgbtRed * GX[2][2];

                sum_gy[0] = image[i][j].rgbtBlue * GY[1][1] + image[i][j + 1].rgbtBlue * GY[1][2] + image[i + 1][j].rgbtBlue * GY[2][1]
                            + image[i + 1][j + 1].rgbtBlue * GY[2][2];
                sum_gy[1] = image[i][j].rgbtGreen * GY[1][1] + image[i][j + 1].rgbtGreen * GY[1][2] + image[i + 1][j].rgbtGreen * GY[2][1]
                            + image[i + 1][j + 1].rgbtGreen * GY[2][2];
                sum_gy[2] = image[i][j].rgbtRed * GY[1][1] + image[i][j + 1].rgbtRed * GY[1][2] + image[i + 1][j].rgbtRed * GY[2][1]
                            + image[i + 1][j + 1].rgbtRed * GY[2][2];
            }

            // Bottom right corner
            else if (i == (height - 1) && j == (width - 1))
            {
                sum_gx[0] = image[i - 1][j - 1].rgbtBlue * GX[0][0] + image[i - 1][j].rgbtBlue * GX[0][1] + image[i][j - 1].rgbtBlue * GX[1][0]
                            + image[i][j].rgbtBlue * GX[1][1];
                sum_gx[1] = image[i - 1][j - 1].rgbtGreen * GX[0][0] + image[i - 1][j].rgbtGreen * GX[0][1] + image[i][j - 1].rgbtGreen * GX[1][0]
                            + image[i][j].rgbtGreen * GX[1][1];
                sum_gx[2] = image[i - 1][j - 1].rgbtRed * GX[0][0] + image[i - 1][j].rgbtRed * GX[0][1] + image[i][j - 1].rgbtRed * GX[1][0]
                            + image[i][j].rgbtRed * GX[1][1];

                sum_gy[0] = image[i - 1][j - 1].rgbtBlue * GY[0][0] + image[i - 1][j].rgbtBlue * GY[0][1] + image[i][j - 1].rgbtBlue * GY[1][0]
                            + image[i][j].rgbtBlue * GY[1][1];
                sum_gy[1] = image[i - 1][j - 1].rgbtGreen * GY[0][0] + image[i - 1][j].rgbtGreen * GY[0][1] + image[i][j - 1].rgbtGreen * GY[1][0]
                            + image[i][j].rgbtGreen * GY[1][1];
                sum_gy[2] = image[i - 1][j - 1].rgbtRed * GY[0][0] + image[i - 1][j].rgbtRed * GY[0][1] + image[i][j - 1].rgbtRed * GY[1][0]
                            + image[i][j].rgbtRed * GY[1][1];
            }

            // Bottom left corner
            else if (i == (height - 1) && j == 0)
            {
                sum_gx[0] = image[i - 1][j].rgbtBlue * GX[0][1] + image[i - 1][j + 1].rgbtBlue * GX[0][2] + image[i][j].rgbtBlue * GX[1][1]
                            + image[i][j + 1].rgbtBlue * GX[1][2];
                sum_gx[1] = image[i - 1][j].rgbtGreen * GX[0][1] + image[i - 1][j + 1].rgbtGreen * GX[0][2] + image[i][j].rgbtGreen * GX[1][1]
                            + image[i][j + 1].rgbtGreen * GX[1][2];
                sum_gx[2] = image[i - 1][j].rgbtRed * GX[0][1] + image[i - 1][j + 1].rgbtRed * GX[0][2] + image[i][j].rgbtRed * GX[1][1]
                            + image[i][j + 1].rgbtRed * GX[1][2];

                sum_gy[0] = image[i - 1][j].rgbtBlue * GY[0][1] + image[i - 1][j + 1].rgbtBlue * GY[0][2] + image[i][j].rgbtBlue * GY[1][1]
                            + image[i][j + 1].rgbtBlue * GY[1][2];
                sum_gy[1] = image[i - 1][j].rgbtGreen * GY[0][1] + image[i - 1][j + 1].rgbtGreen * GY[0][2] + image[i][j].rgbtGreen * GY[1][1]
                            + image[i][j + 1].rgbtGreen * GY[1][2];
                sum_gy[2] = image[i - 1][j].rgbtRed * GY[0][1] + image[i - 1][j + 1].rgbtRed * GY[0][2] + image[i][j].rgbtRed * GY[1][1]
                            + image[i][j + 1].rgbtRed * GY[1][2];
            }

            // Top right corner
            else if (i == 0 && j == (width - 1))
            {
                sum_gx[0] = image[i][j - 1].rgbtBlue * GX[1][0] + image[i][j].rgbtBlue * GX[1][1] + image[i + 1][j - 1].rgbtBlue * GX[2][0]
                            + image[i + 1][j].rgbtBlue * GX[2][1];
                sum_gx[1] = image[i][j - 1].rgbtGreen * GX[1][0] + image[i][j].rgbtGreen * GX[1][1] + image[i + 1][j - 1].rgbtGreen * GX[2][0]
                            + image[i + 1][j].rgbtGreen * GX[2][1];
                sum_gx[2] = image[i][j - 1].rgbtRed * GX[1][0] + image[i][j].rgbtRed * GX[1][1] + image[i + 1][j - 1].rgbtRed * GX[2][0]
                            + image[i + 1][j].rgbtRed * GX[2][1];

                sum_gy[0] = image[i][j - 1].rgbtBlue * GY[1][0] + image[i][j].rgbtBlue * GY[1][1] + image[i + 1][j - 1].rgbtBlue * GY[2][0]
                            + image[i + 1][j].rgbtBlue * GY[2][1];
                sum_gy[1] = image[i][j - 1].rgbtGreen * GY[1][0] + image[i][j].rgbtGreen * GY[1][1] + image[i + 1][j - 1].rgbtGreen * GY[2][0]
                            + image[i + 1][j].rgbtGreen * GY[2][1];
                sum_gy[2] = image[i][j - 1].rgbtRed * GY[1][0] + image[i][j].rgbtRed * GY[1][1] + image[i + 1][j - 1].rgbtRed * GY[2][0]
                            + image[i + 1][j].rgbtRed * GY[2][1];
            }

            // Top edge
            else if (i == 0 && j != 0 && j != (width - 1))
            {
                sum_gx[0] = image[i][j - 1].rgbtBlue * GX[1][0] + image[i][j].rgbtBlue * GX[1][1] + image[i][j + 1].rgbtBlue * GX[1][2]
                            + image[i + 1][j - 1].rgbtBlue * GX[2][0] + image[i + 1][j].rgbtBlue * GX[2][1] + image[i + 1][j + 1].rgbtBlue * GX[2][2];
                sum_gx[1] = image[i][j - 1].rgbtGreen * GX[1][0] + image[i][j].rgbtGreen * GX[1][1] + image[i][j + 1].rgbtGreen * GX[1][2]
                            + image[i + 1][j - 1].rgbtGreen * GX[2][0] + image[i + 1][j].rgbtGreen * GX[2][1] + image[i + 1][j + 1].rgbtGreen * GX[2][2];
                sum_gx[2] = image[i][j - 1].rgbtRed * GX[1][0] + image[i][j].rgbtRed * GX[1][1] + image[i][j + 1].rgbtRed * GX[1][2]
                            + image[i + 1][j - 1].rgbtRed * GX[2][0] + image[i + 1][j].rgbtRed * GX[2][1] + image[i + 1][j + 1].rgbtRed * GX[2][2];

                sum_gy[0] = image[i][j - 1].rgbtBlue * GY[1][0] + image[i][j].rgbtBlue * GY[1][1] + image[i][j + 1].rgbtBlue * GY[1][2]
                            + image[i + 1][j - 1].rgbtBlue * GY[2][0] + image[i + 1][j].rgbtBlue * GY[2][1] + image[i + 1][j + 1].rgbtBlue * GY[2][2];
                sum_gy[1] = image[i][j - 1].rgbtGreen * GY[1][0] + image[i][j].rgbtGreen * GY[1][1] + image[i][j + 1].rgbtGreen * GY[1][2]
                            + image[i + 1][j - 1].rgbtGreen * GY[2][0] + image[i + 1][j].rgbtGreen * GY[2][1] + image[i + 1][j + 1].rgbtGreen * GY[2][2];
                sum_gy[2] = image[i][j - 1].rgbtRed * GY[1][0] + image[i][j].rgbtRed * GY[1][1] + image[i][j + 1].rgbtRed * GY[1][2]
                            + image[i + 1][j - 1].rgbtRed * GY[2][0] + image[i + 1][j].rgbtRed * GY[2][1] + image[i + 1][j + 1].rgbtRed * GY[2][2];
            }

            // Left edge
            else if (i != 0 && i != (height - 1) && j == 0)
            {
                sum_gx[0] = image[i - 1][j].rgbtBlue * GX[0][1] + image[i - 1][j + 1].rgbtBlue * GX[0][2] + image[i][j].rgbtBlue * GX[1][1]
                            + image[i][j + 1].rgbtBlue * GX[1][2] + image[i + 1][j].rgbtBlue * GX[2][1] + image[i + 1][j + 1].rgbtBlue * GX[2][2];
                sum_gx[1] = image[i - 1][j].rgbtGreen * GX[0][1] + image[i - 1][j + 1].rgbtGreen * GX[0][2] + image[i][j].rgbtGreen * GX[1][1]
                            + image[i][j + 1].rgbtGreen * GX[1][2] + image[i + 1][j].rgbtGreen * GX[2][1] + image[i + 1][j + 1].rgbtGreen * GX[2][2];
                sum_gx[2] = image[i - 1][j].rgbtRed * GX[0][1] + image[i - 1][j + 1].rgbtRed * GX[0][2] + image[i][j].rgbtRed * GX[1][1]
                            + image[i][j + 1].rgbtRed * GX[1][2] + image[i + 1][j].rgbtRed * GX[2][1] + image[i + 1][j + 1].rgbtRed * GX[2][2];

                sum_gy[0] = image[i - 1][j].rgbtBlue * GY[0][1] + image[i - 1][j + 1].rgbtBlue * GY[0][2] + image[i][j].rgbtBlue * GY[1][1]
                            + image[i][j + 1].rgbtBlue * GY[1][2] + image[i + 1][j].rgbtBlue * GY[2][1] + image[i + 1][j + 1].rgbtBlue * GY[2][2];
                sum_gy[1] = image[i - 1][j].rgbtGreen * GY[0][1] + image[i - 1][j + 1].rgbtGreen * GY[0][2] + image[i][j].rgbtGreen * GY[1][1]
                            + image[i][j + 1].rgbtGreen * GY[1][2] + image[i + 1][j].rgbtGreen * GY[2][1] + image[i + 1][j + 1].rgbtGreen * GY[2][2];
                sum_gy[2] = image[i - 1][j].rgbtRed * GY[0][1] + image[i - 1][j + 1].rgbtRed * GY[0][2] + image[i][j].rgbtRed * GY[1][1]
                            + image[i][j + 1].rgbtRed * GY[1][2] + image[i + 1][j].rgbtRed * GY[2][1] + image[i + 1][j + 1].rgbtRed * GY[2][2];
            }

            // right edge
            else if (i != 0 && i != (height - 1) && j == (width - 1))
            {
                sum_gx[0] = image[i - 1][j - 1].rgbtBlue * GX[0][0] + image[i - 1][j].rgbtBlue * GX[0][1] + image[i][j - 1].rgbtBlue * GX[1][0]
                            + image[i][j].rgbtBlue * GX[1][1] + image[i + 1][j - 1].rgbtBlue * GX[2][0] + image[i + 1][j].rgbtBlue * GX[2][1];
                sum_gx[1] = image[i - 1][j - 1].rgbtGreen * GX[0][0] + image[i - 1][j].rgbtGreen * GX[0][1] + image[i][j - 1].rgbtGreen * GX[1][0]
                            + image[i][j].rgbtGreen * GX[1][1] + image[i + 1][j - 1].rgbtGreen * GX[2][0] + image[i + 1][j].rgbtGreen * GX[2][1];
                sum_gx[2] = image[i - 1][j - 1].rgbtRed * GX[0][0] + image[i - 1][j].rgbtRed * GX[0][1] + image[i][j - 1].rgbtRed * GX[1][0]
                            + image[i][j].rgbtRed * GX[1][1] + image[i + 1][j - 1].rgbtRed * GX[2][0] + image[i + 1][j].rgbtRed * GX[2][1];

                sum_gy[0] = image[i - 1][j - 1].rgbtBlue * GY[0][0] + image[i - 1][j].rgbtBlue * GY[0][1] + image[i][j - 1].rgbtBlue * GY[1][0]
                            + image[i][j].rgbtBlue * GY[1][1] + image[i + 1][j - 1].rgbtBlue * GY[2][0] + image[i + 1][j].rgbtBlue * GY[2][1];
                sum_gy[1] = image[i - 1][j - 1].rgbtGreen * GY[0][0] + image[i - 1][j].rgbtGreen * GY[0][1] + image[i][j - 1].rgbtGreen * GY[1][0]
                            + image[i][j].rgbtGreen * GY[1][1] + image[i + 1][j - 1].rgbtGreen * GY[2][0] + image[i + 1][j].rgbtGreen * GY[2][1];
                sum_gy[2] = image[i - 1][j - 1].rgbtRed * GY[0][0] + image[i - 1][j].rgbtRed * GY[0][1] + image[i][j - 1].rgbtRed * GY[1][0]
                            + image[i][j].rgbtRed * GY[1][1] + image[i + 1][j - 1].rgbtRed * GY[2][0] + image[i + 1][j].rgbtRed * GY[2][1];
            }

            // Bottom edge
            else if (i == (height - 1) && j != 0 && j != (width - 1))
            {
                sum_gx[0] = image[i - 1][j - 1].rgbtBlue * GX[0][0] + image[i - 1][j].rgbtBlue * GX[0][1] + image[i - 1][j + 1].rgbtBlue * GX[0][2]
                            + image[i][j - 1].rgbtBlue * GX[1][0] + image[i][j].rgbtBlue * GX[1][1] + image[i][j + 1].rgbtBlue * GX[1][2];
                sum_gx[1] = image[i - 1][j - 1].rgbtGreen * GX[0][0] + image[i - 1][j].rgbtGreen * GX[0][1] + image[i - 1][j + 1].rgbtGreen *
                            GX[0][2] + image[i][j - 1].rgbtGreen * GX[1][0] + image[i][j].rgbtGreen * GX[1][1] + image[i][j + 1].rgbtGreen *
                            GX[1][2];
                sum_gx[2] = image[i - 1][j - 1].rgbtRed * GX[0][0] + image[i - 1][j].rgbtRed * GX[0][1] + image[i - 1][j + 1].rgbtRed * GX[0][2]
                            + image[i][j - 1].rgbtRed * GX[1][0] + image[i][j].rgbtRed * GX[1][1] + image[i][j + 1].rgbtRed * GX[1][2];

                sum_gy[0] = image[i - 1][j - 1].rgbtBlue * GY[0][0] + image[i - 1][j].rgbtBlue * GY[0][1] + image[i - 1][j + 1].rgbtBlue * GY[0][2]
                            + image[i][j - 1].rgbtBlue * GY[1][0] + image[i][j].rgbtBlue * GY[1][1] + image[i][j + 1].rgbtBlue * GY[1][2];
                sum_gy[1] = image[i - 1][j - 1].rgbtGreen * GY[0][0] + image[i - 1][j].rgbtGreen * GY[0][1] + image[i - 1][j + 1].rgbtGreen *
                            GY[0][2] + image[i][j - 1].rgbtGreen * GY[1][0] + image[i][j].rgbtGreen * GY[1][1] + image[i][j + 1].rgbtGreen *
                            GY[1][2];
                sum_gy[2] = image[i - 1][j - 1].rgbtRed * GY[0][0] + image[i - 1][j].rgbtRed * GY[0][1] + image[i - 1][j + 1].rgbtRed * GY[0][2]
                            + image[i][j - 1].rgbtRed * GY[1][0] + image[i][j].rgbtRed * GY[1][1] + image[i][j + 1].rgbtRed * GY[1][2];
            }

            // All other interior pixels
            else
            {
                sum_gx[0] = image[i - 1][j - 1].rgbtBlue * GX[0][0] + image[i - 1][j].rgbtBlue * GX[0][1] + image[i - 1][j + 1].rgbtBlue * GX[0][2]
                            + image[i][j - 1].rgbtBlue * GX[1][0] + image[i][j].rgbtBlue * GX[1][1] + image[i][j + 1].rgbtBlue * GX[1][2]
                            + image[i + 1][j - 1].rgbtBlue * GX[2][0] + image[i + 1][j].rgbtBlue * GX[2][1] + image[i + 1][j + 1].rgbtBlue * GX[2][2];
                sum_gx[1] = image[i - 1][j - 1].rgbtGreen * GX[0][0] + image[i - 1][j].rgbtGreen * GX[0][1] + image[i - 1][j + 1].rgbtGreen *
                            GX[0][2] + image[i][j - 1].rgbtGreen * GX[1][0] + image[i][j].rgbtGreen * GX[1][1] + image[i][j + 1].rgbtGreen * GX[1][2]
                            + image[i + 1][j - 1].rgbtGreen * GX[2][0] + image[i + 1][j].rgbtGreen * GX[2][1] + image[i + 1][j + 1].rgbtGreen *
                            GX[2][2];
                sum_gx[2] = image[i - 1][j - 1].rgbtRed * GX[0][0] + image[i - 1][j].rgbtRed * GX[0][1] + image[i - 1][j + 1].rgbtRed * GX[0][2]
                            + image[i][j - 1].rgbtRed * GX[1][0] + image[i][j].rgbtRed * GX[1][1] + image[i][j + 1].rgbtRed * GX[1][2]
                            + image[i + 1][j - 1].rgbtRed * GX[2][0] + image[i + 1][j].rgbtRed * GX[2][1] + image[i + 1][j + 1].rgbtRed * GX[2][2];

                sum_gy[0] = image[i - 1][j - 1].rgbtBlue * GY[0][0] + image[i - 1][j].rgbtBlue * GY[0][1] + image[i - 1][j + 1].rgbtBlue * GY[0][2]
                            + image[i][j - 1].rgbtBlue * GY[1][0] + image[i][j].rgbtBlue * GY[1][1] + image[i][j + 1].rgbtBlue * GY[1][2]
                            + image[i + 1][j - 1].rgbtBlue * GY[2][0] + image[i + 1][j].rgbtBlue * GY[2][1] + image[i + 1][j + 1].rgbtBlue * GY[2][2];
                sum_gy[1] = image[i - 1][j - 1].rgbtGreen * GY[0][0] + image[i - 1][j].rgbtGreen * GY[0][1] + image[i - 1][j + 1].rgbtGreen *
                            GY[0][2] + image[i][j - 1].rgbtGreen * GY[1][0] + image[i][j].rgbtGreen * GY[1][1] + image[i][j + 1].rgbtGreen * GY[1][2]
                            + image[i + 1][j - 1].rgbtGreen * GY[2][0] + image[i + 1][j].rgbtGreen * GY[2][1] + image[i + 1][j + 1].rgbtGreen *
                            GY[2][2];
                sum_gy[2] = image[i - 1][j - 1].rgbtRed * GY[0][0] + image[i - 1][j].rgbtRed * GY[0][1] + image[i - 1][j + 1].rgbtRed * GY[0][2]
                            + image[i][j - 1].rgbtRed * GY[1][0] + image[i][j].rgbtRed * GY[1][1] + image[i][j + 1].rgbtRed * GY[1][2]
                            + image[i + 1][j - 1].rgbtRed * GY[2][0] + image[i + 1][j].rgbtRed * GY[2][1] + image[i + 1][j + 1].rgbtRed * GY[2][2];
            }

            // Calculate the final pixel value into a copy of the pixel array to keep oringal pixel values for next calculations
            imagecopy[i][j].rgbtBlue = round(limit(sqrt(pow(sum_gx[0], 2) + pow(sum_gy[0], 2)), 255));
            imagecopy[i][j].rgbtGreen = round(limit(sqrt(pow(sum_gx[1], 2) + pow(sum_gy[1], 2)), 255));
            imagecopy[i][j].rgbtRed = round(limit(sqrt(pow(sum_gx[2], 2) + pow(sum_gy[2], 2)), 255));
        }
    }

    // Loop to asign copied pixel value to the final pixel value
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = imagecopy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = imagecopy[i][j].rgbtGreen;
            image[i][j].rgbtRed = imagecopy[i][j].rgbtRed;
        }
    }

    return;
}

// Function to limit pixels value to max
float limit(float value, float max)
{
    if (value > max)
    {
        return max;
    }

    else
    {
        return value;
    }
}
