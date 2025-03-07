#ifndef ENCODE_H
#define ENCODE_H

#include <png.h>

/* Reads bits from str and applies data redundancy, then writes the codeword and its length to img. */
void encode(Image img, char *str);

/* Allocates memory for the codeword and inserts data bits, leaving power of 2 indices empty. */
int *getDataBits(char *str, int len);

/* Writes the data to the least significant bits of each pixel, starting at pos. */
void write(Image img, Position pos, int* data, int len);

/* Calculates the maximum number of characters that can be encoded in img. */
int maxlen(Image img);

#endif
