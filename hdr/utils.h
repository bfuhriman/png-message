#ifndef UTILS_H
#define UTILS_H

#include <png.h>

/* Stores image dimensions and other important information. */
typedef struct {
    int width;
    int height;
    png_bytep *rows;
} Image;

/* Stores the location of a particular pixel bit in an image. */
typedef struct {
    int row;
    int column;
    int channel;
} Position;

/* Increments the pixel bit position n times. */
Position increment(Image img, Position pos, int n);

/* Reads the text file and returns its contents as a string. */
char *readTextFile(char *fp);

/* Parses the command line and returns all arguments starting from index as a string. */
char *readCmdLine(int argc, char *argv[], int index);

/* Returns an array containing the binary representation of num. */
int *getBinary(int num);

/* Flips 1 or 2 bits in data at random to simulate data disruption. */
void simulateNoise(int *data, int len);

#endif
