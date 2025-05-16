/* PhotoLab.c */
// Janice Ho

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "DIPs.h"
#include "Test.h"
#include "Image.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"


// print a menu
void PrintMenu();

// main function 
int main() {

#ifdef DEBUG
    AutoTest();
    return 0;

#else

	int option;			/* user input option */
	char fname[SLEN];		/* input file name */

	PrintMenu();
	printf("Please make your choice: ");
	scanf("%d", &option);


	/* ColorFilter() parameters */
	int target_r, target_g, target_b, threshold;
	double factor_r, factor_g, factor_b;
	
    /* Pixelate() parameter */
	int block_size;

    /* AddBorder() parameters */
    int border_width;
    char color[SLEN];
    
	/* Crop() parameters */
	int x, y, W, H; 

	/* Resize() parameters */
	int newWidth, newHeight;

	/* RotateBy90() parameters */
	int rotateDirection;

	/* Watermark() parameters */
	Image *watermark_image = NULL;


    Image *image = NULL;
	while (option != EXIT) {
		if (option == 1) {
			printf("Please input the file name to load: ");
			scanf("%75s", fname);
			image = LoadImage(fname);
            if (!image){
                return SUCCESS;
            }
		}

		// menu item 2 - 16 requires image is loaded first 
		else if (option >= 2 && option <= 16) {
			if (image == NULL)	 {
				printf("No image to process.\n");
			}
			
			else {
				switch(option) {
					case 2:
						printf("Please input the file name to save: ");
						scanf("%75s", fname);
						SaveImage(fname, image);
						break;
					case 3:
						image = BlackNWhite(image);
						printf("\"Black & White\" operation is done!\n");
						break;
					case 4:
						image = Negative(image);
						printf("\"Negative\" operation is done!\n");
						break;
					case 5:
						printf("Enter Red   component for the target color: ");
						scanf("%d", &target_r);
						printf("Enter Green component for the target color: ");
						scanf("%d", &target_g);
						printf("Enter Blue  component for the target color: ");
						scanf("%d", &target_b);
						printf("Enter threshold for the color difference: ");
						scanf("%d", &threshold);
						printf("Enter value for Red component in the target color: ");
						scanf("%lf", &factor_r);
						printf("Enter value for Green component in the target color: ");
						scanf("%lf", &factor_g);
						printf("Enter value for Blue  component in the target color: ");
						scanf("%lf", &factor_b);
						image = ColorFilter(image, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
						printf("\"Color Filter\" operation is done!\n");
						break;
					case 6:
						image = Edge(image);
						printf("\"Edge\" operation is done!\n");
						break;
					case 7:
						image = Shuffle(image);
						printf("\"Shuffle\" operation is done!\n");
						break;
					case 8:
						image = VFlip(image);
						printf("\"VFlip\" operation is done!\n");
						break;
					case 9:
						image = HMirror(image);
						printf("\"HMirror\" operation is done!\n");
						break;
                    case 10: // boarder
                        printf("Enter border width: ");
                        scanf("%d", &border_width);
                        printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
                        printf("Select border color from the options: ");
                        scanf("%s", color);
                        image = AddBorder(image, color, border_width);
						printf("\"Boarder\" operation is done!\n");
						break; 
					case 11: // pixelate
						printf("Enter pixelate block size: ");
						scanf("%d", &block_size);
						image = Pixelate(image, block_size);
						printf("\"Pixelate\" operation is done!\n");
						break;
					 case 12: // shift
                        image = Shift(image, 160 , 40);
						printf("\"Shift\" operation is done!\n");
						break;
					case 13: // crop
						printf("Please enter the X offset value: ");
						scanf("%d", &x);
						printf("Please enter the Y offset value: ");
						scanf("%d", &y);
						printf("Please input the crop width: ");
						scanf("%d", &W);
						printf("Please input the crop height: ");
						scanf("%d", &H);
						image = Crop(image, x, y, W, H);
						printf("\"Crop\" operation is done!\n");
						break;
					case 14: // resize 
						printf("Please input the new image width: ");
						scanf("%d", &newWidth);
						printf("Please input the new image height: ");
						scanf("%d", &newHeight);
						image = Resize(image, newWidth, newHeight);
						printf("\"Resizing the image\" is done!\n");
						break;
                    case 15: // watermark 
						watermark_image = LoadImage("watermark_template");
						image = Watermark(image, watermark_image);
                        printf("\"Watermark\" operation is done!\n");
						DeleteImage(watermark_image);
						break;
                    case 16: // 90 degree rotate
						printf("Please input the direction of rotation (0:clockwise, 1:counterclockwise): ");
						scanf("%d", &rotateDirection);
						image = RotateBy90(image, rotateDirection);
                        printf("\"RotateBy90\" operation is done!\n"); 
					default: // invalid choice
						break;
				}
			}
		}
		else if (option == 17) {
			AutoTest();
			
		}
		else {
			printf("Invalid selection!\n");
		}

		// otherwise waiting for input 
		PrintMenu();
		printf("Please make your choice: ");
		scanf("%d", &option);
	}
	printf("You exit the program.\n");

#endif
	return 0;
}



/* menu */
void PrintMenu() {
	printf("\n----------------------------\n");
	printf(" 1: Load a PPM image\n");
	printf(" 2: Save an image in PPM and JPEG format\n");
	printf(" 3: Change a color image to Black & White\n");
	printf(" 4: Make a negative of an image\n");
	printf(" 5: Color filter an image\n");
	printf(" 6: Sketch the edge of an image\n");
	printf(" 7: Shuffle an image\n");
	printf(" 8: Flip an image vertically\n");
	printf(" 9: Mirror an image horizontally\n");
	printf("10: Add border to an image\n");
	printf("11: Pixelate an image\n");
	printf("12: Shift an image\n");
	printf("13: Crop an image \n");
	printf("14: Resize an image\n");
    printf("15: Add Watermark to an image\n");
    printf("16: Rotate an image by 90 degree\n");
	printf("17: Test all functions\n");
	printf("18: Exit\n");
}
