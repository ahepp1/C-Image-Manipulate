//Emerson Sullivan, Eric Bao, Alex Hepp, Jack Goldrick
//esulli26, ebao1, ahepp1, jgoldri5


#ifndef PPM_IO_H
#define PPM_IO_H

#include <stdio.h>

/* A struct to store a single RGB pixel, one byte per color channel.
 */
typedef struct _pixel {
  unsigned char r;  //red   channel value
  unsigned char g;  //green channel value
  unsigned char b;  //blue  channel value
} Pixel;

/* A struct to bundle together a pixel array with the other
 * image data we'll frequently want to pass around with it.
 * (This saves us from having to pass the same three
 * variables to every function.) Note that no Pixels are
 * stored within this struct; the data field is a pointer.
 */
typedef struct _image {
  Pixel *data;  //pointer to array of Pixels
  int rows;     //number of rows of Pixels
  int cols;     //number of columns of Pixels
} Image;

/*
 * Wrapper funtion to handle all input and output. When given an integer
 * representing the number of command line arguments passed, and an array of
 * the strings passed, it will decide which of the manipulation functions to
 * run and write the new image. If no issues are encountered, main will return 0
 * after calling this function.
 */
void wrapper(int argsc, char* argsv[]);

/* Read a PPM-formatted image from a file (assumes fp != NULL).
 * Returns the address of the heap-allocated Image struct it
 * creates and populates with the Image data.
 */
Image * read_ppm(FILE *fp);


/* Write a PPM-formatted image to a file (assumes fp != NULL),
 * and return the number of pixels successfully written.
 */
int write_ppm(FILE *fp, const Image *im);


/* Creates the image by taking the file and completing the array
 * of pixels with values representing the image.
 */
Image * create_image(int cols, int rows);


/*
 * Frees allocated space in heap, called when space no longer needed.
 */
int delete_image(Image *pic);


#endif
