/* DIPs.c */
// Janice Ho 


#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

#include "Constants.h"
#include "DIPs.h"
#include "Image.h"


/* reverse image color */
Image *Negative(Image *image) {
    assert(image);
	int x, y;
	for (y = 0; y < ImageHeight(image); y++) {
		for (x = 0; x < ImageWidth(image); x++) {

            unsigned int r = GetPixelR(image, x, y);
			unsigned int g = GetPixelG(image, x, y);
			unsigned int b = GetPixelB(image, x, y);
			SetPixelR(image, x, y, MAX_PIXEL - r);
			SetPixelG(image, x, y, MAX_PIXEL - g);
			SetPixelB(image, x, y, MAX_PIXEL - b);
		}
	}
    return image; 
}


/* color filter */
Image *ColorFilter (Image *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b) {

    assert(image);
    int x, y;

    replace_r = (replace_r > MAX_PIXEL) ? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
    replace_g = (replace_g > MAX_PIXEL) ? MAX_PIXEL : (replace_g < 0) ? 0 : replace_g;
    replace_b = (replace_b > MAX_PIXEL) ? MAX_PIXEL : (replace_b < 0) ? 0 : replace_b;

    for (y = 0; y < ImageHeight(image); y++){
        for (x = 0; x < ImageWidth(image); x++){
            unsigned int r = r = GetPixelR(image, x, y);
            unsigned int g = GetPixelG(image, x, y);
			unsigned int b = GetPixelB(image, x, y);
			if (abs(r - target_r) <= threshold && abs(g - target_g) <= threshold && abs(b - target_b) <= threshold) {

                SetPixelR(image, x, y, replace_r);
                SetPixelG(image, x, y, replace_g);
			    SetPixelB(image, x, y, replace_b);
            }
        }
    }
    return image; 
}

/* edge detection */
Image *Edge(Image *image) {

    assert(image);
	int x, y, m, n, a, b;
	unsigned char   tmpR[ImageWidth(image)][ImageHeight(image)];
	unsigned char   tmpG[ImageWidth(image)][ImageHeight(image)];
	unsigned char   tmpB[ImageWidth(image)][ImageHeight(image)];

	for (y = 0; y < ImageHeight(image); y++){
		for (x = 0; x < ImageWidth(image); x++) {
			tmpR[x][y] = GetPixelR(image, x, y);
			tmpG[x][y] = GetPixelG(image, x, y);
			tmpB[x][y] = GetPixelB(image, x, y);
		}
	}

	int sumR = 0, sumG = 0, sumB = 0;
    // sum of the intensity differences 

	for (y = 1; y < ImageHeight(image) - 1; y++){
		for (x = 1; x < ImageWidth(image) - 1; x++){
			for (n = -1; n <= 1; n++){
				for (m = -1; m <= 1; m++) {
					a = (x + m >= ImageWidth(image)) ? ImageWidth(image) - 1 : (x + m < 0) ? 0 : x + m;
					b = (y + n >= ImageHeight(image)) ? ImageHeight(image) - 1 : (y + n < 0) ? 0 : y + n;
					sumR += (tmpR[x][y] - tmpR[a][b]);
					sumG += (tmpG[x][y] - tmpG[a][b]);
					sumB += (tmpB[x][y] - tmpB[a][b]);
				}
			}
			SetPixelR(image, x, y, (sumR > MAX_PIXEL) ? MAX_PIXEL: (sumR < 0) ? 0: sumR);
			SetPixelG(image, x, y, (sumG > MAX_PIXEL) ? MAX_PIXEL: (sumG < 0) ? 0: sumG);
			SetPixelB(image, x, y, (sumB > MAX_PIXEL) ? MAX_PIXEL: (sumB < 0) ? 0: sumB);
			sumR = sumG = sumB = 0;
		}
	}
	
    // setting all y borders to 0
	for (y = 0; y < ImageHeight(image); y++) {
		SetPixelR(image, 0, y, 0);
		SetPixelG(image, 0, y, 0);
		SetPixelB(image, 0, y, 0);
		SetPixelR(image, ImageWidth(image) - 1, y, 0);
		SetPixelG(image, ImageWidth(image) - 1, y, 0);
		SetPixelB(image, ImageWidth(image) - 1, y, 0);
	}
    // setting all x boarders to 0
	for (x = 0; x < ImageWidth(image); x++) {
		SetPixelR(image, x, 0, 0);
		SetPixelG(image, x, 0, 0);
		SetPixelB(image, x, 0, 0);
		SetPixelR(image, x, ImageHeight(image) - 1, 0);
		SetPixelG(image, x, ImageHeight(image) - 1, 0);
		SetPixelB(image, x, ImageHeight(image) - 1, 0);
	}
    return image; 
}


