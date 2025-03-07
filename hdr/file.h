#ifndef FILE_H
#define FILE_H

/* Reads image file into memory and prepares it for encoding. */
Image read(char *filename);

/* Saves the image to an output file. */
void save(Image img, char *filename);

#endif
