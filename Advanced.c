/* Advanced.c New Fuction Implimentation */
// Janice Ho 

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
 
#include "Advanced.h"
#include "Constants.h"
#include "Image.h"


/* Crop */
Image *Crop(Image *image, int x, int y, int W, int H){
    assert(image);
    
    // create new image with new size 
    Image *croppedImage = CreateImage(W, H);

    // iterate through new image
    for (int oldX = x; oldX  < x + W; oldX++) {
        for (int oldY = y; oldY < y + H; oldY++) {
            
            // get old values
            int tempR = GetPixelR(image, oldX, oldY);
            int tempG = GetPixelG(image, oldX, oldY);
            int tempB = GetPixelB(image, oldX, oldY);
            
            // establish new image by subtracting old values with input 
            SetPixelR(croppedImage, oldX-x, oldY-y, tempR);
            SetPixelG(croppedImage, oldX-x, oldY-y, tempG);
            SetPixelB(croppedImage, oldX-x, oldY-y, tempB);
        }
    }

    // delete old image
	DeleteImage(image);
	image = NULL;

    // return new 
    return croppedImage;
}


/* Resize */
Image *Resize(Image *image, int newWidth, int newHeight){
    assert(image);
    int oldWidth = ImageWidth(image);
    int oldHeight = ImageHeight(image);
    
    // create new image with new size
    Image *resizedImage = CreateImage(newWidth, newHeight);

    // finding the scaling factors from lab manual 
    double ScaleX = (double)newWidth/oldWidth;
    double ScaleY = (double)newHeight/oldHeight;

    // iterate on new image
    for (int x = 0; x < newWidth; x++){
		for (int y = 0; y < newHeight; y++){
            // find origional x and y values
			int oldX = (int)(x / ScaleX);
			int oldY = (int)(y / ScaleY);

            // maximum bounds error handeling 
            if (oldX >= oldWidth) oldX = oldWidth - 1;
            if (oldY >= oldHeight) oldY = oldHeight - 1;

            // get values from old image
			unsigned int r = GetPixelR(image, oldX, oldY);
			unsigned int g = GetPixelG(image, oldX, oldY);
			unsigned int b = GetPixelB(image, oldX, oldY);
            // set values to resized image
			SetPixelR(resizedImage, x, y, r);
			SetPixelG(resizedImage, x, y, g);
			SetPixelB(resizedImage, x, y, b);
		}
	}

    DeleteImage(image);
	image = NULL;
	return resizedImage;
}


/* Watermark */
Image *Watermark(Image *image, const Image *watermark_image){
    assert(image);
    assert(watermark_image);

    int WIDTH = ImageWidth(image);
    int HEIGHT = ImageHeight(image);

    int waterWidth = ImageWidth(watermark_image);
    int waterHeight = ImageHeight(watermark_image);

    for(int y = 0; y < HEIGHT; y++){
        for( int x = 0; x < WIDTH; x++){

            // watermark wrap around 
            int waterX = x % waterWidth;
            int waterY = y % waterHeight;

            // get watermark pixel coordinates from image 
            unsigned char waterR = GetPixelR(watermark_image, waterX, waterY);
            unsigned char waterG = GetPixelG(watermark_image, waterX, waterY);
            unsigned char waterB = GetPixelB(watermark_image, waterX, waterY);
        
            // find where watermark has blaxk pixels and if black then:
            if (waterR == 0 && waterG == 0 && waterB == 0) {
                // get original image values 
                unsigned char r = GetPixelR(image, x, y);
                unsigned char g = GetPixelG(image, x, y);
                unsigned char b = GetPixelB(image, x, y);

                // multiply origional with 1.45, making sure that colors stay in bounds w/ saturation 
                r = (r * 1.45 > 255) ? 255 : (unsigned char)(r * 1.45);
                g = (g * 1.45 > 255) ? 255 : (unsigned char)(g * 1.45);
                b = (b * 1.45 > 255) ? 255 : (unsigned char)(b * 1.45);
        
                // set new pixel values
                SetPixelR(image, x, y, r);
                SetPixelG(image, x, y, g);
                SetPixelB(image, x, y, b);
            }
        }
    }

    return image;
}

/* Rotate by 90 */
Image *RotateBy90(Image *image, int rotateDirection){
    assert(image);

    int WIDTH = ImageWidth(image);
    int HEIGHT = ImageHeight(image);

    Image *rotatedImage = CreateImage(HEIGHT, WIDTH);

    // iterate over image 
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // get origional image pixels 
            unsigned char r = GetPixelR(image, x, y);
            unsigned char g = GetPixelG(image, x, y);
            unsigned char b = GetPixelB(image, x, y);
            
            // establish variables for new x and y image dimensions 
            int newX, newY;
            
            if (rotateDirection == 0) { // clockwise calculation 
                newX = HEIGHT - 1 - y;
                newY = x;
            } else { // counterclockwise calculation
                newX = y;
                newY = WIDTH - 1 - x;
            }

            // set new pixels onto image 
            SetPixelR(rotatedImage, newX, newY, r);
            SetPixelG(rotatedImage, newX, newY, g);
            SetPixelB(rotatedImage, newX, newY, b);
        }
    }

    // delete old image
    DeleteImage(image);
    // return new image 
    return rotatedImage;
}


