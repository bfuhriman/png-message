#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../hdr/hamming.h"
#include "../hdr/utils.h"
#include "../hdr/file.h"
#include "../hdr/encode.h"

/* If true, 1 or 2 bits will be flipped at random before writing data.
   Noise is set to true when the program is ran with the -n flag. */
bool noise = false;

/* Fetches a string from the command line or a text file and encodes it in the image. */
int main(int argc, char *argv[]) {
    Image img = read(argv[1]);
    char *str;
    int arg = 3;

    while (argv[arg][0] == '-' && strlen(argv[arg]) == 2) {
        if (strcmp(argv[arg], "-n") == 0) {
            noise = true;
        } else if (strcmp(argv[arg], "-f") == 0) {
            str = readTextFile(argv[arg + 1]);
        }
        arg++;
    }

    if (!str) {
        str = readCmdLine(argc, argv, arg);
    }

    encode(img, str);
    save(img, argv[2]);
}

/* Reads bits from str and applies data redundancy, then writes the codeword and its length to img. */
void encode(Image img, char *str) {
	if (strlen(str) > maxlen(img)) {
		printf("Your message is too long. Maximum length for the image provided: %d\n", maxlen(img));
		return;
	}

    Position pos = {0, 0, 0,};
	int d = strlen(str) * 8;
	int p = minRedundancy(d);
	int len = d + p;
    int *bin = getBinary(len);

	write(img, pos, bin, sizeof(int) * 8);
	pos = increment(img, pos, sizeof(int) * 8);
    free(bin);

	int *data = getDataBits(str, len);
    free(str);

    for (int i = 1; i < len; i *= 2) {
        data[i] = getParity(data, len, i);
    }
    data[0] = getOverallParity(data, len);

    if (noise) {
        simulateNoise(data, len);
    }

	write(img, pos, data, len);
	free(data);
}

/* Allocates memory for the codeword and inserts data bits, leaving power of 2 indices empty. */
int *getDataBits(char *str, int len) {
	int *bits = calloc(len, sizeof(int));
    int strIndex = 0;
    int bitIndex = 0;
    char c, bit;

    while (strIndex < strlen(str) * 8) {
        c = str[strIndex / 8];
        bit = ((c >> (7 - (strIndex % 8))) & 1);

        while ((bitIndex & (bitIndex - 1)) == 0) {
            bitIndex++;
        }

        bits[bitIndex++] = bit;
        strIndex++;
    }
	return bits;
}

/* Writes the data to the least significant bits of each pixel, starting at pos. */
void write(Image img, Position pos, int* data, int len) {
	png_bytep row, px;
    for (int i = 0; i < len; i++) {
		row = img.rows[pos.row];
		px = &(row[pos.column * 4]);
		px[pos.channel] = (px[pos.channel] & 0xFE) | data[i];
		pos = increment(img, pos, 1);
	}
}

/* Calculates the maximum number of characters that can be encoded in img. */
int maxlen(Image img) {
	int d, max = img.height * img.width * 3;
	for (d = max; d + minRedundancy(d) + sizeof(int) > max; d--);
	return d / 8;
}
