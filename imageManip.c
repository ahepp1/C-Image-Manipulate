//Emerson Sullivan, Eric Bao, Alex Hepp, Jack Goldrick
//esulli26, ebao1, ahepp1, jgoldri5
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ppm_io.h"
#include "imageManip.h"
#define PI 3.14159265358979323846


/*
 *Invert each color (r, g, b) value by subtracting it from 255. Inverting again
 * will yield the original image.
 */
void Invert_Colors(Image *invert_img) {

  int array_size = invert_img->rows * invert_img->cols; //size of array

  for (int i = 0; i < array_size; i++) { //parse through array to invert colors
    (invert_img->data)[i].r = 255 - (invert_img->data)[i].r;
    (invert_img->data)[i].g = 255 - (invert_img->data)[i].g;
    (invert_img->data)[i].b = 255 - (invert_img->data)[i].b;
  }
  return;
}

/*
 * Using the NTSC standard conversion formula, each pixel has a value that
 * will turn it grayscale: intensity = 0.30*red + 0.59*green + 0.11*blue.
 * Intensity is assigned to all color channels of that pixel.
 */
void Grayscale_Convert(Image *grey_img) {

  int array_size = grey_img->rows * grey_img->cols; //size of array
  float intensity = 0;
  int red = 0;
  int green = 0;
  int blue = 0;
  unsigned char grey_rgb; //gray value assigned to each pixel

  for (int i = 0; i < array_size; i++) { //parse through array
    red = (grey_img->data)[i].r;
    green = (grey_img->data)[i].g;
    blue = (grey_img->data)[i].b;
    intensity = 0.30 * red + 0.59 * green + 0.11 * blue; //NTSC formula
    grey_rgb = (unsigned char) intensity; //finds grayscale value
    (grey_img->data)[i].r = grey_rgb;
    (grey_img->data)[i].g = grey_rgb;
    (grey_img->data)[i].b = grey_rgb;
  }
  return;
}


/* Takes in an image and swaps all the pixels in the image. Old values of green
 * become the new values for red, old values of blue become new values of green
 * and old values of red become new values of blue. Swaps pointers so is void.
 */

void Swap_Colors(Image *swap_img) {
  int num_rows = swap_img->rows;
  int num_cols = swap_img->cols;
  int ar_len = num_rows * num_cols; //length of array
  for (int i = 0; i < ar_len; i++) {
    char old_r = (swap_img->data)[i].r; //assign old rgb values to temp var.
    char old_g = (swap_img->data)[i].g;
    char old_b = (swap_img->data)[i].b;
    (swap_img->data)[i].r = old_g; //re-assigns rgb to designated temps
    (swap_img->data)[i].g = old_b;
    (swap_img->data)[i].b = old_r;
  }
}


/*
 * Takes an image and adds a value to each channel of the pixel. A positive
 * value will brighten the image, and a negative value will darken the image
 * Will need to saturate (no overflow or underflow beyond [0, 255] per
 * channel.
 */
 void Bright(Image *bright_img, float val) {
   int num_rows = bright_img->rows;
   int num_cols = bright_img->cols;
   int ar_len = num_rows * num_cols; //length of array of pixels
   for (int i = 0; i < ar_len; i++) {
     unsigned char r = (bright_img->data)[i].r; //assigns rgb to vars for
     unsigned char g = (bright_img->data)[i].g;// easier code reading
     unsigned char b = (bright_img->data)[i].b;
     if ((r + val) < 0 ) {
       (bright_img->data)[i].r = 0; //de-saturation

     }
     else if ((r + val) > 255) {
       (bright_img->data)[i].r = 255; //over-saturation
     }
     else {
       (bright_img->data)[i].r = r + val;

     }
     if ((g + val) < 0) {
       (bright_img->data)[i].g = 0; //de-saturation
     }
     else if ((g + val > 255)) {
       (bright_img->data)[i].g = 255; //over-saturation
     }
     else {
       (bright_img->data)[i].g = g + val;
     }
     if ((b + val) < 0) {
       (bright_img->data)[i].b = 0; //de-saturation
     }
     else if ((b + val) > 255) {
       (bright_img->data)[i].b = 255; //over-saturation
     }
     else {
       (bright_img->data)[i].b = b + val;
     }
   }
 }


/*
 * Takes in top left corner values and bottom right corner values to specify
 * the crop dimensions. Must allocate the correct amount of space for the
 * new pixel array.
 */
