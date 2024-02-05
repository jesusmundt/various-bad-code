#include "bmp.h"

typedef struct
{
    int blue;
    int green;
    int red;
}
rgbvalues;

// Calculate the target average background color of the 5% of the target
rgbvalues getBackground(int height, int width, RGBTRIPLE image[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE imagecopy[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE imagecopy[height][width]);

