#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <png.h>
#include "../hdr/utils.h"

/* Increments the pixel bit position n times. */
Position increment(Image img, Position pos, int n) {
    for (int i = 0; i < n; i++) {
    	if (pos.channel < 2) {
    	    pos.channel++;
	} else {
	    pos.channel = 0;
	    pos.column++;

	    if (pos.column >= img.width) {
		pos.column = 0;
		pos.row++;
	    }
	}
    }
    return pos;
}

/* Reads the text file and returns its contents as a string. */
char *readTextFile(char *fp) {
    FILE *file = fopen(fp, "r");
    if (!file) {
        printf("Error opening text file.");
        return "";
    }

    fseek(file, 0, SEEK_END);
    int len = ftell(file);
    rewind(file);

    char *str = malloc(len);
    fread(str, 1, len - 1, file);
    fclose(file);
    return str;
}

/* Parses the command line and returns all arguments starting from index as a string. */
char *readCmdLine(int argc, char *argv[], int index) {
    int len = 0;
    for (int i = index; i < argc; i++) {
        len += strlen(argv[i]) + 1;
    }

    char *str = calloc(len, sizeof(char));
    for (int i = index; i < argc; i++) {
        strcat(str, argv[i]);
        if (i < argc - 1) {
            strcat(str, " ");
        }
    }
    return str;
}

/* Returns an array containing the binary representation of num. */
int *getBinary(int num) {
    int bits = sizeof(int) * 8;
    int *bin = malloc(bits * sizeof(int));
    for (int i = 0; i < bits; i++) {
        bin[bits - 1 - i] = (((num) >> i) & 1);
    }
    return bin;
}

/* Flips 1 or 2 bits in data at random to simulate data disruption. */
void simulateNoise(int *data, int len) {
    srand(time(0));
    for (int i = 0; i < rand() % 2 + 1; i++) {
        int r = rand() % len + 1;
        printf("Flipping bit %d from %d to %d.\n", r, data[r], data[r] ? 0 : 1);
        data[r] = data[r] ? 0 : 1;

        int newrand;
        do {
            newrand = rand() % len + 1;
        } while (newrand == r);
        r = newrand;
    }
}
