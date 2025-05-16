/* Image.c */
// Janice Ho

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Image.h"

/* Get the R intensity of pixel (x, y) in image */
unsigned char GetPixelR(const Image *image, unsigned int x,  unsigned int y){
    // check valid image input
    assert(image);
   
	assert(image->R != NULL);
	
    return image->R[x + (y * image->W)];
}

/* Get the G intensity of pixel (x, y) in image */
unsigned char GetPixelG(const Image *image, unsigned int x,  unsigned int y){
    // check valid image input
    assert(image);
    
	assert(image->G != NULL);

	return image->G[x + (y * image->W)];
}

/* Get the B intensity of pixel (x, y) in image */
unsigned char GetPixelB(const Image *image, unsigned int x,  unsigned int y){
    // check valid image input
    assert(image);
   
	assert(image->B != NULL);

	return image->B[x + (y * image->W)];
}

/* Set the R intensity of pixel (x, y) in image to r */
void SetPixelR(Image *image, unsigned int x,  unsigned int y, unsigned char r){
    // check valid image input
    assert(image);
	assert(image->R != NULL);

	image->R[x + (y * image->W)] = r;
}

/* Set the G intensity of pixel (x, y) in image to g */
void SetPixelG(Image *image, unsigned int x,  unsigned int y, unsigned char g){
    // check valid image input
    assert(image);
	assert(image->G != NULL);

	image->G[x + (y * image->W)] = g;
}

/* Set the B intensity of pixel (x, y) in image to b */
void SetPixelB(Image *image, unsigned int x,  unsigned int y, unsigned char b){
    // check valid image input
    assert(image);
	assert(image->B != NULL);

	image->B[x + (y * image->W)] = b;
}

/* Allocate dynamic memory for the image structure and its R/G/B values */
/* Return the pointer to the image, or NULL in case of error */
Image *CreateImage(unsigned int Width, unsigned int Height){
	Image *image = (Image *)malloc(sizeof(Image));
	assert(image != NULL);
    
    image->W = Width;
    image->H = Height;


    image->R = (unsigned char *)malloc(Width * Height * sizeof(unsigned char));
    image->G = (unsigned char *)malloc(Width * Height * sizeof(unsigned char));
    image->B = (unsigned char *)malloc(Width * Height * sizeof(unsigned char));

    assert(image->R != NULL && image->G != NULL && image->B != NULL);

    return image; 
}

/* Free the memory for the R/G/B values and Image structure */
void DeleteImage(Image *image){
        // valid image, free or "delete"
        assert(image);
        if (image->R) {
            free(image->R);
            image->R = NULL;
        }
        if (image->G) {
            free(image->G);
            image->G = NULL;
        }
        if (image->B) {
            free(image->B);
            image->B = NULL;
        }
        free(image);
        image = NULL; 
}  

/* Return the image's width in pixels */
unsigned int ImageWidth(const Image *image){
    assert(image);
    return image->W;
}

/* Return the image's height in pixels */
unsigned int ImageHeight(const Image *image){

    assert(image);
    return image->H;
}


