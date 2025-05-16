# MAKEFILE
# Author: Janice Ho 30945594

all: PhotoLab PhotoLabTest
	
# object files
FileIO.o: FileIO.h FileIO.c Constants.h
	gcc -Wall -std=c11 -c FileIO.c -o FileIO.o
PhotoLab.o: PhotoLab.c DIPs.h Advanced.h FileIO.h Constants.h
	gcc -Wall -std=c11 -c PhotoLab.c -o PhotoLab.o
Test.o: Test.h Test.c
	gcc -Wall -std=c11 -c Test.c -o Test.o
Image.o: Image.h Image.c
	gcc -Wall -std=c11 -c Image.c -o Image.o
Advanced.o: Advanced.h Advanced.c Constants.h
	gcc -Wall -lm -std=c11 -c Advanced.c -o Advanced.o
DIPS.o: DIPs.c
	gcc -Wall -std=c11 -c DIPs.c -o DIPS.o

# executiables 
PhotoLab: Advanced.o DIPS.o FileIO.o PhotoLab.o Test.o Image.o
	gcc -Wall -lm -std=c11 PhotoLab.o DIPS.o Image.o Test.o Advanced.o FileIO.o -o PhotoLab
PhotoLabTest: Advanced.o DIPS.o FileIO.o PhotoLab.o PhotoLab.o Test.o Image.o
	gcc -Wall -std=c11 -DDEBUG -o PhotoLabTest PhotoLab.c DIPs.c Advanced.c FileIO.c Image.o Test.o -lm

# remove files and images 
clean:
	rm -f *.o PhotoLab PhotoLabTest 
	rm -f $(filter-out EngPlaza.ppm watermark_template.ppm border.ppm, $(wildcard *.ppm)) 
# removes all images except EngPlaza