/* mirror image horizontally */
Image *HMirror(Image *image){
   assert(image);
    int x, y;

    for (y = 0; y < ImageHeight(image); y++) {
        for (x = 0; x < ImageWidth(image) / 2; x++) {
            SetPixelR(image, ImageWidth(image) - 1 - x, y, GetPixelR(image, x, y));
			SetPixelG(image, ImageWidth(image) - 1 - x, y, GetPixelG(image, x, y));
			SetPixelB(image, ImageWidth(image) - 1 - x, y, GetPixelB(image, x, y));
        }
    }
    return image; 
}

/* Pizelate image */
Image *Pixelate(Image *image, int block_size){
    assert(image);
    int x, y, bx, by;
    int WIDTH = ImageWidth(image);
    int HEIGHT = ImageHeight(image);
    int sumR, sumG, sumB;
    int count;

    for (y = 0; y < HEIGHT - HEIGHT % block_size; y += block_size) {
        for (x = 0; x < WIDTH - WIDTH % block_size; x += block_size) {
            sumR = sumG = sumB = 0; // initialize
            count = 0;

            for (by = 0; by < block_size; by++) {
                for (bx = 0; bx < block_size; bx++) {
                    sumR += GetPixelR(image, x + bx, y + by);
                    sumG += GetPixelG(image, x + bx, y + by);
                    sumB += GetPixelB(image, x + bx, y + by);
                    count++;
                }
            }

            // calculate average RGB value
            sumR /= count;
            sumG /= count;
            sumB /= count;

            // write new values to pixels in the block
            for (by = 0; by < block_size; by++) {
                for (bx = 0; bx < block_size; bx++) {
                    SetPixelR(image, x + bx, y + by, sumR);
                    SetPixelG(image, x + bx, y + by, sumG);
                    SetPixelB(image, x + bx, y + by, sumB);
                
                }
            }
        }
    }
    return image; 
}

/* change color image to black & white */
Image *BlackNWhite(Image *image){
    assert(image);
    int x, y, tmp;

    for (y = 0; y < ImageHeight(image); y++)
    {
        for (x = 0; x < ImageWidth(image); x++)
        {
            unsigned char r = GetPixelR(image, x, y);
			unsigned char g = GetPixelG(image, x, y);
			unsigned char b = GetPixelB(image, x, y);

			tmp = (r + g + b) / 3;

			SetPixelR(image, x, y, tmp);
			SetPixelG(image, x, y, tmp);
			SetPixelB(image, x, y, tmp);

        }
    }
    return image; 
}

/* flip image vertically */
Image *VFlip(Image *image){
    assert(image);
    int x, y;
    int width = ImageWidth(image);
    int height = ImageHeight(image);
    unsigned char   r, g, b;

    for (y = 0; y < height / 2; y++) {
        for (x = 0; x < width; x++) {
            r = GetPixelR(image, x, height - 1 - y);
            g = GetPixelG(image, x, height - 1 - y);
            b = GetPixelB(image, x, height - 1 - y);

            SetPixelR(image, x, height - 1 - y, GetPixelR(image, x, y));
            SetPixelG(image, x, height - 1 - y, GetPixelG(image, x, y));
            SetPixelB(image, x, height - 1 - y, GetPixelB(image, x, y));

            // copy new pixels onto old
            SetPixelR(image, x, y, r);
            SetPixelG(image, x, y, g);
            SetPixelB(image, x, y, b);

        }
    }
    return image; 
}