void Crop(Image *crop_img, int col_left, int row_top, int col_right, int row_bot) {

  int cols = 0;
  int temprow = 0;

  Pixel twodim[crop_img->rows][crop_img->cols];
  Pixel temp[crop_img->rows][crop_img->cols]; //temp 2D array to store data for the cropped image

  int count = 0;

  for (int i = 0; i < crop_img->rows; i++) {
    for (int j = 0; j < crop_img->cols; j++) {
      twodim[i][j] = (crop_img->data)[count++];
    }
  }

  int rows = 0;

  for (int i = col_left; i < col_right; i++) {
    for (int j = row_top; j < row_bot; j++) {
      temp[temprow++][cols] = twodim[j][i];
    }
    rows = temprow;
    temprow = 0;
    cols++;
  }

  Image * new_img = create_image(cols, rows); //malloc cropped image space

  count = 0;

  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      (new_img->data)[j * cols + i] = temp[j][i]; //creates "fake 2D" array
    }
  }
  //realloc data in the original img data for the cropped image dimensions
  free(crop_img->data);
  crop_img->data = NULL;
  crop_img->data = malloc(sizeof(Pixel*) * cols * rows);
  if (crop_img->data == NULL) {
    printf("Error, failed to allocate memory");
    exit(8);
  }
  crop_img->cols = cols;
  crop_img->rows = rows;
  for(int n = 0; n < cols * rows; n++) {


    (crop_img->data)[n] = (new_img->data)[n]; //match 1D to 1D "fake 2D" RA's
  }
  delete_image(new_img);
}

double Sqre(double num) { return num * num; }

int sizeSig (double sigma)  {
  int num = ceil(10 * sigma);
  if(num % 2 == 0)
    ++num;
  return num;
} //need


/*
*Get the Gaussian Matrix when sigma and size are inputted.
*/
double * gauss_matrix(double sigma, int size){
  double * gMat = malloc(sizeof(double) * size * size);
  if (gMat == NULL) {
  printf("Error, failed to allocate memory");
  exit(8);
  }
  int cent = size / 2;
  int row;
  int col;
  double g;
  int ub = cent;
  int lb = -cent;

    for(int dy = lb; dy < ub + 1; ++dy){

      row = cent + dy;

      for(int dx = lb; dx < ub + 1; ++dx) {
        g = ( 1.0 / ( 2.0 * PI * Sqre(sigma) ) ) * exp( -( Sqre(dx) + Sqre(dy) ) / (2.0 * Sqre(sigma)) );

        col = cent + dx;


        gMat[(row * size) + col] = g;
      }
    }
  return gMat;
}

/*
 * Blur a pixel in accordance with the pixels around it. We weigh the
 * importance of neighboring pixels according to a Gaussian distribution.
 */
Pixel blur_Pixel(Image * img, int row, int col, double * gMat, int size) {
  Pixel blurred;
  int center = size / 2;
  int dist_r_fc = (row - center);
  int dist_c_fc = (col - center);
  double normalize = 0;
  double sum_r = 0;
  double sum_b = 0;
  double sum_g = 0;
  double x;
  int loc_c;
  int loc_r;

  for(int i = 0; i < size; ++i) {
    loc_r = i + dist_r_fc;
    for(int j = 0; j < size; ++j) {
      loc_c = j + dist_c_fc;

      if(loc_r <  0){} else if(loc_c < 0){} else if(loc_r > img->rows - 1){} else if(loc_c > img->cols - 1){}
      else {
	       x = gMat[(i * size) + j];

	       sum_r += (img->data[((i + dist_r_fc) * (img->cols)) + (j + dist_c_fc)].r * x);
	       sum_g += (img->data[((i + dist_r_fc) * (img->cols)) + (j + dist_c_fc)].g * x);
	       sum_b += (img->data[((i + dist_r_fc) * (img->cols)) + (j + dist_c_fc)].b * x);
	       normalize += x;
      } //end if/else

    }//end inner loop

  }//end outer loop
  blurred.r = sum_r / normalize;
  blurred.g = sum_g / normalize;
  blurred.b = sum_b / normalize;

  return blurred;

}

/*
* Helper function to apply pixel blur to all pixels in an image in order to create
* the final blurred image.
*/
void Blur(Image *img, double sigma) {
  int size = sizeSig(sigma);
  double * gMat = gauss_matrix(sigma, size);
  //Image * blurry = create_image(img->cols, img->rows);
  int colNum = img->cols;
  int rowNum = img->rows;

  for(int i = 0; i < rowNum; ++i) {
      for(int j = 0; j < colNum; ++j) {
        img->data[(i * colNum) + j] = blur_Pixel(img, i, j, gMat, size);
      }
    }

    free(gMat);
    gMat = NULL;
}
