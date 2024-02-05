#include "helpers.h"
#include <math.h>

float limit(float value, float max);

// New typedef struct to create a copy of the pixels value
/*typedef struct
{
    int blue;
    int green;
    int red;
}
rgbvalues;*/


rgbvalues getBackground(int height, int width, RGBTRIPLE image[height][width])
{
    rgbvalues average, sum;

    average.blue = 0;
    average.green = 0;
    average.red = 0;

    sum.blue = 0;
    sum.green = 0;
    sum.red = 0;

    /*for (int i = 0; i < (height/3); i++)
    {
        for (int j = 0; j < (width/3); j++)
        {

            sum.blue = sum.blue + image[i][j].rgbtBlue;
            sum.green = sum.green + image[i][j].rgbtGreen;
            sum.red = sum.red + image[i][j].rgbtRed;

        }

        average.blue = sum.blue / (height*width/9);
        average.green = sum.green / (height*width/9);
        average.red = sum.red / (height*width/9);

    }*/

     for (int k = 0; k < (height); k++)
    {
        for (int l = 0; l < (width); l++)
        {

            if ((image[k][l].rgbtBlue + image[k][l].rgbtGreen + image[k][l].rgbtRed) / 3 < 140 || (image[k][l].rgbtBlue + image[k][l].rgbtGreen + image[k][l].rgbtRed) / 3 > 170 )
            {
                for (int m = k; m < k + 20; m++)
                {
                    for (int n = l; n < l + 20; n++)

                    sum.blue = sum.blue + image[m][n].rgbtBlue;
                    sum.green = sum.green + image[m][n].rgbtGreen;
                    sum.red = sum.red + image[m][n].rgbtRed;

                    average.blue = sum.blue / 

                }

            }

            image[k][l].rgbtBlue = average.blue;
            image[k][l].rgbtGreen = average.green;
            image[k][l].rgbtRed = average.red;

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
