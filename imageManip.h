//Emerson Sullivan, Eric Bao, Alex Hepp, Jack Goldrick
//esulli26, ebao1, ahepp1, jgoldri5

#ifndef IMAGEMANIP_H
#define IMAGEMANIP_H

//#include "ppm_io.h"
#include <math.h>


/*
 *Invert each color (r, g, b) value by subtracting it from 255. Inverting again
 * will yield the original image.
 */
void Invert_Colors(Image *invert_img);


/*
 * Using the NTSC standard conversion formula, each pixel has a value that
 * will turn it grayscale: intensity = 0.30*red + 0.59*green + 0.11*blue.
 * Intensity is assigned to all color channels of that pixel.
 */
void Grayscale_Convert(Image *grey_img);


/* Takes in an image and swaps all the pixels in the image. Old values of green
 * become the new values for red, old values of blue become new values of green
 * and old values of red become new values of blue. Swaps pointers so is void.
 */
void Swap_Colors(Image *swap_img);


/*
 * Takes an image and adds a value to each channel of the pixel. A positive
 * value will brighten the image, and a negative value will darken the image
 * Will need to saturate (no overflow or underflow beyond [0, 255] per
 * channel.
 */
void Bright(Image *bright_img, float value);


/*
 * Takes in top left corner values and bottom right corner values to specify
 * the crop dimensions. Must allocate the correct amount of space for the
 * new pixel array.
 */
void Crop(Image *crop_img, int col_right, int row_top, int col_left, int row_bot);


/*
* Returns the square of two numbers.
*/
double Sqre(double num);


/*
* Finds the upper value of the required size of the sigma matrix.
*/
int sizeSig (double sigma);


/*
*Get the Gaussian Matrix when sigma and size are inputted.
*/
double * gauss_matrix(double sigma, int size); //need


/*
 * Blur a pixel in accordance with the pixels around it. We weigh the
 * importance of neighboring pixels according to a Gaussian distribution.
 */
Pixel blur_Pixel(Image * im, int row, int col, double * gMat, int size); //need


/*
* Helper function to apply pixel blur to all pixels in an image in order to create
* the final blurred image.
*/
void Blur(Image *img, double sigma);

#endif
