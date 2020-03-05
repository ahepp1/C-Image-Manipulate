//Emerson Sullivan, Eric Bao, Alex Hepp, Jack Goldrick
//esulli26, ebao1, ahepp1, jgoldri5


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ppm_io.h"
#include "imageManip.h"


/*
* Wrapper funtion to handle all input and output. When given an integer
* representing the number of command line arguments passed, and an array of
* the strings passed, it will decide which of the manipulation functions to
* run and write the new image. If no issues are encountered, main will return 0
* after calling this function.
*/
void wrapper(int argsc, char* argsv[]) {


  //Check to make sure at a minimum the input file and output file are given.
  if (argsc < 3) {
    printf("Please supply an input .ppm file, an output .ppm destination and an image operation.\n");
    exit(1);
  }
  //Creates the pointer to the input file and checks to make sure it opened to read properly.
  FILE *input = fopen(argsv[1], "rb");
  if(input == NULL) {
    printf("Input file failed to open, please supply a valid .ppm file.\n");
    exit(2);
  }
  //Creates the pointer to the output file and checks to make sure it opened to write properly.
  FILE *output = fopen(argsv[2], "wb");
  if(output == NULL) {
    printf("Output file failed to open, please supply a valid .ppm file.\n");
    exit(7);
  }

  //Create the image from the file input.
  Image *pic = read_ppm(input);

  //Make sure a valid operation was input.
  if (argsc < 4) {
    printf("Please supply a valid operation. Valid operations are:\nswap\nbright\ninvert\ngray\ncrop\nblur\n");
    exit(4);
  }
  //Big if tree to check which argument was passed an execute the matching fucntion.
  //Also checks input and makes sure all arguments are as they should be.
  else if(strcmp(argsv[3], "swap") == 0) {
    if (argsc > 4) {
      printf("Incorrect number of arguments, please only supply 4 arguments (including the executable file)\n");
      exit(5);
    }
    Swap_Colors(pic);
  }
  else if(strcmp(argsv[3], "bright") == 0) {
    if(argsc != 5) {
      printf("Please supply a factor to brighten or darken by. Positive numbers will brighten and negative numbers will darken.\n");
      exit(5);
      }
    int val = atoi(argsv[4]);
    Bright(pic, val);
  }
  else if(strcmp(argsv[3], "invert") == 0) {
    if (argsc > 4) {
      printf("Incorrect number of arguments, please only supply 4 arguments (including the executable file)\n");
      exit(5);
    }
    Invert_Colors(pic);
  }
  else if(strcmp(argsv[3], "gray") == 0) {
    if (argsc > 4) {
      printf("Incorrect number of arguments, please only supply 4 arguments (including the executable file)\n");
      exit(5);
    }
    Grayscale_Convert(pic);
  }
  else if(strcmp(argsv[3], "crop") == 0) {
    if (argsc != 8 ) {
      printf("Please supply 4 values to crop the image: the column and row of the upper-left corner, and the column and then row of the lower-right corner\n");
      exit(5);
    }
    int col_left = atoi(argsv[4]);
    int row_top = atoi(argsv[5]);
    int col_right = atoi(argsv[6]);
    int row_down = atoi(argsv[7]);
    if (col_left < 0 || row_top < 0 || row_down > pic->rows || col_right > pic->cols || row_top > row_down || col_left > col_right) {
      printf("Invalid cropping range. Make sure you arent cropping outside of the image, and make sure your left corner isn't bigger then your right corner!\n");
      exit(6);
    }
    Crop(pic, col_left, row_top, col_right, row_down);
  }
  else if(strcmp(argsv[3], "blur") == 0) {
    if(argsc != 5) {
      printf("Please supply a value to blur the image by.\n");
      exit(5);
    }
    double val = atof(argsv[4]);
    if (val < 0) {
      printf("Please supply a blur value greater than 0.\n");
      exit(6);
    }
    Blur(pic, val);
  }
  else{
    printf("Please supply a valid operation. Valid operations are:\nswap\nbright\ninvert\ngray\ncrop\nblur\n");
    exit(4);
  }

  //Write the image to the supplied output file.
  write_ppm(output, pic);
  //Free the memory from the image.
  delete_image(pic);

  //Close open input and output files.
  fclose(input);
  fclose(output);
}

/*
* Helper function to malloc out the memory for an image structure.
* Returns the pointer to the image given a number of columns and rows.
*/
Image * create_image(int numcol, int numrow) {
  Image *pic = malloc(sizeof(Image*) + sizeof(int) * 2);
  pic->data = malloc(sizeof(Pixel) * numcol * numrow);
  if (pic == NULL) {
    printf("Error, failed to allocate memory\n");
    exit(8);
  }
  pic->data = malloc(sizeof(Pixel*) * numcol * numrow);
  if (pic->data == NULL) {
    printf("Error, failed to allocate memory\n");
    exit(8);
  }
  pic->cols = numcol;
  pic->rows = numrow;
  return pic;
}


/* Read a PPM-formatted image from a file (assumes fp != NULL).
 * Returns the address of the heap-allocated Image struct it
 * creates and populates with the Image data.
 */
Image * read_ppm(FILE *fp) {
  // check that fp is not NULL
  assert(fp);

  char str[200];
  int ncol = 0, nrow = 0, ncolor = 255;
  for(int i = 0; i < 3; i++) {
    char header = fgetc(fp);
    //Check to make sure the file supplied is a valid .ppm file.
    if(header != 'P' && i == 0) {
      printf("File is not of valid .ppm formatting\n");
      exit(3);
    }
    else if (header != '6' && i == 1) {
      printf("File is not of valid .ppm formatting\n");
      exit(3);
    }
  }
  //See if there is a comment in the input file and skip it if there is.
  if (fgetc(fp) == '#'){
    fgets(str, 100, fp);
  }
  else{
    rewind(fp);
    fseek(fp, sizeof(char) + sizeof(char), SEEK_SET);
  }
  //Read the number of columns and rows from the file header.
  fscanf(fp, "%d %d %d", &ncol, &nrow, &ncolor);

  fgetc(fp);
  //Create the file pointer by calling a helper function.
  Image *pic = create_image(ncol, nrow);
  //Read the binary data into the image data.
  int num_read = fread(pic->data, sizeof(Pixel), ncol * nrow, fp);
  //Check to make sure the file was read properly.
  if (num_read != pic->cols * pic->rows) {
    fprintf(stderr, "Uh oh. Pixel data failed to read properly!\n");
    exit(2);
  }
  return pic;
}


/* Write a PPM-formatted image to a file (assumes fp != NULL),
 * and return the number of pixels successfully written.
 */
int write_ppm(FILE *fp, const Image *im) {
  // check that fp is not NULL
  assert(fp);
  // write PPM file header, in the following format
  // P6
  // cols rows
  // 255
  fprintf(fp, "P6\n%d %d\n255\n", im->cols, im->rows);

  // now write the pixel array
  int num_pixels_written = fwrite(im->data, sizeof(Pixel), im->cols * im->rows, fp);

  //Check to make sure the file was written properly.
  if (num_pixels_written != im->cols * im->rows) {
    fprintf(stderr, "Uh oh. Pixel data failed to write properly!\n");
    exit(8);
  }

  return num_pixels_written;
}

/*
*Function to free the memory malloc'ed in create image.
*/
int delete_image(Image *pic) {
  free(pic->data);
  pic->data = NULL;
  free(pic);
  pic = NULL;
  return 0;
}