/* Shuffle Image */
Image *Shuffle(Image *image){
    assert(image);
    int WIDTH = ImageWidth(image);
    int HEIGHT = ImageHeight(image);
    int block_width = WIDTH/SHUFF_WIDTH_DIV;
    int block_height = HEIGHT/SHUFF_HEIGHT_DIV;
    int i, j, x, y;
    unsigned char tempR, tempG, tempB;

    for (i = 0; i < SHUFF_HEIGHT_DIV/2; i++){ // only need to iterate throught half of the blocks
        for (j = 0; j < SHUFF_WIDTH_DIV; j++){
            for (x = 0; x < block_width; x++){
                for (y = 0; y < block_height; y++){
                    int srcX = x + (j * block_width);
                    int srcY = y + (i * block_height);
                    int dstX = x + ((SHUFF_WIDTH_DIV - 1 - j) * block_width);
                    int dstY = y + ((SHUFF_HEIGHT_DIV - 1 - i) * block_height);

                    tempR = GetPixelR(image, srcX, srcY);
                    tempG = GetPixelG(image, srcX, srcY);
                    tempB = GetPixelB(image, srcX, srcY);

                    SetPixelR(image, srcX, srcY, GetPixelR(image, dstX, dstY));
                    SetPixelG(image, srcX, srcY, GetPixelG(image, dstX, dstY));
                    SetPixelB(image, srcX, srcY, GetPixelB(image, dstX, dstY));

                    SetPixelR(image, dstX, dstY, tempR);
                    SetPixelG(image, dstX, dstY, tempG);
                    SetPixelB(image, dstX, dstY, tempB);
                }
            }
        }
        
    }
    return image; 
}

/* Shift an image */
Image *Shift(Image *image, int shiftX, int shiftY){
    assert(image);
    int WIDTH = ImageWidth(image);
    int HEIGHT = ImageHeight(image);
    Image *shiftedImage = CreateImage(WIDTH, HEIGHT); 
    // temp image to hold new shifted image values 

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // wrap-around coordinates
            int newX = (x + shiftX) % WIDTH;
            int newY = (y + shiftY) % HEIGHT;

            if (newX < 0) newX += WIDTH;
            if (newY < 0) newY += HEIGHT;

            // origional pixel values
            unsigned char r = GetPixelR(image, x, y);
            unsigned char g = GetPixelG(image, x, y);
            unsigned char b = GetPixelB(image, x, y);

            // copy new values onto old
            SetPixelR(shiftedImage, newX, newY, r);
            SetPixelG(shiftedImage, newX, newY, g);
            SetPixelB(shiftedImage, newX, newY, b);
        }
    }
    DeleteImage(image);

    return shiftedImage;

}


/* add color border to image */
Image *AddBorder(Image *image, char *color, int border_width){
    assert(image);
    int x, y;

    int WIDTH = ImageWidth(image);
    int HEIGHT = ImageHeight(image);

    int border_r = 255;
    int border_g = 255;
    int border_b = 255;

    if (!strcmp(color, "black")) { // rgb for black
        border_r = 0;
        border_g = 0;
        border_b = 0;
    } else if (!strcmp(color, "white")) { // rgb for white
        border_r = 255;
        border_g = 255;
        border_b = 255;
    } else if (!strcmp(color, "red")) {
        border_r = 255;
        border_g = 0;
        border_b = 0;
    } else if (!strcmp(color, "green")) {
        border_r = 0;
        border_g = 255;
        border_b = 0;
    } else if (!strcmp(color, "blue")) {
        border_r = 0;
        border_g = 0;
        border_b = 255;
    } else if (!strcmp(color, "yellow")) { 
        border_r = 255;
        border_g = 255;
        border_b = 0;
    } else if (!strcmp(color, "cyan")) {
        border_r = 0;
        border_g = 255;
        border_b = 255;
    } else if (!strcmp(color, "pink")) { // rgb for pink
        border_r = 255;
        border_g = 192;
        border_b = 203;
    } else if (!strcmp(color, "orange")) { // rgb for orange 
        border_r = 255;
        border_g = 165;
        border_b = 0;
    } else {
        printf("Error. Invalid color option.\n"); // error handling 
        return 0;
    }
    
    // iterate through new image
    for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++) {
            // set borders
			if ((y < border_width) || (y > HEIGHT - 1 - border_width) ||
					(x < border_width) || (x > WIDTH - 1 - border_width)) {

                    // copy new onto old image 
                    SetPixelR(image, x, y, border_r);
                    SetPixelG(image, x, y, border_g);
                    SetPixelB(image, x, y, border_b);
        
            }
        }
    }
    return image;
}
















