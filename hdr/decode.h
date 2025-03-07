#ifndef DECODE_H
#define DECODE_H

#include <png.h>

/* Decodes message from the least significant bits of each pixel. */
char *decode(Image image);

/* Parses the codeword and returns the original string. */
char *getMessage(int *codeword, int len);

/* Returns the least significant bit at position pos. */
int getBit(Image img, Position pos);

#endif
