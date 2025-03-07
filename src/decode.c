#include <stdlib.h>
#include <stdio.h>
#include "../hdr/hamming.h"
#include "../hdr/utils.h"
#include "../hdr/file.h"
#include "../hdr/decode.h"

/* Reads a message encoded in the image, then prints the message or writes it to a text file. */
int main(int argc, char *argv[]) {
    Image img = read(argv[1]);
    char *str = decode(img);

    if (!str) {
        printf("No message was found in %s.\n", argv[1]);
        return 1;
    }

    if (!argv[2]){
        printf("%s\n", str);
    } else {
        FILE *file = fopen(argv[3], "w");
        fprintf(file, "%s", str);
        fprintf(file, "%c", '\n');
        fclose(file);
    }
    free(str);
}

/* Decodes message from the least significant bits of each pixel. */
char *decode(Image img) {
    Position pos = {0, 0, 0};
    int len = 0;
	
    for (int i = 0; i < sizeof(int) * 8; i++) {
        len = (len << 1) | getBit(img, pos);
	pos = increment(img, pos, 1);
    }

    if (len == -1) {
        return NULL;
    }

    int index = 0;
    int codeword[len];
    while (index < len) {
	codeword[index++] = getBit(img, pos);
	pos = increment(img, pos, 1);
    }

    int err = findErrors(codeword, len);
    if (err > 0) {
        codeword[err] = codeword[err] ? 0 : 1;
        printf("A single-bit error was found and corrected at index %d.\n", err);
    } else if (err < 0) {
        printf("An unfixable two-bit error has been detected.\n");
    }

    return getMessage(codeword, len);
}

/* Parses the codeword and returns the original string. */
char *getMessage(int *codeword, int len) {
    int index = 1, bits = 0;
    char *str = malloc(maxData(len));
    char c = 0;

    while (index < len) {
        if ((index & (index - 1)) != 0) {
	    c |= codeword[index] << (7 - (bits % 8));
	    bits++;

            if (bits % 8 == 0) {
                str[bits / 8 - 1] = c;
                c = 0;
            }
	}
	index++;
    }
    str[bits / 8] = '\0';
    return str;
}

/* Returns the least significant bit at position pos. */
int getBit(Image img, Position pos) {
    png_bytep row, px;
    row = img.rows[pos.row];
    px = &(row[pos.column * 4]);
    return px[pos.channel] & 1;
}
